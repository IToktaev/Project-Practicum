#include <SFML/Graphics/RenderWindow.hpp>
#include "../Level/Level.h"

class Home {
    public:
        Home();

        void RenderHome(sf::RenderWindow& window, int lastOpenedLevel);

        GameState HandleHomeStateChange(
            const sf::Event::MouseButtonPressed* mousePressed, 
            sf::RenderWindow* window,
            GameState currentState,
            Level& level,
            int lastOpenedLevel
        );

    private:
        sf::Texture m_backgroundTexture;
        sf::Texture m_levelFirstIconTexture;
        sf::Texture m_levelSecondIconTexture;
        sf::Texture m_levelThirdIconTexture;
        sf::Texture m_chainsLightTexture;
        sf::Texture m_chainsDarkTexture;

        sf::Sprite m_background;
        sf::Sprite m_levelFirstIcon;
        sf::Sprite m_levelSecondIcon;
        sf::Sprite m_levelThirdIcon;

        sf::Sprite m_secondIconLocked;
        sf::Sprite m_thirdIconLocked;
};