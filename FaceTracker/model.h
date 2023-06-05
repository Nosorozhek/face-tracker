#pragma once

#include <string>
#include <vector>

#include "structs.h"

class Model
{
   private:
    std::vector<Vector3F> vertexes_;
    std::vector<Face> faces_;
public:
    Model(std::string path);
};
