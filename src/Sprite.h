#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

#include "Renderer.h"

struct Sprite {
    SDL_Texture* texture = nullptr;
    int width, height;
    bool display = true;
    double angle = 0;

    Sprite(SDL_Rect& rect, SDL_Color& color, double angle = 0);
    Sprite(SDL_Surface& surface, double angle = 0);
    Sprite(SDL_Texture* texture, double angle = 0);
    ~Sprite();

    void AddTexture(SDL_Texture* texture, SDL_Rect pos);
    void AddTexture(SDL_Surface* surface, SDL_Rect pos);
    void AddTexture(SDL_Rect* rect, SDL_Color color, SDL_Rect pos);

    void SetDisplay(bool val = true);
    void SetAngle(double val = 0);

    bool operator==(const Sprite& others);
};
