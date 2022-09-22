#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include "Constants.hpp"

class SoundManager
{
private:
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;
    bool hasClickSound;

public:
    SoundManager();
    void playClickSound();
};

SoundManager::SoundManager()
{
    if (!clickSoundBuffer.loadFromFile(clickSoundPath))
    {
        std::cerr
            << "Click sound file is missing." << std::endl;
        hasClickSound = false;
        return;
    }
    hasClickSound = true;
    clickSound.setBuffer(clickSoundBuffer);
}

void SoundManager::playClickSound()
{
    if (!hasClickSound)
    {
        std::cerr
            << "Cannot play click sound due to missing sound file." << std::endl;
    }
    else
    {
        clickSound.play();
    };
}

// the sound file lives in buffer, so a global variable is required to keep it alive
SoundManager globalSoundManager;