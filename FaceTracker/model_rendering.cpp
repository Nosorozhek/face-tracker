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

    // Prepare for drawing
    //  Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply some transformations for the cube
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -100.f);

    // Rendering model
    glBegin(GL_TRIANGLES);
    for (auto &face : faces)
    {
        glColor3f(0, 1, 1);
        glVertex3f(vertices[face.x].x, vertices[face.x].y, vertices[face.x].z);
        glVertex3f(vertices[face.y].x, vertices[face.y].y, vertices[face.y].z);
        glVertex3f(vertices[face.z].x, vertices[face.z].y, vertices[face.z].z);
    }
    glEnd();

    window_.display();
}