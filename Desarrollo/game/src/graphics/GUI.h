#ifndef GUI_H
#define GUI_H

#include "string"
#include "defines.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "AnimatedSprite.hpp"

namespace dwe{

    // SFML FACHADA
    // ==============
    class Button{
        public:
            Button(std::string t, int x, int y, bool bg);
            ~Button();
            void draw();
            int getXOrigin();
            int getYOrigin();
            int getWidth();
            int getHeight();
            bool buttonCheck(int mx, int my);
            void hover();
            void unhover();
            void clicked();

        private:
            int x, y;
            int bgx, bgy;
            bool bg;
            bool hovered;
            sf::Font font;
            sf::Text text;
            sf::Texture texture;
            sf::Sprite sp;
    };

    class Background{
        public:
            Background(std::string s);
            ~Background();
            void draw();
        private:
            sf::Texture texture;
            sf::RectangleShape rs;
    };

    class Sprite{
        public:
            Sprite(std::string s, int x, int y);
            ~Sprite();
            void draw();
            void SetTexture(std::string s);
            void SetScale(float factorX, float factorY);
        private:
            sf::Texture texture;
            sf::Sprite sp;
    };

    class HudBox
    {
        public:
            HudBox(){};
            ~HudBox(){};
            virtual void draw(){};
            void setComponents(std::string str, sf::Sprite *s, sf::Texture *t, float px, float py);
            void setTextComponents(sf::Text *text, sf::Font font, unsigned int siz, sf::Color color, float px, float py);

        protected:
            float t;                  // Probar a cambiar de arma, vida, botiquines...
            sf::Font font;            // Fuente para los textos
    };

    class WeaponBox : public HudBox
    {
        public:
            WeaponBox(float x, float y);
            ~WeaponBox();
            void swapWeapon(FirearmKind weapon, int ammo, int ammoBag, sf::Texture *tweapon, sf::Text *textammo);
            void updateWeapon (sf::Texture *tweapon, std::string str, int ammo, int ammobag, sf::Text *textammo);
            void draw(FirearmKind weapon, int ammo, int ammoBag, int grenades);
            void setText(sf::Text *text, int num);
            void setWeaponBoxAnimation ();
            void animateWeaponBox();

        private:
            AnimatedSprite s_box;
            sf::Texture t_box;
            Animation weaponBoxAnim;

            sf::Sprite s_weapon;
            sf::Texture t_weapon;

            sf::Sprite s_grenade;
            sf::Texture t_grenade;

            sf::Text text_ammo;
            sf::Text text_grenades;

            // Variables para probar HUD
            int ammoGun;        // Para la munición de cada arma
            int ammoRifle;
            int ammoShotgun;
            int grenades;

            sf::Clock frameClock; // Para controlar el tiempo de animacion del hud
            sf::Time frameTime;
            float t;
    };

    class HealthBox : public HudBox
    {
        public:
            HealthBox(float x, float y);
            ~HealthBox();

            void drawCurrentHealth(int health, int maxHealth);
            void drawNumberOfMedkits(int medkits);
            void draw(int medkits, int health, int maxHealth, int speedBoosts);
            void drawNumberOfSpeedBoosts(int speedBoosts);


        private:

            // Caja base
            sf::Sprite s_box;
            sf::Texture t_box;

            // Vida
            sf::RectangleShape s_health;
            sf::Texture t_health;
            sf::Text text_health;

            // Vida perdida
            sf::Sprite s_hplost;
            sf::Texture t_hplost;

            // Contorno vida
            sf::Sprite s_edge;
            sf::Texture t_edge;

            // Botiquines
            sf::Sprite s_heal;
            sf::Texture t_heal;
            sf::Text text_heal;

            // Adrenalina
            sf::Sprite s_speedBoost;
            sf::Texture t_speedBoost;
            sf::Text text_sb;


    };


}


#endif // GUI_H
