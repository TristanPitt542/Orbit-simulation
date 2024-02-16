#include "Spaceship.h"
#include <iostream>

#define M_PI acos(-1.0);

Particle::Particle(float pos_x, float pos_y, float vel_x, float vel_y)
{
    position.x = pos_x;
    position.y = pos_y;

    velocity.x = vel_x;
    velocity.y = vel_y;
}

void Particle::Render(sf::RenderWindow& window)
{
    sf::CircleShape triangle(25, 3);
    triangle.setOrigin(12.5, 12.5);
    triangle.setScale(1, 2);
    triangle.setPosition(position);
    triangle.setFillColor(sf::Color::White);
   
    triangle.setRotation(rotation);
    
    window.draw(triangle);

}

void Particle::Update(GravitySource& s)
{
    float distance_x = s.GetPos().x - position.x;
    float distance_y = s.GetPos().y - position.y;

    float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

    float inverse_distance = 1.f / distance;

    float normalized_x = inverse_distance * distance_x;
    float normalized_y = inverse_distance * distance_y;

    float inverse_square_dropoff = inverse_distance * inverse_distance;

    float acceleration_x = (normalized_x * s.GetMass() * inverse_square_dropoff);
    float acceleration_y = (normalized_y * s.GetMass() * inverse_square_dropoff);

    velocity.x += acceleration_x;
    velocity.y += acceleration_y;

    position.x += velocity.x;
    position.y += velocity.y;
   
    //rotaiton
    rotation = atan2(velocity.y, velocity.x) * 360 / M_PI;

    if (rotation < 0) {
        rotation += 360;
    }


 /*   if (pos.x >= 1600)
    {
        pos.x = 0;
    }
    else if (pos.x <= 0)
    {
        pos.x = 1600;
    }

    if (pos.y >= 1000)
    {
        pos.y = 0;
    }
    else if (pos.y <= 0)
    {
        pos.y = 1000;
    }*/
}