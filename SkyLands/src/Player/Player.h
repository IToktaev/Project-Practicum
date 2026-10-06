#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void Update(float dt);
    void Draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool isGrounded;
};