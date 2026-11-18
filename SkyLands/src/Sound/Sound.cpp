#include "Sound.h"
#include <iostream>
#include <memory>

bool Sound::LoadFromFile(const std::string& filename) {
    if (!m_buffer.loadFromFile(filename)) {
        std::cerr << "Failed to load sound: " << filename << '\n';
        return false;
    }

    m_sound = std::make_unique<sf::Sound>(m_buffer);
    return true;
}

sf::Sound::Status Sound::GetStatus() {
    if (!m_sound) {
        return sf::Sound::Status::Stopped;
    }

    return m_sound->getStatus();
}

void Sound::Play() {
    if (m_sound) {
        m_sound->play();
    }
}

void Sound::Pause() {
    if (m_sound) {
        m_sound->pause();
    } 
}

void Sound::Stop() {
    if (m_sound) {
        m_sound->stop();
    }
}

void Sound::SetVolume(float volume) {
    if (m_sound) {
        m_sound->setVolume(volume);
    }
}

void Sound::SetLooping(bool looping) {
    if (m_sound) {
        m_sound->setLooping(looping);
    }
}