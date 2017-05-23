#include "AudioEngine.h"

dwe::AudioEngine* dwe::AudioEngine::Instance()
{
    static AudioEngine instance;
    return &instance;
}

void dwe::AudioEngine::Create()
{
    engine = irrklang::createIrrKlangDevice();
    m_numSounds = 0;
    SetMasterVolume(1.0);
}

void dwe::AudioEngine::Drop()
{
    engine->drop();
}

void dwe::AudioEngine::SetMasterVolume(float volume)
{
    m_volume = volume;
    engine->setSoundVolume(volume);
}

void dwe::AudioEngine::UpdateListenerPosition(dwe::vec3f pos)
{
    irrklang::vec3df position(pos.x*_ratio, pos.y, pos.z*_ratio);
    irrklang::vec3df rotation(0,0,1);
    engine->setListenerPosition(position, rotation);
}

void dwe::AudioEngine::Play2D(const char* fileName, float volume, bool loop)
{
    irrklang::ISound* sound = engine->play2D(fileName, loop, false, true);
    sound->setVolume(volume);
    sound->drop();
}

void dwe::AudioEngine::Play3D(const char* fileName, dwe::vec3f pos, float volume, bool loop)
{
    irrklang::vec3df position(pos.x*_ratio, pos.y, pos.z*_ratio);
    irrklang::ISound* sound = engine->play3D(fileName, position, loop, false, true);
    sound->setVolume(volume);
    sound->drop();
}

/*** GETTERS ***/

float dwe::AudioEngine::GetMasterVolume()
{
    return m_volume;
}
