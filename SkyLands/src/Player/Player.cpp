#include "Player.h"
#include <iostream>
#include <algorithm>

const float START_X_POS = 400.0f;
const float START_Y_POS = 300.0f;

const float ACCELERATION = 1800.0f;
const float MAX_SPEED = 300.0f;
const float FRICTION = 0.88f;   

Player::Player()
    : sprite(texture)
{
    if (!texture.loadFromFile("../../assets/hero.png")) {
        std::cerr << "Load error!\n";
    }

    sprite.setTexture(texture);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});

    sprite.setPosition({START_X_POS, START_Y_POS});

    velocity = {0.0f, 0.0f};
    isGrounded = false;
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::Update(float dt) {
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        velocity.x += ACCELERATION * dt;
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        velocity.x -= ACCELERATION * dt;
        isMoving = true;
    }

    if (!isMoving) {
        velocity.x *= FRICTION;
    }

    velocity.x = std::clamp(velocity.x, -MAX_SPEED, MAX_SPEED);

    if (velocity.x > 10.0f) {
        sprite.setScale({1.0f, 1.0f});
    } else if (velocity.x < 10.0f) {
        sprite.setScale({-1.0f, 1.0f});
    }
}