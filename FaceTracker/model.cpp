#include "model.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Default constructor
Model::Model()
{
    vertices_ = std::vector<sf::Vector3f>();
    faces_ = std::vector<sf::Vector3i>();
}

// Load model from .obj file
Model::Model(const std::string &path)
{
    vertices_ = std::vector<sf::Vector3f>();
    faces_ = std::vector<sf::Vector3i>();

    // Open .obj file
    std::ifstream file(path, std::ios::in);
    if (!file)
    {
        std::cout << "Cannot open " << path << std::endl;
    }

    // Read file line by line
    std::string line;
    while (std::getline(file, line))
    {
        // Check for vertexes
        if (line.substr(0, 2) == "v ")
        {
            std::istringstream v(line.substr(2));

            float x, y, z;
            v >> x;
            v >> y;
            v >> z;
            sf::Vector3f vertex = {x, y, z};
            vertices_.push_back(vertex);
        }
        // Check for faces
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream f(line.substr(2));

            int a,b,c;
            f >> a;
            f >> b;
            f >> c;
            sf::Vector3i face = {a--, b--, c--};
            faces_.push_back(face);
        }
    }
}
