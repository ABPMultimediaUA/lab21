#ifndef GUI_H
#define GUI_H

#include "string"
#include "defines.h"
#include <SFML/Graphics.hpp>
#include <sstream>

namespace dwe{

    // SFML FACHADA
    // ==============
    class Button{
        public:
            Button(std::string t, int x, int y);
            ~Button();
            void draw();
            int getXOrigin();
            int getYOrigin();
            int getWidth();
            int getHeight();
            bool buttonCheck(dwe::Button *b);
        private:
            int x, y;
            sf::Font font;
            sf::Text text;
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

    class AchievementInfo{
        public:
            AchievementInfo(std::string n);
            ~AchievementInfo();
            void draw();
            void setPosition();
        private:
            sf::Texture texture;
            sf::Sprite sp;
    };

    class Condition{

        public:

            virtual bool test() = 0;

        private:

    };

    class ConditionEnemiesKilled : public Condition{

        public:

            ConditionEnemiesKilled(int en);

            bool test();

        private:

            int enemies;



    };

    class Achievement{
        public:
            Achievement(std::string n, int x, int y, Condition* con);
            ~Achievement();
            void draw();
            void drawInfo();
            void hovered();
            bool getAchieved();
            bool testAchieved();
            void setAchieved();
        private:
            sf::Sprite sp;
            sf::Texture texture;
            sf::Texture textureAchieved;
            int x, y;
            dwe::AchievementInfo achinfo;
            bool achieved;
            Condition* condition;
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
            void swapWeapon(FirearmKind weapon, int ammo, sf::Texture *tweapon, sf::Text *textammo);
            void updateWeapon (sf::Texture *tweapon, std::string str, int ammo, sf::Text *textammo);
            void draw(FirearmKind weapon, int ammo);

        private:
            sf::Sprite s_box;
            sf::Texture t_box;

            sf::Sprite s_weapon;
            sf::Texture t_weapon;

            sf::Text text_ammo;

            // Variables para probar HUD
            int ammoGun;        // Para la munición de cada arma
            int ammoRifle;
            int ammoShotgun;
            int grenades;
    };

    class HealthBox : public HudBox
    {
        public:
            HealthBox(float x, float y);
            ~HealthBox();

            void drawCurrentHealth(int health, int maxHealth);
            void drawNumberOfMedkits(int medkits);
            void draw(int medkits, int health, int maxHealth);


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


            // Variables para probar el HUD al no tenerlo junto al Game
            //int heals;      // Para los botiquines

            //float health;     // Para la vida actual
            //float max_health; // Para la vida máxima

    };


}


#endif // GUI_H
