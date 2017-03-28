#ifndef GUI_H
#define GUI_H

#include "string"
#include <SFML/Graphics.hpp>

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



}


#endif // GUI_H
