#pragma once

#include <map>
#include <string>

#include <SDL2/SDL.h>

class GameObject {
private:
    std::map<std::string, SDL_Texture*> objects;
    SDL_Rect hitbox;
    unsigned int width, height;
public:
    GameObject();
    ~GameObject();
};

GameObject::GameObject(/* args */) {
}

GameObject::~GameObject() {
}
