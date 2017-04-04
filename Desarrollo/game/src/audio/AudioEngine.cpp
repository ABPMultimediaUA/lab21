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
