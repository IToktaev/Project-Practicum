#pragma once

#include "Player.h"
#include "Map.h"
#include "../Game/GameState.h"

class Level {
private:
    Player m_player;
    Map m_map;

    sf::View m_view;

    sf::Vector2f CountCameraPosition();

    int m_id;

public:
    Level();

    void Init(int levelId);
    void Update(float dt);
    void Draw(sf::RenderWindow& window);

    int GetId();

    GameState HandleLevelStateChange();
};