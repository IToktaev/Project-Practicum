#include <SFML/Graphics/RenderWindow.hpp>
#include "../Level/Level.h"

class Home {
    public:
        void RenderHome(sf::RenderWindow& window);

        GameState HandleHomeStateChange(
            const sf::Event::MouseButtonPressed* mousePressed, 
            sf::RenderWindow* window,
            GameState currentState,
            Level& level
        );
};