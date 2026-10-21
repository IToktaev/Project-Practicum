#pragma once
#include "../Map/Map.h"
#include <SFML/Graphics.hpp>

class Player {

public:
    Player();

    void Update(float dt, sf::Vector2f tileSetSize, float floor, Map map);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() { return m_sprite.getPosition(); }

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;

    bool m_isGrounded;
    bool m_isJumping;
    float m_jumpForce;
    float m_jumpChargeTime;

    void CountMove(float dt, sf::Vector2f& velocity, sf::Sprite& sprite);
    void CountJump(
        float dt,
        sf::Vector2f& velocity,
        bool& isGrounded,
        float& jumpForce,
        bool& isJumping,
        float& jumpChargeTime
    );
    void ResolveCollisions(
        sf::Sprite& sprite, 
        sf::Vector2f& velocity, 
        bool& isGrounded, 
        float floorY,
        sf::Vector2f tileSetSize
    );

    void MoveX(float dt, const Map& map);
    void MoveY(float dt, const Map& map);
};