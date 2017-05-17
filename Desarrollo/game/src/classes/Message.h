#ifndef MESSAGE_H
#define MESSAGE_H

#include "GraphicsEngine.h"

class Message
{
    public:

        Message();
        virtual ~Message();
        dwe::vec2f position();
        int setSender(int id);
        int setReceiver(int id);
        int getSender();
        int getReceiver();

    protected:

    private:
        int m_sender;
        int m_receiver;

};

#endif // CONSUMABLE_H
