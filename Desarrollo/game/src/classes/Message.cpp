#include "Message.h"

Message::Message()
{

}

Message::~Message()
{

}

dwe::vec2f Message::position(){

}

int Message::setSender(int id){
    m_sender = id;
}
int Message::setReceiver(int id){
    m_receiver = id;
}
int Message::getSender(){
    return m_sender;
}
int Message::getReceiver(){
    return m_receiver;
}



