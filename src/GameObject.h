#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

struct GameObject {
    SDL_Texture* texture;
    SDL_Rect pos;
    double angle;
    bool display;

    GameObject(SDL_Texture* texture = nullptr, SDL_Rect rect = {}, double angle = 0, bool display = true) {
        this->texture = texture;
        this->pos = rect;
        this->angle = angle;
        this->display = display;
    }
    ~GameObject() {
        SDL_DestroyTexture(texture);
        std::cout << "delete" << std::endl;
    }

    void Display(SDL_Renderer* renderer) const {
        if (!this->display) return;
        SDL_RenderCopyEx(renderer, texture, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
    }
    virtual void SetStage(std::string) {};
};

struct Object : public GameObject {
    std::map<std::string, GameObject> objects{};
    Object() {}

    void SetStage(std::string key) {
        if (this->objects.find(key) == this->objects.end()) return;
        GameObject test = objects.at(key);

        this->angle = test.angle;
        this->pos = test.pos;
        this->texture = test.texture;
    }
    ~Object() {
        for (auto const& [key, value] : objects) {
            SDL_DestroyTexture(value.texture);
        }
    }
};