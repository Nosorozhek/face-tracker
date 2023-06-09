#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Model
{
   public:
    Model();
    Model(const std::string &path);
   private:
    std::vector<sf::Vector3f> vertices_;
    std::vector<sf::Vector3i> faces_;
};
