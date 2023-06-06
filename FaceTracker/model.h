#pragma once

#include <string>
#include <vector>

#include "structs.h"

class Model
{
   private:
    std::vector<Vector3F> vertices_;
    std::vector<Face> faces_;
public:
    Model();
    Model(std::string path);
};
