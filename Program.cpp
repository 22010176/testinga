#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "Utilities.h"

#define WIDTH               1280
#define HEIGHT              720
#define FPS                 120

SDL_Window* Init();
void InitDriver(SDL_Window* window);
SDL_Renderer* InitRenderer(SDL_Window* window);
void MainLoop(std::function<void(SDL_Renderer*)>& loopFunc, std::function<void(SDL_Event*)>& eventFunc);
void CleanUp();

SDL_Window* window;
SDL_Renderer* renderer;

TTF_Font* gSemiBold;

class GameObject {
private:
    SDL_Texture* texture;
    SDL_Rect position;
public:
    GameObject(SDL_Texture* texture, SDL_Rect position) : texture(texture), position(position) {}
    GameObject(SDL_Renderer* renderer, SDL_Rect position) : position(position) {
        this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, position.w, position.h);
    }
    GameObject(SDL_Renderer* renderer, SDL_Rect position, SDL_Color color) : position(position) {
        this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, position.w, position.h);

        SDL_Rect rect = { 0,0,position.w,position.h };
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderTarget(renderer, NULL);
    }
    GameObject(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Rect position) : position(position) {
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    ~GameObject() { SDL_DestroyTexture(texture); }

    void AddTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect localPosition) {
        SDL_SetRenderTarget(renderer, texture);
        SDL_RenderCopy(renderer, texture, NULL, &localPosition);
        SDL_SetRenderTarget(renderer, NULL);
    }
    void AddTexture(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Rect localPosition) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_SetRenderTarget(renderer, this->texture);
        SDL_RenderCopy(renderer, texture, NULL, &localPosition);
        SDL_SetRenderTarget(renderer, NULL);

        SDL_DestroyTexture(texture);
    }
    void AddTexture(SDL_Renderer* renderer, SDL_Rect localPosition, SDL_Color color) {
        SDL_SetRenderTarget(renderer, this->texture);
        SDL_RenderFillRect(renderer, &localPosition);
        SDL_SetRenderTarget(renderer, NULL);
    }

    SDL_Texture* GetTexture() const { return texture; }
    SDL_Rect GetHitbox() const { return position; }

    void Display(SDL_Renderer* renderer) const { SDL_RenderCopy(renderer, this->texture, NULL, &this->position); };
};

class Scene {
private:
    std::string name;
    std::map<std::string, GameObject*> objects;
public:
    Scene(std::string name) : name(name), objects({}) {}
    ~Scene() {
        for (std::pair<std::string, GameObject*> x : objects) delete x.second;
    }

    void AddTexture(std::string name, SDL_Texture* texture, SDL_Rect position) {
        GameObject* object = new GameObject(texture, position);
        this->AddTexture(name, object);
    }
    void AddTexture(std::string name, GameObject* gameObject) {
        this->objects[name] = gameObject;
    }

    void RemoveTexture(std::string name) {
        delete this->objects.at(name);
        this->objects.erase(name);
    }
    GameObject* GetGameObject(std::string name) { return this->objects.at(name); }

    std::function<void(SDL_Renderer* renderer)> MainLoop;
    std::function<void(SDL_Event* event)> EventListener;
};

int main(int argc, char* argv[]) {
    window = Init();
    InitDriver(window);
    renderer = InitRenderer(window);

    Scene startScene("startScene");

    startScene.MainLoop = [&](SDL_Renderer* renderer) {};
    startScene.EventListener = [&](SDL_Event* event) {

        };

    MainLoop(startScene.MainLoop, startScene.EventListener);

    /* Release resources */
    CleanUp();

    return 0;
}

SDL_Window* Init() {
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
        TTF_Quit();
        exit(1);
    }

    if (IMG_Init(63) == 0) {
        std::cout << "Error Init Image" << std::endl;
        IMG_Quit();
        exit(1);
    }

    // Setup icon
    SDL_Surface* surface = IMG_Load("./assets/image/icon.png");
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);

    gSemiBold = TTF_OpenFont("./assets/font/SourceCodePro-SemiBold.ttf", 40);
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

void MainLoop(std::function<void(SDL_Renderer*)>& loopFunc, std::function<void(SDL_Event*)>& eventFunc) {
    bool running = true;
    SDL_Event event;

    while (running) {
        SDL_Delay(1000 / FPS);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        loopFunc(renderer);

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
    TTF_CloseFont(gSemiBold);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}