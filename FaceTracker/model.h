#pragma once

#include <string>
#include <vector>

#include "structs.h"

class Model
{
   private:
    std::vector<Point3f> vertexes_;
    std::vector<Polygon> polygons_;
public:
    Model(std::string path);
};
