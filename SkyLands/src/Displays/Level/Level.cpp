#include "Level.h"
#include <algorithm>
#include <iostream>
#include "../../Entity/Entity.h"

const float DEATH_BORDER = 800.0f;
const float VICTORY_BORDER = 7200.0f;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Level::Level()
    : m_view(sf::FloatRect({0.0f, 0.0f}, {WINDOW_WIDTH, WINDOW_HEIGHT})),
      m_uiView(sf::FloatRect({0.0f, 0.0f}, {WINDOW_WIDTH, WINDOW_HEIGHT}))
{
    if (!m_thornsTexture.loadFromFile("../assets/thorns.png")) {
        std::cerr << "Failed to load thorns texture!\n";
        return;
    }

    if (!m_kitTexture.loadFromFile("../assets/kit.png")) {
        std::cerr << "Failed to load kit texture!\n";
        return;
    }
}

void Level::Init(int levelId) {
    m_id = levelId;
    m_map.MapInit(levelId);
    m_player.Init();

    m_thorns.clear();
    m_kits.clear();

    for (const EntityTile spawn : m_map.GetThorns()) {
        float worldX = spawn.col * TILE_SIZE;
        float worldY = spawn.row * TILE_SIZE;
        m_thorns.emplace_back(m_thornsTexture, worldX, worldY);
    }

    for (const EntityTile spawn : m_map.GetKits()) {
        float worldX = spawn.col * TILE_SIZE;
        float worldY = spawn.row * TILE_SIZE;
        m_kits.emplace_back(m_kitTexture, worldX, worldY);
    }
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
    sf::Vector2f cameraPos = CountCameraPosition();
    m_view.setCenter({ std::round(cameraPos.x), std::round(cameraPos.y) });

    HandleInteractions();
}

void Level::HandleInteractions() {
    sf::FloatRect playerBounds = m_player.GetHitbox();

    for (Entity thorn : m_thorns) {
        if (playerBounds.findIntersection(thorn.GetBounds())) {
            m_player.TakeDamage();
        }
    }

    for (size_t i = 0; i < m_kits.size(); ) {
        if (playerBounds.findIntersection(m_kits[i].GetBounds())) {
            m_player.GiveHearth();
            m_kits.erase(m_kits.begin() + i);
        } else {
            ++i;
        }
    }
}

void Level::Draw(sf::RenderWindow& window) {
    window.setView(m_view);

    m_map.MapDraw(window);

    for (Entity thorn : m_thorns) {
        thorn.Draw(window);
    }

    for (Entity kit : m_kits) {
        kit.Draw(window);
    }


    m_player.Draw(window);

    m_uiView = window.getDefaultView();
    window.setView(m_uiView);

    m_ui.RenderHealthBar(m_player.GetHealth(), m_player.GetMaxHealth(), window);
}

int Level::GetId() {
    return m_id;
}

GameState Level::HandleLevelStateChange(int& lastOpenedLevel) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        return menuState;
    }

    sf::Vector2f position = m_player.GetPosition();

    bool isShock = m_player.GetShockState();
    int lives = m_player.GetHealth();

    if (lives == 0 && !isShock) {
        return defeatState;
    }

    if (position.x > VICTORY_BORDER) {
        lastOpenedLevel++;
        return victoryState;
    } else if (position.y > DEATH_BORDER) {
        return defeatState;
    }

    return levelState;
}