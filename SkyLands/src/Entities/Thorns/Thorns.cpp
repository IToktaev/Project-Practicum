#include "Thorns.h"
#include <Map.h>

Thorns::Thorns(const sf::Texture& texture, float x, float y) 
    : m_sprite(texture)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(texture.getSize())));

    sf::Vector2u textureSize = texture.getSize();
    float scaleX = TILE_SIZE / static_cast<float>(textureSize.x);
    float scaleY = TILE_SIZE / static_cast<float>(textureSize.y);

    m_sprite.setScale({scaleX, scaleY});
    m_sprite.setPosition({x, y});
}

void Thorns::Draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

sf::FloatRect Thorns::GetBounds() {
    return m_sprite.getGlobalBounds();
}