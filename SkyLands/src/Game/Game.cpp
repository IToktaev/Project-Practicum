#include "Game.h"
#include <algorithm>
#include <iostream>

const float FLOOR_Y = 700.0f;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game()
    :   m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SkyLands"),
        m_currentState(homeState)
{

}

void Game::RenderHome() {
    sf::RectangleShape rectLevel1({200.f, 50.f});
    rectLevel1.setPosition({100.f, 100.f});
    rectLevel1.setFillColor(sf::Color::Red);

    sf::RectangleShape rectLevel2({200.f, 50.f});
    rectLevel2.setPosition({100.f, 200.f});
    rectLevel2.setFillColor(sf::Color::Blue);

    sf::RectangleShape rectLevel3({200.f, 50.f});
    rectLevel3.setPosition({100.f, 300.f});
    rectLevel3.setFillColor(sf::Color::Green);

    m_window.draw(rectLevel1);
    m_window.draw(rectLevel2);
    m_window.draw(rectLevel3);
}

void Game::Run() {
    while (m_window.isOpen()) {
        float dt = m_clock.restart().asSeconds();

        while (const std::optional event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }

            if (m_currentState == homeState) {
                if (
                    const sf::Event::MouseButtonPressed* mousePressed =
                    event->getIf<sf::Event::MouseButtonPressed>()
                ) {
                    if (mousePressed->button == sf::Mouse::Button::Left) {
                        sf::Vector2f pos = m_window.mapPixelToCoords(mousePressed->position);

                        if (sf::FloatRect({100.f, 100.f}, {200.f, 50.f}).contains(pos)) {
                            m_currentState = levelState;
                            m_level.Init(1);
                        } else if (sf::FloatRect({100.f, 200.f}, {200.f, 50.f}).contains(pos)) {
                            m_currentState = levelState;
                            m_level.Init(2);
                        } else if (sf::FloatRect({100.f, 300.f}, {200.f, 50.f}).contains(pos)) {
                            m_currentState = levelState;
                            m_level.Init(3);
                        }
                    }
                }
            }

            if (m_currentState == menuState) {
                if (
                    const sf::Event::MouseButtonPressed* mousePressed =
                    event->getIf<sf::Event::MouseButtonPressed>()
                ) {
                    if (mousePressed->button == sf::Mouse::Button::Left) {
                        sf::Vector2f pos = m_window.mapPixelToCoords(mousePressed->position);

                        if(sf::FloatRect({100.f, 100.f}, {200.f, 50.f}).contains(pos)) {
                            m_currentState = homeState;
                            std::cout << "To Home\n";
                        }

                        if(sf::FloatRect({100.f, 200.f}, {200.f, 50.f}).contains(pos)) {
                            m_currentState = levelState;
                            std::cout << "Back to level\n";
                        }
                    }
                }
            }

            if (m_currentState == levelState) {
                m_currentState = m_level.HandleLevelStateChange();
            }
        }

        m_window.clear(sf::Color::Black);

        if (m_currentState == homeState) {
            m_window.setView(m_window.getDefaultView());
            RenderHome();
        } else if (m_currentState == menuState) {
            m_window.setView(m_window.getDefaultView());
            m_menu.RenderMenu(m_window);
        } else if (m_currentState == levelState) {
            m_level.Update(dt);
            m_level.Draw(m_window);
        }

        m_window.display();
    }
}
