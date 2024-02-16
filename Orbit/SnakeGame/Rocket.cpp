#include "Rocket.h"

Rocket::Rocket(sf::Vector2f r_velocity, sf::Color col, float rot) : r_velocity(r_velocity) , r_colour(col), r_rotation(rot)
{
}

void Rocket::Render(sf::RenderWindow& window)
{
    sf::RectangleShape rocket;

    rocket.setSize(sf::Vector2f(50, 25));
    rocket.setPosition(r_velocity);
    rocket.setFillColor(r_colour);
    rocket.setOrigin(sf::Vector2f(25,12.5f));
    rocket.setRotation(r_rotation);

	window.draw(rocket);
};

void Rocket::Update()
{
    if (r_rotation < 0)
    {
        r_rotation = 360;
    }
    else if (r_rotation > 360)
    {
        r_rotation = 0;
    }
    // Update spaceship position based on user input (e.g., arrow keys)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        r_rotation -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        r_rotation += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sf::Vector2f direction = sf::Vector2f(std::cos(r_rotation * 3.14159265 / 180), std::sin(r_rotation * 3.14159265 / 180));
        r_velocity += r_speed * direction;
    }
}
