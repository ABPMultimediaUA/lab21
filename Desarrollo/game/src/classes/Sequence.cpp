#include "Sequence.h"
#include <iostream>

Sequence::Sequence()
{
    numChildren = 0;
    brunning = false;
}

Sequence::~Sequence()
{
    delete children;
}

States Sequence::run()
{
    int i;

    for(i = 0; i < numChildren; i++)
    {
        // Primero vemos si hay algún nodo en running
        if (children[i]->getRunning()) // brunning true
        {
            while(i < numChildren)
            {
                States ns = children[i]->run();

                switch(ns)
                {
                    case failure:

                        brunning = false;
                        return failure;
                        break;

                    case running:

                        brunning = true;
                        return running;
                        break;

                    case success:

                        break;

                }

                i++;
            }

            brunning = false;
            return success;
        }
    }

    // Si no hay ningún nodo en running, recorremos el árbol desde el principio
    for(i = 0; i < numChildren; i++)
    {
        States ns = children[i]->run();

        switch(ns)
        {
            case failure:

                brunning = false;
                return failure;
                break;

            case running:

                brunning = true;
                return running;
                break;

            case success:

                break;
        }
    }

    brunning = false;
    return success;
}
