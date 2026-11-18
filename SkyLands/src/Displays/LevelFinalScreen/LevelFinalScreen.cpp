#include "LevelFinalScreen.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Game/GameState.h"
#include "../Utils/DrawImage.h"

const sf::Vector2f BUTTON_SCALE = {1.0f, 1.0f};
const sf::Vector2f BUTTON_HOME_POSITION = {200.0f, 400.0f};
const sf::Vector2f BUTTON_LEVEL_POSITION = {425.0f, 400.0f};

const sf::Vector2f IMAGE_SCALE = {2.0f, 2.0f};
const sf::Vector2f IMAGE_POSITION = {200.0f, 0.0f};

LevelFinalScreen::LevelFinalScreen() 
    : m_toHomeButton(m_toHomeButtonTexture),
      m_restartButton(m_restartButtonTexture),
      m_screenImage(m_victoryTexture)
{
    if (!m_toHomeButtonTexture.loadFromFile("../assets/to_home_button.png")) {
        return;
    }

    if (!m_restartButtonTexture.loadFromFile("../assets/to_restart_button.png")) {
        return;
    }

    if (!m_defeatTexture.loadFromFile("../assets/defeat_image.png")) {
        return;
    }

    if (!m_victoryTexture.loadFromFile("../assets/victory_image.png")) {
        return;
    }

    m_toHomeButton.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_toHomeButtonTexture.getSize())));
    m_restartButton.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_restartButtonTexture.getSize())));
}

void LevelFinalScreen::RenderDisplay(sf::RenderWindow& window, GameState gameState)
{
    if (gameState == victoryState) {
        m_screenImage.setTexture(m_victoryTexture);
        m_screenImage.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_victoryTexture.getSize())));
    }
    else if (gameState == defeatState) {
        m_screenImage.setTexture(m_defeatTexture);
        m_screenImage.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_defeatTexture.getSize())));
    }

    DrawImage(m_toHomeButton, BUTTON_SCALE, BUTTON_HOME_POSITION, window);
    DrawImage(m_restartButton, BUTTON_SCALE, BUTTON_LEVEL_POSITION, window);
    DrawImage(m_screenImage, IMAGE_SCALE, IMAGE_POSITION, window);
}

GameState LevelFinalScreen::HandleLevelFinalStateChange(
    const sf::Event::MouseButtonPressed* mousePressed, 
    sf::RenderWindow* window,
    GameState currentState,
    Level &level
) {
    if (mousePressed) {
        if (mousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f pos = window->mapPixelToCoords(mousePressed->position);

            if (m_toHomeButton.getGlobalBounds().contains(pos)) {
                return homeState;
            }

            if (m_restartButton.getGlobalBounds().contains(pos)) {
                int id = level.GetId();
                level.Init(id);
                return levelState;
            }
        }
    }

    return currentState;
}