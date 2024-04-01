#pragma once

#include <string>
#include <map>

#include <SDL2/SDL.h>

#include "Sprite.h"

class GameObject : public Sprite {
private:
    std::map<std::string, Sprite> sprites{};
    SDL_Point position;
public:
    void AddSprite(const std::string name, const Sprite sprite) { sprites.insert({ name,Sprite(sprite) }); }
    void RemoveSprite(const std::string& name) { sprites.erase(name); }
    void SetSprite(const std::string name) {
        if (sprites.find(name) == sprites.end()) return;
        operator=(sprites.at(name));
    }
    void SetPos(int x, int y) { position = { x,y }; }

    GameObject& operator=(const Sprite& other) {
        this->texture = other.texture;
        this->angle = other.angle;
        this->display = other.display;
        this->width = other.width;
        this->height = other.height;
    }
};