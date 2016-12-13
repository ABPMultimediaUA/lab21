#include "Selector.h"
#include <iostream>

Selector::Selector()
{
    numChildren = 0;
    brunning = false;
    children = new Node*;
}

Selector::~Selector()
{
    delete children;
}

States Selector::run()
{
    int i;

    for(i = 0; i < numChildren; i++)
    {
        if (children[i]->getRunning())
        {

            while(i < numChildren)
            {
                States ns = children[i]->run();

                switch(ns)
                {
                    case success:

                        brunning = false;
                        return success;
                        break;

                    case running:

                        brunning = true;
                        return running;
                        break;

                    case failure:

                        break;
                }

                i++;
            }

            brunning = false;
            return failure;
        }
    }


    for(i = 0; i < numChildren; i++)
    {
        States ns = children[i]->run();

        switch(ns)
        {
            case success:

                brunning = false;
                return success;
                break;

            case running:

                brunning = true;
                return running;
                break;

            case failure:

                break;
        }
    }

    brunning = false;
    return failure;
}
