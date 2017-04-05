#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "irrKlang.h"
#include "GraphicsEngine.h"

namespace dwe
{
    class AudioEngine
    {
        public:

            static AudioEngine* Instance();

            void Create();
            void Drop();

            void UpdateListenerPosition(dwe::vec3f pos);

            void Play2D(const char* fileName);
            void Play3D(const char* fileName, dwe::vec3f pos);

        private:

            AudioEngine(){};
            ~AudioEngine(){};

            irrklang::ISoundEngine* engine;
    };
}

#define AEInstance dwe::AudioEngine::Instance()

#endif // AUDIOENGINE_H
