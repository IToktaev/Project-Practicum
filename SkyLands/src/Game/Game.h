#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "../Map/Map.h"

class Game {
    public: 
        Game();
        void Run();

    private:
        sf::RenderWindow window;
        sf::Clock clock;
        sf::View view;

        Player player;
        Map map;

        sf::Vector2f CountCameraPosition();
};