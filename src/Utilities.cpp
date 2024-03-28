#include "Utilities.h"

SDL_Texture* WriteText(SDL_Renderer* renderer, TTF_Font* font, std::string const message, SDL_Color color) {
    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, message.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_FreeSurface(messageSurface);

    return texture;
}
SDL_Texture* DrawRect(SDL_Renderer* renderer, int width, int height, SDL_Color color) {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, *(int*)&color, surface->h * surface->pitch);
    SDL_UnlockSurface(surface);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}
SDL_Texture* DisplayImage(SDL_Renderer* renderer, std::string const path) {
    SDL_Surface* img = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    return texture;
}