#include "DrawImage.h"

void DrawImage(
    sf::Sprite& sprite,
    sf::Vector2f scale,
    sf::Vector2f position,
    sf::RenderWindow& window
)
{
    sprite.setScale(scale);
    sprite.setPosition(position);
    window.draw(sprite);
}