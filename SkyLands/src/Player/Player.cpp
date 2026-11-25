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
const float PLAYER_SCALE = 0.5f; 

const float EPSILON = 0.001f;

const float HITBOX_X_SCALE_FACTOR = 0.6;

const float RUN_DURATION = 0.2f;
const float BASE_DURATION = 0.1f;
const float DEATH_DURATION = 0.5f;

const int SPRITE_WIDTH = 220;
const int SPRITE_HEIGHT = 210;

const int MAX_HEALTHBAR = 3;

const int SHOCK_TIME_S = 1;

Player::Player()
    : m_sprite(m_texture),
      m_animator(m_sprite),
      m_currentAnimation(AnimationState::Idle)
{
    if (!m_texture.loadFromFile("../assets/hero_atlas.png")) {
        std::cerr << "Load error!\n";
    }

    m_sprite.setTexture(m_texture);
    SetIdleAnimation();

    m_runSound.LoadFromFile("../assets/sounds/footstep.wav");
    m_jumpSound.LoadFromFile("../assets/sounds/jump.wav");

    m_jumpSound.SetVolume(50);
}

int Player::GetHealth() {
    return m_healthbar;
}

int Player::GetMaxHealth() {
    return MAX_HEALTHBAR;
}

void Player::SetRunAnimation() {
    m_animator.SetAnimation({
        sf::IntRect({0, 420}, {SPRITE_WIDTH, SPRITE_HEIGHT}),
        sf::IntRect({420, 420}, {SPRITE_WIDTH, SPRITE_HEIGHT}),
    }, RUN_DURATION);
}

void Player::SetIdleAnimation() {
    m_animator.SetAnimation({
        sf::IntRect({0, 0}, {SPRITE_WIDTH, SPRITE_HEIGHT})
    }, BASE_DURATION);
}

void Player::SetDeathAnimation() {
    m_animator.SetAnimation({
        sf::IntRect({180, 1050}, {SPRITE_WIDTH, SPRITE_HEIGHT}),
        sf::IntRect({360, 1050}, {SPRITE_WIDTH, SPRITE_HEIGHT}),
        sf::IntRect({540, 1050}, {SPRITE_WIDTH, SPRITE_HEIGHT})
    }, DEATH_DURATION);
}

void Player::SetJumpAnimation() {
    m_animator.SetAnimation({
        sf::IntRect({420, 640}, {SPRITE_WIDTH, SPRITE_HEIGHT})
    }, BASE_DURATION);
}

void Player::ChangeAnimation(AnimationState newState) {
    if (m_currentAnimation == newState) {
        return;
    }

    m_currentAnimation = newState;

    switch (newState) {
        case AnimationState::Idle:
            SetIdleAnimation();
            break;

        case AnimationState::Run:
            SetRunAnimation();
            break;

        case AnimationState::Jump:
            SetJumpAnimation();
            break;

        case AnimationState::Death:
            SetDeathAnimation();
            break;
    }
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

        m_jumpSound.Play();
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
    sf::FloatRect hitbox,
    sf::Vector2f& velocity, 
    sf::Vector2f tileSetSize
) {
    float halfWidth = hitbox.size.x / 2.0f;

    float x = sprite.getPosition().x;
    float y = sprite.getPosition().y;

    if (x - halfWidth < 0.0f) {     
        sprite.setPosition({halfWidth, y});
        velocity.x = 0.0f;
    }

    if (x + halfWidth > static_cast<float>(tileSetSize.x)) {
        sprite.setPosition({static_cast<float>(tileSetSize.x) - halfWidth, y});
        velocity.x = 0.0f;
    }
}

sf::FloatRect Player::GetHitbox() {
    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    float width = bounds.size.x * HITBOX_X_SCALE_FACTOR;

    return {
        {bounds.position.x + (bounds.size.x - width) / 2.0f,
         bounds.position.y},
        {width, bounds.size.y}
    };
}

