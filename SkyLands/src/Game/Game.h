#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Level/Level.h"
#include "../Menu/Menu.h"
#include "GameState.h"

class Game {
    public: 
        Game();
        void Run();
        void RenderHome();
        void RunLevel();

    private:
        sf::RenderWindow m_window;
        sf::Clock m_clock;

        Level m_level;
        Menu m_menu;

        GameState m_currentState;
};