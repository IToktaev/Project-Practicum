
#include "Animator.h"

Animator::Animator(sf::Sprite& sprite)
    : m_sprite(sprite)
{
}

void Animator::SetAnimation(
    const std::vector<sf::IntRect>& frames,
    float frameDuration,
    bool isLooping
) {
    m_frames = frames;
    m_frameDuration = frameDuration;
    m_isLooping = isLooping;

    m_currentFrame = 0;
    m_animationTimer = 0.0f;

    if (!m_frames.empty()) {
        m_sprite.setTextureRect(m_frames[0]);
    }
}

void Animator::Update(float dt) {
    if (m_frames.empty() || m_frameDuration <= 0.0f) {
        return;
    }

    m_animationTimer += dt;

    while (m_animationTimer >= m_frameDuration) {
        m_animationTimer -= m_frameDuration;

        if (m_currentFrame + 1 < static_cast<int>(m_frames.size())) {
            m_currentFrame++;
        }
        else if (m_isLooping) {
            m_currentFrame = 0;
        }
        else {
            m_animationTimer = 0.0f;
            return;
        }

        m_sprite.setTextureRect(m_frames[m_currentFrame]);
    }
}
