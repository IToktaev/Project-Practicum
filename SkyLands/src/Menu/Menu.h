#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Game/GameState.h"

class Menu {
    public: 
        void RenderMenu(sf::RenderWindow& window);
        
        GameState HandleMenuStateChange(
            const sf::Event::MouseButtonPressed* mousePressed, 
            sf::RenderWindow* window,
            GameState currentState
        );
};