#ifndef ACHIEVEMENTSHANDLER_H
#define ACHIEVEMENTSHANDLER_H

#include "GUI.h"

#define nAchievements 1


class AchievementsHandler
{
    private:
        int numAchieved;
        dwe::Achievement *achievements[nAchievements];
        int enemiesKilled;
        int pasosCaminados;

	public:
		AchievementsHandler(){
		    /*TODO antes no se ejecutaba pq estaba mal llamado, no se ejecutaba el constructor.
		    Ahora al ejecutarse deja el programa parado....?¿?¿?

		    numAchieved=0;
		    dwe::ConditionEnemiesKilled* con = new dwe::ConditionEnemiesKilled(50);
            achievements[0] = new dwe::Achievement("1", 0.1, 0.35, con);*/
		}

		void draw(){
            for(int i=0; i<nAchievements; i++){
                achievements[i]->draw();
                achievements[i]->drawInfo();
            }
		}

		void update(){
		     for(int i=numAchieved; i<nAchievements; i++){
                //if(!achievements[i]->getAchieved() && Game::getInstance()->getEnemyDeads()>=50)
                    //achievements[i]->setAchieved();
                if(achievements[i]->testAchieved()){
                    achievements[i]->setAchieved();

                }

            }
		}

		int getEnemiesKilled(){
            return enemiesKilled;
		}

};

#endif // ACHIEVEMENTSHANDLER_H
