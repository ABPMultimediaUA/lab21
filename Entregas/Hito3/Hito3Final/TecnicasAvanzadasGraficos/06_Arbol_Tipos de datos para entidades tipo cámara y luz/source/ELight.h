#ifndef TAG_ELIGHT_H
#define TAG_ELIGHT_H

#include "Entity.h"
#include "tag/TAGEngine.h"

namespace tag
{
    class ELight : public Entity
    {
        public:
            ELight();
            ~ELight();

            void beginDraw();
            void endDraw();
            vec3f getBoundingBox() { return vec3f(0,0,0); };

            // Luz difusa, especular y ambiental
            vec3f getDiffuseIntensity();
            void setDiffuseIntensity(vec3f intensity);

            vec3f getSpecularIntensity();
            void setSpecularIntensity(vec3f intensity);

            vec3f getAmbientIntensity();
            void setAmbientIntensity(vec3f intensity);

            bool getIfLightOn();
            void setOnOff (bool on); // True si está encendida, false si apagada

        private:
            vec3f   m_diffuseIntensity;
            vec3f   m_specularIntensity;
            vec3f   m_ambientIntensity;
            bool        m_lightOn;

    };
}

#endif // TAG_ELIGHT_H
