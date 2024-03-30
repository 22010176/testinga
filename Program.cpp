#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "Constant.h"
#include "Utilities.h"

SDL_Window* InitWindow();
void InitDriver(SDL_Window* window);
SDL_Renderer* InitRenderer(SDL_Window* window);

void MainLoop(void(*loopFunc)(), void(*eventFunc)(SDL_Event* event));
void CleanUp();

// global window's objects
SDL_Window* window;
SDL_Renderer* renderer;
bool running = true;

Scene startScene;
void InitStartScene() {
    TTF_Font* primaryFont = TTF_OpenFont("./assets/font/SourceCodePro-SemiBold.ttf", 40);
    TTF_Font* titleFont = TTF_OpenFont("./assets/font/SourceCodePro-ExtraBold.ttf", 100);
    int btnW = 250, btnH = 65, posx = CalcPadding(WIDTH, btnW), posy = CalcPadding(HEIGHT, btnH) + btnH;

    GameObject* playBtn_ = CreateBtnObj(renderer, { "PLAY",primaryFont,white }, green, { posx,posy,btnW,btnH });
    GameObject* optBtn_ = CreateBtnObj(renderer, { "OPTIONS",primaryFont,white }, grey, { posx,posy += btnH * 1.3,btnW,btnH });
    GameObject* quitBtn_ = CreateBtnObj(renderer, { "QUIT",primaryFont,white }, red, { posx,posy += btnH * 1.3,btnW,btnH });

    SDL_Texture* texture = WriteText(renderer, titleFont, "CHESS", white);
    GameObject* test = new GameObject{ texture, new SDL_Rect{ CalcPadding(WIDTH,300),50,300,100 },-10 };

    startScene.objects["playButton"] = playBtn_;
    startScene.objects["optionButton"] = optBtn_;
    startScene.objects["quitButton"] = quitBtn_;
    startScene.objects["test"] = test;


    startScene.displayObjects[playBtn_] = true;
    startScene.displayObjects[optBtn_] = true;
    startScene.displayObjects[quitBtn_] = true;
    startScene.displayObjects[test] = true;

    TTF_CloseFont(primaryFont);
    TTF_CloseFont(titleFont);
}
void LoopStartScene() {
    for (auto const& [key, value] : startScene.objects) {
        if (startScene.displayObjects.at(value)) SDL_RenderCopyEx(renderer, value->texture, NULL, value->pos, value->angle, NULL, SDL_FLIP_NONE);
    }
}

void EventStartScene(SDL_Event* event) {

}

void CleanStartScene() {
    startScene.displayObjects.clear();
    for (auto const& [key, value] : startScene.objects) {
        SDL_DestroyTexture(value->texture);
        delete value->pos;
        delete value;
    }
}

int main(int argc, char* argv[]) {
    window = InitWindow();
    InitDriver(window);
    renderer = InitRenderer(window);

    InitStartScene();

    MainLoop(LoopStartScene, EventStartScene);

    CleanStartScene();
    CleanUp();

    return 0;
}

SDL_Window* InitWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Window* wind = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);

    if (!wind) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    return wind;
}
void InitDriver(SDL_Window* window) {
    if (TTF_Init() < 0) {
        printf("%s", TTF_GetError());
        CleanUp();
        exit(1);
    }

    if (IMG_Init(63) == 0) {
        std::cout << "Error Init Image" << std::endl;
        CleanUp();
        exit(1);
    }

    // Setup icon
    SDL_Surface* surface = IMG_Load("./assets/image/icon.png");
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}
SDL_Renderer* InitRenderer(SDL_Window* window) {
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!rend) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }

    return rend;
}

void MainLoop(void(*loopFunc)(), void(*eventFunc)(SDL_Event* event)) {
    SDL_Event event;

    while (running) {
        SDL_Delay(1000 / FPS);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        loopFunc();

        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                continue;
            }
            eventFunc(&event);
        }
    }
}
void CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}