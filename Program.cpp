#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
// #include "Scene.h"

#include "Constant.h"
#include "Utilities.h"

bool isRunning = true;
int main(int argc, char* argv[]) {
    SDL_Event event;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
        }
    }

    return 0;
}

