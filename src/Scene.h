#pragma once

#include <string>
#include <map>
#include <functional>

#include <SDL2/SDL.h>

#include "Sprite.h"

class Scene {
private:
    std::map <std::string, Sprite*> objects;
    std::map <uint32_t, std::function<void(SDL_Event*)>> events;

    virtual void MainLoop() = 0;
    virtual void Event() = 0;

public:
    Scene(const Scene& scene) = delete;
    Scene() {}

    std::map<std::string, Sprite*>& GetObjects() { return objects; }
    std::map<uint32_t, std::function<void(SDL_Event* e)>>& GetEvents() { return events; }
};