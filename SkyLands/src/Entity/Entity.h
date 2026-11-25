#pragma once
#include <SFML/Graphics.hpp>

class Entity {
    public:
        Entity(const sf::Texture& texture, float x, float y);
        void Draw(sf::RenderWindow& window);
        sf::FloatRect GetBounds();
    private:
        sf::Sprite m_sprite;
};