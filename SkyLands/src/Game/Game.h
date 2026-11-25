#pragma once
#include "../Level/Level.h"
#include "../Menu/Menu.h"
#include "../Home/Home.h"
#include "../Displays/LevelFinalScreen/LevelFinalScreen.h"

class Game {
    public: 
        Game();
        void Run();

    private:
        sf::RenderWindow m_window;
        sf::Clock m_clock;

        Level m_level;
        Menu m_menu;
        Home m_home;
        LevelFinalScreen m_levelFinalScreen;

        GameState m_currentState;

        int m_currentOpenedLevel;
};

//здесь будет публичный метод создания пули