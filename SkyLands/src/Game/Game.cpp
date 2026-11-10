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

void Game::Run() {
    while (m_window.isOpen()) {
        float dt = m_clock.restart().asSeconds();

        while (const std::optional event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }

            if (m_currentState == homeState) {
                const sf::Event::MouseButtonPressed* mousePressed = 
                    event->getIf<sf::Event::MouseButtonPressed>();
                m_currentState = 
                    m_home.HandleHomeStateChange(mousePressed, &m_window, m_currentState, m_level);
            }

            if (m_currentState == menuState) {
                const sf::Event::MouseButtonPressed* mousePressed =
                    event->getIf<sf::Event::MouseButtonPressed>();
                m_currentState = m_menu.HandleMenuStateChange(mousePressed, &m_window, m_currentState);
            }

            if (m_currentState == levelState) {
                m_currentState = m_level.HandleLevelStateChange();
            }
        }

        m_window.clear(sf::Color::Black);

        if (m_currentState == homeState) {
            m_window.setView(m_window.getDefaultView());
            m_home.RenderHome(m_window);
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
