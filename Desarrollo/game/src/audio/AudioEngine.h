#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "irrKlang.h"
#include "GraphicsEngine.h"
#include <vector>

namespace dwe
{
    class AudioEngine
    {
        public:

            static AudioEngine* Instance();

            void Create();
            void Drop();

            void SetMasterVolume(float volume);
            void UpdateListenerPosition(dwe::vec3f pos);

            void Play2D(const char* fileName, float volume = 1.0, bool loop = false);
            void Play3D(const char* fileName, dwe::vec3f pos, float volume = 1.0, bool loop = false);

            void StopAllSounds();

            float GetMasterVolume();

        private:

            AudioEngine(){};
            ~AudioEngine(){};

            std::vector<irrklang::ISound*> m_sounds;
            int m_numSounds;

            irrklang::ISoundEngine* engine;
            float m_volume;

            static const float _ratio = 0.035;
    };
}

#define AEInstance dwe::AudioEngine::Instance()

#endif // AUDIOENGINE_H
