#include "Renderer.h"

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cout << "Fail intitial SDL!" << std::endl;
        exit(-1);
    }

    Renderer::window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    Renderer::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!Renderer::renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-1);
    }

    if (TTF_Init() < 0) {
        printf("%s", TTF_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);

        SDL_Quit();
        exit(1);
    }

    if (IMG_Init(63) == 0) {
        std::cout << "Error Init Image" << std::endl;
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);

        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    if (Mix_Init(MIX_INIT_FLAC) == 0) {
        std::cout << Mix_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    // Setup icon
    SDL_Surface* surface = IMG_Load("./assets/image/icon.png");
    std::cout << "test:" << surface << std::endl;

    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    std::cout << "Good" << std::endl;
}

void Renderer::ClearScene() const {
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

Renderer Renderer::instance;