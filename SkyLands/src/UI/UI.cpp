#include "UI.h"
#include <iostream>
#include "../../Utils/DrawImage.h"

const sf::Vector2f HEART_SCALE = {1.0f, 1.0f}; 
const float HEART_Y_POSITION = 20.0f;
const float HEART_X_OFFSET_SCALE = 20.0f;
const float HEART_X_OFFSET = 10.0f;

UI::UI() {
    if (!m_aliveHearthTexture.loadFromFile("../assets/alive_hearth.png")) {
        std::cerr << "Failed to load alive heart texture!\n";
        return;
    }

    if (!m_deadHearthTexture.loadFromFile("../assets/dead_hearth.png")) {
        std::cerr << "Failed to load dead heart texture!\n";
        return;
    }
}

void UI::RenderHealthBar(int lives, int maxLives, sf::RenderWindow& window) {
    if (m_hearts.size() < static_cast<size_t>(maxLives)) {
        m_hearts.resize(maxLives, sf::Sprite(m_aliveHearthTexture));
    }
    
    for (int i = 0; i < maxLives; i++) {
        if (i < lives) {
            m_hearts[i].setTexture(m_aliveHearthTexture);
            m_hearts[i].setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_aliveHearthTexture.getSize())));
        } else {
            m_hearts[i].setTexture(m_deadHearthTexture);
            m_hearts[i].setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(m_deadHearthTexture.getSize())));
        }

        DrawImage(
            m_hearts[i], 
            HEART_SCALE, 
            {static_cast<float>(i) * HEART_X_OFFSET_SCALE + HEART_X_OFFSET, HEART_Y_POSITION}, 
            window
        );
    }
}