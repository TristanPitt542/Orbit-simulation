#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;


constexpr int kScreenWidth{ 1600 };
constexpr int kScreenHeight{ 1000 };

void Game::FrontEnd()
{
    sf::Font font;

    if (!font.loadFromFile("Data/Fonts/menu_font.ttf"))
    {
        cout << "Error loading font" << endl;
        return;
    }
    //title
    sf::Text title("Main Menu", font, 50);
    title.setPosition((float)kScreenWidth / 2 + 30, 100);
    title.setOrigin(250, 25);
    title.setCharacterSize(75);

    //playbutton and play text
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition((float)kScreenWidth / 2, 300);
    playButton.setOrigin(100, 25);
 
    sf::Text playButtonText("Play", font, 30);
    playButtonText.setPosition((float)kScreenWidth / 2 - 50, 280);
    playButtonText.setColor(sf::Color::White);

//=========================================================================//

    //quit button and quit text 
    sf::RectangleShape quitButton(sf::Vector2f(200, 50));
    quitButton.setFillColor(sf::Color::Red);
    quitButton.setPosition((float)kScreenWidth / 2, 500);
    quitButton.setOrigin(100, 25);

    sf::Text quitButtonText("Quit", font, 30);
    quitButtonText.setPosition((float)kScreenWidth / 2 - 50, 480);
    quitButtonText.setColor(sf::Color::White);


    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
                m_state = GameState::Exit;  // Set the state to exit gracefully
                return;
            }
        }
        //button pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
            sf::FloatRect playbounds = playButton.getGlobalBounds();
            sf::FloatRect quitbounds = quitButton.getGlobalBounds();
            if (playbounds.contains(mousePos.x, mousePos.y))
            {
                m_window->clear();
                m_state = GameState::Playing;
                return;
            }
            else if (quitbounds.contains(mousePos.x, mousePos.y))
            {
                m_window->clear();
                m_state = GameState::Exit;
                return;
            }
        }

        m_window->clear();

        m_window->draw(title);
        m_window->draw(playButton);
        m_window->draw(playButtonText);
        m_window->draw(quitButton);
        m_window->draw(quitButtonText);

        m_window->display();
    }
}

void Game::Play()
{
    sf::Font font;

    std::vector<GravitySource> sources;

    sources.push_back(GravitySource(sf::Vector2f(500, 500), 7000));
    sources.push_back(GravitySource(sf::Vector2f(1200, 500), 7000));

    //sources.push_back(GravitySource(sf::Mouse().getPosition().x, sf::Mouse().getPosition().y, 500));
    
    int num_spaceships = 20;
    std::vector<Particle> spaceshipvec;

    for (int i = 0; i < num_spaceships; i++)
    {
        spaceshipvec.push_back(Particle(600, 700, 4, 0.2 + (0.1 / num_spaceships) * i));
    }

    while (m_window->isOpen())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
                m_state = GameState::Exit;  // Set the state to exit gracefully
                return;
            }
        }

        m_window->clear();

        //update
        for (int i = 0; i < sources.size(); i++)
        {
            for (int j = 0; j < spaceshipvec.size(); j++)
            {
                spaceshipvec[j].Update(sources[i]);
            }
        }


        //render planets
        for (int i = 0; i < sources.size(); i++)
        {
            sources[i].Render(*m_window);
        }

        //render spaceships
        for (int j = 0; j < spaceshipvec.size(); j++)
        {
            spaceshipvec[j].Render(*m_window);
        }

        m_window->display();
    }

    return;
}

void Game::Run()
{
    std::cout << "SPACE SIMULATION" << std::endl;

    m_window = new sf::RenderWindow(sf::VideoMode(kScreenWidth, kScreenHeight), "Real  simulation : C2460536");
    //randomize
    srand((unsigned)time(0));

    sf::Music music;

    if (!music.openFromFile("Data/Music/retro_music.ogg"))
    {
        cout << "Error loading music" << endl;
        return;
    }
    music.play();
    music.setLoop(true);
    music.setVolume(1.5f);

    m_window->setFramerateLimit(60);

    bool ShouldExit{ false };
    while (!ShouldExit)
    {
        switch (m_state)
        {
        case GameState::Waiting:
            FrontEnd();
            break;
            break;
        case GameState::Playing:
            Play();
            break;
        case GameState::Exit:
            Exit();
        default:
            FrontEnd();
        }
    }

    std::cout << "END" << std::endl;
};

//Exit function
void Game::Exit()
{
    exit(0);
}

