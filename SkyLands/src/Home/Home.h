#include <SFML/Graphics/RenderWindow.hpp>
#include "../Level/Level.h"

class Home {
    public:
        Home();

        void RenderHome(sf::RenderWindow& window);

        GameState HandleHomeStateChange(
            const sf::Event::MouseButtonPressed* mousePressed, 
            sf::RenderWindow* window,
            GameState currentState,
            Level& level
        );

    private:
        sf::Texture m_backgroundTexture;
        sf::Texture m_levelFirstIconTexture;
        sf::Texture m_levelSecondIconTexture;
        sf::Texture m_levelThirdIconTexture;

        sf::Sprite m_background;
        sf::Sprite m_levelFirstIcon;
        sf::Sprite m_levelSecondIcon;
        sf::Sprite m_levelThirdIcon;
};