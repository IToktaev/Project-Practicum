#include "Menu.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Game/GameState.h"
#include <iostream>
#include "../Utils/DrawImage.h"

const sf::Vector2f BUTTON_SCALE = {1.0f, 1.0f};
const sf::Vector2f BUTTON_HOME_POSITION = {225.0f, 0.0f};
const sf::Vector2f BUTTON_LEVEL_POSITION = {225.0f, 250.0f};

Menu::Menu() 
    : m_toHomeButton(m_toHomeButtonTexture),
      m_toLevelButton(m_toLevelButtonTexture)
{
    if (!m_toHomeButtonTexture.loadFromFile("../assets/to_home_button.png")) {
        return;
    }

    if (!m_toLevelButtonTexture.loadFromFile("../assets/to_level_button.png")) {
        return;
    }

    m_toHomeButton.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_toHomeButtonTexture.getSize())));
    m_toLevelButton.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_toLevelButtonTexture.getSize())));
}

void Menu::RenderMenu(sf::RenderWindow& window) {
    DrawImage(m_toHomeButton, BUTTON_SCALE, BUTTON_HOME_POSITION, window);
    DrawImage(m_toLevelButton, BUTTON_SCALE, BUTTON_LEVEL_POSITION, window);
}

GameState Menu::HandleMenuStateChange(
    const sf::Event::MouseButtonPressed* mousePressed, 
    sf::RenderWindow* window,
    GameState currentState
) {
    if (mousePressed) {
        if (mousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f pos = window->mapPixelToCoords(mousePressed->position);

            if(m_toHomeButton.getGlobalBounds().contains(pos)) {
                return homeState;
            }

            if(m_toLevelButton.getGlobalBounds().contains(pos)) {
                return levelState;
            }
        }
    }

    return currentState;
}