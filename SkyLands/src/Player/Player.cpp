#include "Player.h"
#include <iostream>
#include <algorithm>

const float START_X_POS = 400.0f;
const float START_Y_POS = 300.0f;

const float ACCELERATION = 1800.0f;
const float MAX_SPEED = 300.0f;
const float FRICTION = 0.5f;   

const float GRAVITY = 980.0f;
const float MIN_JUMP_FORCE = -300.0f;
const float MAX_JUMP_FORCE = -700.0f;
const float JUMP_CHARGE_SPEED = 800.0f;
const float MAX_JUMP_CHARGE_TIME = 0.25f;

const float MIN_VELOCITY_TO_ROTATE = 10.0f;
const float PLAYER_SCALE = 0.025f; 

const int TEXTURE_SIZE = 4000;

const float EPSILON = 0.001f;

Player::Player()
    :m_sprite(m_texture)       
{
    if (!m_texture.loadFromFile("../assets/hero.png")) {
        std::cerr << "Load error!\n";
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect({
        {0, 0},
        {TEXTURE_SIZE, TEXTURE_SIZE}
    });

    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
    m_sprite.setScale({PLAYER_SCALE, PLAYER_SCALE});

    m_sprite.setPosition({START_X_POS, START_Y_POS});

    m_velocity = {0.0f, 0.0f};
    m_jumpForce = MIN_JUMP_FORCE;
    m_isGrounded = false;
    m_isJumping = false;
}

void Player::CountMove(float dt, sf::Vector2f& velocity, sf::Sprite& sprite) {
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

    if (velocity.x > MIN_VELOCITY_TO_ROTATE) {
        sprite.setScale({PLAYER_SCALE, PLAYER_SCALE});
    } else if (velocity.x < -MIN_VELOCITY_TO_ROTATE) {
        sprite.setScale({-PLAYER_SCALE, PLAYER_SCALE});
    }
}

void Player::CountJump(
    float dt,
    sf::Vector2f& velocity,
    bool& isGrounded,
    float& jumpForce,
    bool& isJumping,
    float& jumpChargeTime
) {
    bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (isGrounded && jumpPressed && !isJumping) {
        jumpForce = MIN_JUMP_FORCE;
        jumpChargeTime = 0.0f;

        velocity.y = jumpForce;

        isGrounded = false;
        isJumping = true;
    }

    if (isJumping && jumpPressed && jumpChargeTime < MAX_JUMP_CHARGE_TIME) {
        jumpChargeTime += dt;

        jumpForce -= JUMP_CHARGE_SPEED * dt;
        jumpForce = std::max(jumpForce, MAX_JUMP_FORCE);

        velocity.y = jumpForce;
    }

    if (isJumping && (!jumpPressed || jumpChargeTime >= MAX_JUMP_CHARGE_TIME)) {
        isJumping = false;
    }
}

void Player::ResolveCollisions(
    sf::Sprite& sprite, 
    sf::Vector2f& velocity, 
    bool& isGrounded, 
    float floorY,
    sf::Vector2f tileSetSize
) {
    float halfWidth = sprite.getGlobalBounds().size.x / 2.0f;
    float halfHeight = sprite.getGlobalBounds().size.y / 2.0f;

    float x = sprite.getPosition().x;
    float y = sprite.getPosition().y;

    if (y + halfHeight >= floorY) {
        sprite.setPosition({x, floorY - halfHeight});
        velocity.y = 0.0f;
        isGrounded = true;
    }

    if (x - halfWidth < 0.0f) {
        sprite.setPosition({halfWidth, y});
        velocity.x = 0.0f;
    }

    if (x + halfWidth > static_cast<float>(tileSetSize.x)) {
        sprite.setPosition({static_cast<float>(tileSetSize.x) - halfWidth, y});
        velocity.x = 0.0f;
    }
}

void Player::MoveX(float dt, const Map& map) {
    m_sprite.move({m_velocity.x * dt, 0.0f});

    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    int left = std::floor(bounds.position.x / TILE_SIZE);
    int right = std::floor((bounds.position.x + bounds.size.x - EPSILON) / TILE_SIZE);
    int top = std::floor(bounds.position.y / TILE_SIZE);
    int bottom = std::floor((bounds.position.y + bounds.size.y - EPSILON) / TILE_SIZE);

    for (int row = top; row <= bottom; row++) {
        for (int col = left; col <= right; col++) {
            float tileX = static_cast<float>(col * TILE_SIZE);
            float tileY = static_cast<float>(row * TILE_SIZE);

            if (!map.MapIsSolid(tileX, tileY)) {
                continue;
            }

            if (m_velocity.x > 0.0f) {
                m_sprite.setPosition({
                    tileX - bounds.size.x / 2.0f - EPSILON,
                    m_sprite.getPosition().y
                });
            } else if (m_velocity.x < 0.0f) {
                m_sprite.setPosition({
                    tileX + TILE_SIZE + bounds.size.x / 2.0f + EPSILON,
                    m_sprite.getPosition().y
                });
            }

            m_velocity.x = 0.0f;
            return;
        }
    }
}

void Player::MoveY(float dt, const Map& map) {
    m_velocity.y += GRAVITY * dt;
    m_sprite.move({0.0f, m_velocity.y * dt});

    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    int left = std::floor(bounds.position.x / TILE_SIZE);
    int right =  std::floor((bounds.position.x + bounds.size.x - EPSILON) / TILE_SIZE );
    int top = std::floor(bounds.position.y / TILE_SIZE);
    int bottom = std::floor((bounds.position.y + bounds.size.y - EPSILON) / TILE_SIZE);

    m_isGrounded = false;

    for (int row = top; row <= bottom; row++) {
        for (int col = left; col <= right; col++) {
            float tileX = static_cast<float>(col * TILE_SIZE);
            float tileY = static_cast<float>(row * TILE_SIZE);

            if (!map.MapIsSolid(tileX, tileY)) {
                continue;
            }

            if (m_velocity.y > 0.0f) {
                m_sprite.setPosition({
                    m_sprite.getPosition().x,
                    tileY - bounds.size.y / 2.0f - EPSILON
                });

                m_isGrounded = true;
            } else if (m_velocity.y < 0.0f) {
                m_sprite.setPosition({
                    m_sprite.getPosition().x,
                    tileY + TILE_SIZE + bounds.size.y / 2.0f + EPSILON
                });
            }

            m_velocity.y = 0.0f;
            return;
        }
    }
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void Player::Update(float dt, sf::Vector2f tileSetSize, float floor, Map map) {
    CountMove(dt, m_velocity, m_sprite);
    MoveX(dt, map);
    MoveY(dt, map);

    ResolveCollisions(m_sprite, m_velocity, m_isGrounded, floor, tileSetSize);    

    CountJump(dt, m_velocity, m_isGrounded, m_jumpForce, m_isJumping, m_jumpChargeTime);
}

