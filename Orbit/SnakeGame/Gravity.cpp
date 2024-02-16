#include "Gravity.h"

GravitySource::GravitySource(sf::Vector2f position, float mass)
{
    m_position = position;
    this->m_mass = mass;
}

void GravitySource::Render(sf::RenderWindow& window)
{
    sf::CircleShape a;
    a.setPosition(m_position);
    a.setFillColor(sf::Color(125, 125, 125, 255));
    a.setRadius(m_mass / 100);
    a.setOrigin(a.getRadius(), a.getRadius());

    window.draw(a);
}
