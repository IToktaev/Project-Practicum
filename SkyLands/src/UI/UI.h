#include <SFML/Graphics.hpp>

class UI {

public:
    UI();
    void RenderHealthBar(int lives, int maxLives, sf::RenderWindow& window);

private:
    sf::Texture m_aliveHearthTexture;
    sf::Texture m_deadHearthTexture;

    std::vector<sf::Sprite> m_hearts;
};