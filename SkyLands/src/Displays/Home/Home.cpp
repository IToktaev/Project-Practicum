#include "Home.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Game/GameState.h"
#include "../Utils/DrawImage.h"
#include "../../GlobalConstants/GlobalConstants.h"

const sf::Vector2f ICON_SCALE = {0.5f, 0.5f};
const sf::Vector2f FIRST_LEVEL_ICON_POSITION = {200.f, 350.f};
const sf::Vector2f SECOND_LEVEL_ICON_POSITION = {550.f, 220.f};
const sf::Vector2f THIRD_LEVEL_ICON_POSITION = {330.f, 30.f};

Home::Home()
    : m_background(m_backgroundTexture),
      m_levelFirstIcon(m_levelFirstIconTexture),
      m_levelSecondIcon(m_levelSecondIconTexture),
      m_levelThirdIcon(m_levelThirdIconTexture),
      m_secondIconLocked(m_chainsDarkTexture),
      m_thirdIconLocked(m_chainsLightTexture)
{
    if (!m_backgroundTexture.loadFromFile("../assets/home.png")) {
        return;
    }

    if (!m_levelFirstIconTexture.loadFromFile("../assets/level_1_icon.png")) {
        return;
    }
    
    if (!m_levelSecondIconTexture.loadFromFile("../assets/level_2_icon.png")) {
        return;
    }

    if (!m_levelThirdIconTexture.loadFromFile("../assets/level_3_icon.png")) {
        return;
    }

    if (!m_chainsLightTexture.loadFromFile("../assets/chains_light.png")) {
        return;
    }

    if (!m_chainsDarkTexture.loadFromFile("../assets/chains_dark.png")) {
        return;
    }

    m_background.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_backgroundTexture.getSize())));
    m_levelFirstIcon.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_levelFirstIconTexture.getSize())));
    m_levelSecondIcon.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_levelSecondIconTexture.getSize())));
    m_levelThirdIcon.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_levelThirdIconTexture.getSize())));

    m_secondIconLocked.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_chainsDarkTexture.getSize())));
    m_thirdIconLocked.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_chainsLightTexture.getSize())));
}

void Home::RenderHome(sf::RenderWindow& window, int lastOpenedLevel) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = m_backgroundTexture.getSize();

    DrawImage(m_background, {
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    }, {0, 0}, window);

    DrawImage(m_levelFirstIcon, ICON_SCALE, FIRST_LEVEL_ICON_POSITION, window);
    DrawImage(m_levelSecondIcon, ICON_SCALE, SECOND_LEVEL_ICON_POSITION, window);
    DrawImage(m_levelThirdIcon, ICON_SCALE, THIRD_LEVEL_ICON_POSITION, window);

    if (lastOpenedLevel < SECOND_LEVEL) {
        DrawImage(m_secondIconLocked, ICON_SCALE, SECOND_LEVEL_ICON_POSITION, window);
    }

    if (lastOpenedLevel < THIRD_LEVEL) {
        DrawImage(m_thirdIconLocked, ICON_SCALE, THIRD_LEVEL_ICON_POSITION, window);
    }
}

GameState Home::HandleHomeStateChange(
    const sf::Event::MouseButtonPressed* mousePressed, 
    sf::RenderWindow* window,
    GameState currentState,
    Level& level,
    int lastOpenedLevel
) {
    if (mousePressed) {
        if (mousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f pos = window->mapPixelToCoords(mousePressed->position);

            if (m_levelFirstIcon.getGlobalBounds().contains(pos)) {
                level.Init(FIRST_LEVEL);
                return levelState;
            } else if (m_levelSecondIcon.getGlobalBounds().contains(pos) && lastOpenedLevel > FIRST_LEVEL) {
                level.Init(SECOND_LEVEL);
                return levelState;
            } else if (m_levelThirdIcon.getGlobalBounds().contains(pos) && lastOpenedLevel > SECOND_LEVEL) {
                level.Init(THIRD_LEVEL);
                return levelState;
            }
        }
    }

    return currentState;
}