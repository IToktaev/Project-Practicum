#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Game/GameState.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Menu {
    public: 
        Menu();

        void RenderMenu(sf::RenderWindow& window);
        
        GameState HandleMenuStateChange(
            const sf::Event::MouseButtonPressed* mousePressed, 
            sf::RenderWindow* window,
            GameState currentState
        );

    private:
        sf::Texture m_toHomeButtonTexture;
        sf::Texture m_toLevelButtonTexture;

        sf::Sprite m_toHomeButton;
        sf::Sprite m_toLevelButton;
};