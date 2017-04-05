#include "AudioEngine.h"

dwe::AudioEngine* dwe::AudioEngine::Instance()
{
    static AudioEngine instance;
    return &instance;
}

void dwe::AudioEngine::Create()
{
    engine = irrklang::createIrrKlangDevice();
}

void dwe::AudioEngine::Drop()
{
    engine->drop();
}

void dwe::AudioEngine::UpdateListenerPosition(dwe::vec3f pos)
{
    irrklang::vec3df position(pos.x, pos.y, pos.z);
    irrklang::vec3df rotation(0,0,1);
    engine->setListenerPosition(position, rotation);
}

void dwe::AudioEngine::Play2D(const char* fileName)
{
    engine->play2D(fileName);
}

void dwe::AudioEngine::Play3D(const char* fileName, dwe::vec3f pos)
{
    irrklang::vec3df position(pos.x, pos.y, pos.z);
    engine->play3D(fileName, position);
}
