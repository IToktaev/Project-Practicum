#include <SFML/Graphics/RenderWindow.hpp>
#include "../Level/Level.h"
#include <optional>

class LevelFinalScreen {
    public:
        LevelFinalScreen();

        void RenderDisplay(sf::RenderWindow& window, GameState gameState);

        GameState HandleLevelFinalStateChange(
            const sf::Event::MouseButtonPressed* mousePressed, 
            sf::RenderWindow* window,
            GameState currentState,
            Level &level
        );

    private:
        sf::Texture m_toHomeButtonTexture;
        sf::Texture m_restartButtonTexture;
        sf::Texture m_defeatTexture;
        sf::Texture m_victoryTexture;

        sf::Sprite m_toHomeButton;
        sf::Sprite m_restartButton;
        sf::Sprite m_screenImage;
};