#pragma once

#include "Player.h"
#include "Map.h"
#include "../Game/GameState.h"
#include "../../UI/UI.h"
#include "../../Entities/Thorns/Thorns.h"

class Level {
    private:
        Player m_player;
        Map m_map;

        UI m_ui;

        sf::View m_view;
        sf::View m_uiView;

        std::vector<Thorns> m_thorns;

        sf::Vector2f CountCameraPosition();

        void HandleInteractions();

        int m_id;

        sf::Texture m_thornsTexture;

    public:
        Level();

        void Init(int levelId);
        void Update(float dt);
        void Draw(sf::RenderWindow& window);

        int GetId();

        GameState HandleLevelStateChange(int& lastOpenedLevel);
};