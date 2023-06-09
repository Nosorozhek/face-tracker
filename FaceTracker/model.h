#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Model
{
   public:
    Model();
    Model(const std::string &path);
    std::vector<sf::Vector3f> GetVertices();
    void SetVertices(std::vector<sf::Vector3f> vertices);
    std::vector<sf::Vector3i> GetFaces();
    void SetFaces(std::vector<sf::Vector3i> faces);
   private:
    std::vector<sf::Vector3f> vertices_;
    std::vector<sf::Vector3i> faces_;
};
