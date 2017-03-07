#ifndef ELIGHT_H
#define ELIGHT_H

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

            // Luz difusa, especular y ambiental
            glm::vec4 getDiffuseIntensity();
            void setDiffuseIntensity(glm::vec4 intensity);

            glm::vec4 getSpecularIntensity();
            void setSpecularIntensity(glm::vec4 intensity);

            glm::vec4 getAmbientIntensity();
            void setAmbientIntensity(glm::vec4 intensity);

            bool getIfLightOn();
            void setOnOff (bool on); // True si está encendida, false si apagada

        private:

            glm::vec4 m_DiffuseIntensity;                       // 4 canales de color: RGBA
            glm::vec4 m_SpecularIntensity;
            glm::vec4 m_AmbientIntensity;
            bool m_lightOn;

    };
}

#endif // ELIGHT_H
