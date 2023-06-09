#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class Model
{
   public:
    Model() = default;
    explicit Model(const std::string &path);
    [[nodiscard]] const std::vector<sf::Vector3f>& GetVertices() const;
    void SetVertices(std::vector<sf::Vector3f> vertices);
    [[nodiscard]] const std::vector<sf::Vector3i>& GetFaces() const;
    void SetFaces(std::vector<sf::Vector3i> faces);
   private:
    std::vector<sf::Vector3f> vertices_;
    std::vector<sf::Vector3i> faces_;
};
