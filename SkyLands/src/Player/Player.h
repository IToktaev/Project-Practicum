#pragma once
#include "../Map/Map.h"
#include <SFML/Graphics.hpp>
#include "../Animator/Animator.h"
#include "../Sound/Sound.h"

class Player {

public:
    Player();

    void Update(float dt, sf::Vector2f tileSetSize, Map& map);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() { return m_sprite.getPosition(); }

    void Init();

enum class AnimationState : uint8_t {
    Idle,
    Run,
    Jump
};    

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    Animator m_animator;
    sf::Vector2f m_velocity;

    bool m_isGrounded;
    bool m_isJumping;
    float m_jumpForce;
    float m_jumpChargeTime;

    Sound m_runSound;

    AnimationState m_currentAnimation = AnimationState::Idle;

    void SetIdleAnimation();
    void SetRunAnimation();
    void SetJumpAnimation();
    void SetFlyAnimation();
    void SetLandingAnimation();

    void ChangeAnimation(AnimationState newState);

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
        sf::FloatRect hitbox,
        sf::Vector2f& velocity, 
        sf::Vector2f tileSetSize
    );

    void MoveX(float dt, const Map& map);
    void MoveY(float dt, const Map& map);
    sf::FloatRect GetHitbox() const;
};