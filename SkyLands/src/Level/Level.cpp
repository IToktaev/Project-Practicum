#include "Level.h"
#include <algorithm>
#include <iostream>

const float DEATH_BORDER = 900.0f;
const float VICTORY_BORDER = 1000.0f;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Level::Level()
    : m_view(sf::FloatRect(
        {0.0f, 0.0f},
        {WINDOW_WIDTH, WINDOW_HEIGHT}
    ))
{

}

void Level::Init(int levelId) {
    m_id = levelId;
    m_map.MapInit(levelId);
    m_player.Init();
}

sf::Vector2f Level::CountCameraPosition() {
    sf::Vector2f targetCenter = m_player.GetPosition();

    float minX = WINDOW_WIDTH / 2.0f;
    float maxX = m_map.GetWidth() * TILE_SIZE - WINDOW_WIDTH / 2.0f;

    float minY = WINDOW_HEIGHT / 2.0f;
    float maxY = m_map.GetHeight() * TILE_SIZE - WINDOW_HEIGHT / 2.0f;

    return {
        std::clamp(targetCenter.x, minX, maxX),
        std::clamp(targetCenter.y, minY, maxY)
    };
}

void Level::Update(float dt) {
    sf::Vector2f tileSetSize = {
        static_cast<float>(m_map.GetWidth() * TILE_SIZE),
        static_cast<float>(m_map.GetHeight() * TILE_SIZE)
    };

    m_player.Update(dt, tileSetSize, m_map);
    m_view.setCenter(CountCameraPosition());
}

void Level::Draw(sf::RenderWindow& window) {
    window.setView(m_view);

    m_map.MapDraw(window);
    m_player.Draw(window);
}

GameState Level::HandleLevelStateChange() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        return menuState;
    }

    return levelState;
}