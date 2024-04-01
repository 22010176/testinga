#include "Sprite.h"

Sprite::Sprite(SDL_Rect& rect, SDL_Color& color, double angle) : width(rect.w), height(rect.h), angle(angle) {
    SDL_Renderer* renderer = Renderer::Get().GetRenderer();
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
    AddTexture(&rect, color, { 0,0,rect.w,rect.h });
}

Sprite::Sprite(SDL_Surface& surface, double angle) : width(surface.w), height(surface.h), angle(angle) {
    SDL_Renderer* renderer = Renderer::Get().GetRenderer();
    this->texture = SDL_CreateTextureFromSurface(renderer, &surface);
}

Sprite::Sprite(SDL_Texture* texture, double angle) : angle(angle) {
    SDL_QueryTexture(texture, nullptr, nullptr, &this->width, &this->height);

    SDL_Renderer* renderer = Renderer::Get().GetRenderer();
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->width, this->height);
    AddTexture(texture, { 0,0,this->width,this->height });
}

Sprite::~Sprite() { SDL_DestroyTexture(this->texture); }

void Sprite::SetDisplay(bool val) { this->display = val; }
void Sprite::SetAngle(double val) { this->angle = val; }

void Sprite::AddTexture(SDL_Texture* texture, SDL_Rect pos) {
    SDL_Renderer* renderer = Renderer::Get().GetRenderer();
    SDL_SetRenderTarget(renderer, this->texture);
    SDL_RenderCopy(renderer, texture, NULL, &pos);
    SDL_SetRenderTarget(renderer, nullptr);
}
void Sprite::AddTexture(SDL_Surface* surface, SDL_Rect pos) {
    SDL_Renderer* renderer = Renderer::Get().GetRenderer();
    SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, surface);
    AddTexture(temp, pos);
}
void Sprite::AddTexture(SDL_Rect* rect, SDL_Color color, SDL_Rect pos) {
    SDL_Renderer* renderer = Renderer::Get().GetRenderer();
    SDL_SetRenderTarget(renderer, this->texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &pos);
    SDL_SetRenderTarget(renderer, nullptr);
}

bool Sprite::operator==(const Sprite& other) { return this->texture == other.texture; }