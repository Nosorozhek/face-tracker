#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "model.h"

// Load model from .obj file
Model::Model(const std::string &path)
{
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
        // Check for vertices
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

            int a,b,c,d;
            char t;
            f >> a;
            f >> t;
            f >> t;
            f >> d;
            f >> b;
            f >> t;
            f >> t;
            f >> d;
            f >> c;
            f >> t;
            f >> t;
            f >> d;
            sf::Vector3i face = {--a, --b, --c};
            faces_.push_back(face);
        }
    }
}

const std::vector<sf::Vector3f>& Model::GetVertices() const { return vertices_; }

void Model::SetVertices(std::vector<sf::Vector3f> vertices) { vertices_ = std::move(vertices); }

const std::vector<sf::Vector3i>& Model::GetFaces() const { return faces_; }

void Model::SetFaces(std::vector<sf::Vector3i> faces) { faces_ = std::move(faces); }
