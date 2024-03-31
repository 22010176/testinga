#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "Scene.h"
#include "Constant.h"
#include "Utilities.h"

SDL_Window* InitWindow();
void InitDriver(SDL_Window* window);
SDL_Renderer* InitRenderer(SDL_Window* window);

void MainLoop(void(*loopFunc)(SDL_Renderer*), void(*eventFunc)(SDL_Event* event));
void CleanUp();

// global window's objects
SDL_Window* window;
SDL_Renderer* renderer;
bool running = true, mouseClick = false;
SDL_Point mousePos;

Scene startScene;
void InitStartScene() {
    TTF_Font* primaryFont = TTF_OpenFont("./assets/font/SourceCodePro-SemiBold.ttf", 40);
    TTF_Font* titleFont = TTF_OpenFont("./assets/font/SourceCodePro-ExtraBold.ttf", 100);
    int btnW = 250, btnH = 65, posx = CalcPadding(WIDTH, btnW), posy = CalcPadding(HEIGHT, btnH) + btnH;

    Object playBtn;
    playBtn.objects["normal"] = CreateBtnObj(renderer, { "PLAY",primaryFont,white }, green, { posx,posy,btnW,btnH });
    playBtn.objects["hover"] = CreateBtnObj(renderer, { "PLAY",primaryFont,white }, darkGreen, { posx,posy,btnW,btnH });
    playBtn.SetStage("normal");

    Object optBtn;
    optBtn.objects["normal"] = CreateBtnObj(renderer, { "OPTIONS",primaryFont,white }, grey, { posx,posy += btnH * 1.3,btnW,btnH });
    optBtn.objects["hover"] = CreateBtnObj(renderer, { "OPTIONS",primaryFont,white }, darkGrey, { posx,posy,btnW,btnH });
    optBtn.SetStage("normal");

    Object quitBtn;
    quitBtn.objects["normal"] = CreateBtnObj(renderer, { "QUIT",primaryFont,white }, red, { posx,posy += btnH * 1.3,btnW,btnH });
    quitBtn.objects["hover"] = CreateBtnObj(renderer, { "QUIT",primaryFont,white }, darkRed, { posx,posy,btnW,btnH });
    quitBtn.SetStage("normal");

    SDL_Texture* texture = WriteText(renderer, titleFont, "CHESS", white);

    GameObject test = GameObject(texture, { CalcPadding(WIDTH,500),50,500,200 }, -10);
    GameObject dev = GameObject(DisplayImage(renderer, "./assets/image/icon.png"), { WIDTH - 100 - 10,10,100,100 });

    startScene.objects["playButton"] = playBtn;
    startScene.objects["optionButton"] = optBtn;
    startScene.objects["quitButton"] = quitBtn;

    startScene.objects["logo"] = test;
    startScene.objects["devPic"] = dev;

    TTF_CloseFont(primaryFont);
    TTF_CloseFont(titleFont);
}
void LoopStartScene(SDL_Renderer* renderer) {
    for (auto const& [key, value] : startScene.objects) {
        value.Display(renderer);
    }
}

void EventStartScene(SDL_Event* event) {
    std::vector<std::string> trackHovers;
    if (!mouseClick) {
        for (auto& [key, value] : startScene.objects) {
            if (!(value.display && CheckCollide(&value.pos, &mousePos))) continue;
        }
    }
}

void FreeStartScene() {

}

int main(int argc, char* argv[]) {
    window = InitWindow();
    InitDriver(window);
    renderer = InitRenderer(window);

    InitStartScene();

    MainLoop(LoopStartScene, EventStartScene);

    // FreeStartScene();
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

void MainLoop(void(*loopFunc)(SDL_Renderer*), void(*eventFunc)(SDL_Event* event)) {
    SDL_Event event;

    while (running) {
        SDL_Delay(1000 / FPS);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        loopFunc(renderer);

        SDL_RenderPresent(renderer);

        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                continue;
            }
            switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                mouseClick = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseClick = false;
                break;
            default:
                break;
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