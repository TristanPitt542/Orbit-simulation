#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Gravity.h"
#include "Spaceship.h"

using namespace std;

class Particle;
class Gravity;

enum GameState
{
	Waiting,
	Settings,
	Playing,
	HighScore,
	GameOver,
	Exit
};


class Game
{
private:
	GameState m_state{ GameState::Waiting };

	sf::RenderWindow* m_window{ nullptr };

	vector<sf::RenderWindow> window;

public:
	void FrontEnd();
	void Play();
	void Run();
	void Exit();
};