void Player::MoveX(float dt, const Map& map) {
    m_sprite.move({m_velocity.x * dt, 0.0f});
    sf::FloatRect hitbox = GetHitbox();

    int left = std::floor(hitbox.position.x / TILE_SIZE);
    int right = std::floor((hitbox.position.x + hitbox.size.x - EPSILON) / TILE_SIZE);
    int top = std::floor(hitbox.position.y / TILE_SIZE);
    int bottom = std::floor((hitbox.position.y + hitbox.size.y - EPSILON) / TILE_SIZE);

    for (int row = top; row <= bottom; row++) {
        for (int col = left; col <= right; col++) {
            float tileX = static_cast<float>(col * TILE_SIZE);
            float tileY = static_cast<float>(row * TILE_SIZE);

            if (!map.MapIsSolid(tileX, tileY)) {
                continue;
            }

            if (m_velocity.x > 0.0f) {
                if (hitbox.position.x + hitbox.size.x > tileX &&
                    hitbox.position.x < tileX
                ) {
                    float overlap = hitbox.position.x + hitbox.size.x - tileX;
                    m_sprite.move({-overlap - EPSILON, 0.0f});
                    m_velocity.x = 0.0f;
                    return;
                }
            } else if (m_velocity.x < 0.0f) {
                if (hitbox.position.x < tileX + TILE_SIZE &&
                    hitbox.position.x + hitbox.size.x > tileX + TILE_SIZE
                ) {

                    float overlap = tileX + TILE_SIZE - hitbox.position.x;
                    m_sprite.move({overlap + EPSILON, 0.0f});
                    m_velocity.x = 0.0f;
                    return;
                }
            }

            m_velocity.x = 0.0f;
            return;
        }
    }
}

void Player::MoveY(float dt, const Map& map) {
    m_velocity.y += GRAVITY * dt;
    m_sprite.move({0.0f, m_velocity.y * dt});
    sf::FloatRect bounds = GetHitbox();

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
                float overlap = bounds.position.y + bounds.size.y - tileY;
                m_sprite.move({0.0f, -overlap - EPSILON});
                m_isGrounded = true;
            } else if (m_velocity.y < 0.0f) {
                float overlap = tileY + TILE_SIZE - bounds.position.y;
                m_sprite.move({0.0f, overlap + EPSILON});
            }

            m_velocity.y = 0.0f;
            return;
        }
    }
}

void Player::Draw(sf::RenderWindow& window) {
    if (m_isShock) {
        m_sprite.setColor(sf::Color(255, 80, 80));
    } else {
        m_sprite.setColor(sf::Color::White);
    }

    window.draw(m_sprite);

    // sf::RectangleShape debugRect;

    // sf::FloatRect hitbox = GetHitbox();

    // debugRect.setPosition(hitbox.position);
    // debugRect.setSize(hitbox.size);
    // debugRect.setFillColor(sf::Color::Transparent);
    // debugRect.setOutlineColor(sf::Color::Red);
    // debugRect.setOutlineThickness(1.0f);

    // window.draw(debugRect);
}

void Player::GiveHearth() {
    if (m_healthbar < MAX_HEALTHBAR) {
        m_healthbar++;
    }
}

void Player::TakeDamage() {
    if (m_isShock) {
        return;
    }

    m_healthbar--;
    m_isShock = true;
    m_shockDuration = 0.0f;
}

void Player::Update(float dt, sf::Vector2f tileSetSize, Map& map) {
    if (m_healthbar == 0) {
        ChangeAnimation(AnimationState::Death);
    }

    if (m_healthbar > 0) {
        CountMove(dt, m_velocity, m_sprite);
        MoveX(dt, map);
        MoveY(dt, map);
    }

    m_shockDuration += dt;
    if (m_isShock && m_shockDuration > SHOCK_TIME_S) {
        m_shockDuration = 0;
        m_isShock = false;
    }

    if (!m_isGrounded) {
        ChangeAnimation(AnimationState::Jump);
        m_runSound.Stop();
    } else if (m_velocity.x != 0) {
        ChangeAnimation(AnimationState::Run);
        if (m_runSound.GetStatus() != sf::Sound::Status::Playing) {
            if (m_runSoundClock.getElapsedTime().asMilliseconds() >= 300) {
                m_runSound.Play();
                m_runSoundClock.restart();
            }
        }
    } else if (m_healthbar > 0) {
        ChangeAnimation(AnimationState::Idle);
    }
    
    m_animator.Update(dt);

    ResolveCollisions(m_sprite, GetHitbox(), m_velocity, tileSetSize);  
    CountJump(dt, m_velocity, m_isGrounded, m_jumpForce, m_isJumping, m_jumpChargeTime);
}

void Player::Init() {
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
    m_sprite.setScale({PLAYER_SCALE, PLAYER_SCALE});
    m_sprite.setPosition({START_X_POS, START_Y_POS});

    m_velocity = {0.0f, 0.0f};
    m_jumpForce = MIN_JUMP_FORCE;
    m_isGrounded = false;
    m_isJumping = false;

    m_healthbar = MAX_HEALTHBAR;
    m_isShock = false;
    m_shockDuration = 0;

    SetIdleAnimation();
}
