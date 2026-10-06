#include "Player.h"
#include <iostream>

const float startXPos = 400.0f;
const float startYPos = 300.0f;

Player::Player()
    : sprite(texture)
{
    if (!texture.loadFromFile("../../assets/hero.png")) {
        std::cerr << "Load error!\n";
    }

    sprite.setTexture(texture);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});

    sprite.setPosition({startXPos, startYPos});

    velocity = {0.0f, 0.0f};
    isGrounded = false;
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
}