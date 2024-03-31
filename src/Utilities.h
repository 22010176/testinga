#pragma once

#include <string>
#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "GameObject.h"

#define CalcPadding(width, innerWidth)          (((width) - (innerWidth)) / 2)



struct TextObj {
    std::string content;
    TTF_Font* font;
    SDL_Color color;
};

SDL_Texture* WriteText(SDL_Renderer* renderer, TTF_Font* font, std::string const message, SDL_Color color);
SDL_Texture* DrawRect(SDL_Renderer* renderer, int width, int height, SDL_Color color = { 255,255,255,255 });
SDL_Texture* DisplayImage(SDL_Renderer* renderer, std::string const path);

SDL_Texture* CreateBtnTex(SDL_Renderer* renderer, SDL_Texture* text, SDL_Color color, int width = 10, int height = 10);

GameObject CreateBtnObj(SDL_Renderer* renderer, TextObj text, SDL_Color color, SDL_Rect position);

// template <typename T> T CalcPadding(T width, T innerWidth);

std::vector<std::string> SplitStr(std::string s, std::string del = " ");

bool CheckCollide(SDL_Rect* pos, SDL_Point* point);