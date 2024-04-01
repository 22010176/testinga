#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../Constant.h"


// Apply Singleton
class Renderer {
private:
    static Renderer instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Renderer();

public:
    Renderer(const Renderer&) = delete;
    static Renderer& Get() { return instance; }

    void ClearScene() const;
    SDL_Renderer* GetRenderer() const { return Renderer::Get().renderer; }
    SDL_Window* GetWindow() const { return Renderer::Get().window; }
    ~Renderer();
};

