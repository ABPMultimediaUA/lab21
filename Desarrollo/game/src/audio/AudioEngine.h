#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "irrKlang.h"

namespace dwe
{
    class AudioEngine
    {
        public:

            static AudioEngine* Instance();

            void Create();
            void Drop();

        protected:

        private:

            AudioEngine(){};
            ~AudioEngine(){};

            irrklang::ISoundEngine* engine;
    };
}

#define AEInstance dwe::AudioEngine::Instance()

#endif // AUDIOENGINE_H
