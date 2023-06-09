#include <SFML/OpenGL.hpp>

#include "app.h"

void App::RenderModel() {
    // Process events
    sf::Event event;
    while (window_.pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed) window_.close();

        // Escape key : exit
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape)
            window_.close();
    }

    const std::vector<sf::Vector3f> vertices = obtained_model_.GetVertices();
    const std::vector<sf::Vector3i> faces = obtained_model_.GetFaces();

    // Clear screen with (0.2f, 0.3f, 0.3f, 1.0f) color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering model
    glBegin(GL_TRIANGLES);
    for (auto face : faces)
    {
        glColor3i(0, 1, 1);
        glVertex3f(vertices[face.x].x, vertices[face.x].y, vertices[face.x].z);
        glVertex3f(vertices[face.y].x, vertices[face.y].y, vertices[face.y].z);
        glVertex3f(vertices[face.z].x, vertices[face.z].y, vertices[face.z].z);
    }
    glEnd();

    window_.display();
}