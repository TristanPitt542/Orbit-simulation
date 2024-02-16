#pragma once
#include <SFML/Graphics.hpp>
#include "Gravity.h"

class Particle
{
private:

    sf::Vector2f position;
    sf::Vector2f velocity;

    float rotation;

    static constexpr float G = 0.01f;

public:
    Particle(float pos_x, float pos_y, float vel_x, float vel_y);
   
    void Render(sf::RenderWindow& window);

    void Update(GravitySource& s);
};