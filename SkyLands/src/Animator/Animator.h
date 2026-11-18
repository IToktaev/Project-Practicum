
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animator {
private:
    sf::Sprite& m_sprite;

    std::vector<sf::IntRect> m_frames;

    int m_currentFrame = 0;

    float m_animationTimer = 0.0f;
    float m_frameDuration = 0.1f;

    bool m_isLooping = true;

public:
    Animator(sf::Sprite& sprite);

    void SetAnimation(
        const std::vector<sf::IntRect>& frames,
        float frameDuration,
        bool isLooping = true
    );

    void Update(float dt);
};
