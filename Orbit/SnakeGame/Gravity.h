#pragma once
#include <SFML/Graphics.hpp>

class GravitySource
{
private:
    sf::Vector2f m_position;
    float m_mass;

public:
    GravitySource(sf::Vector2f position, float mass);

    void Render(sf::RenderWindow& window);


    sf::Vector2f GetPos() { return m_position; };

    float GetMass() { return m_mass; };

};