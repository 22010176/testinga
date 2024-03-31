#pragma once

#include <string>
#include <map>

#include "GameObject.h"

struct Scene {
    std::map<std::string, GameObject> objects;
};
