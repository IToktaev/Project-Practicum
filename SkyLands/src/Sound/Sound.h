#pragma once

#include <SFML/Audio.hpp>
#include <string>

class Sound {
public:
    Sound() = default;

    bool LoadFromFile(const std::string& filename);

    void Play();
    void Pause();
    void Stop();

    void SetVolume(float volume);
    void SetLooping(bool looping);
    sf::Sound::Status GetStatus();

private:
    sf::SoundBuffer m_buffer;
    std::unique_ptr<sf::Sound> m_sound;
};