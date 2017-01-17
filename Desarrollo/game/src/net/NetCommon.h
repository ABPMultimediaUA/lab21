#ifndef NETCOMMON_H
#define NETCOMMON_H
#include "MessageIdentifiers.h"

using namespace RakNet;

enum GameMessages
{
    ID_GAME_PARTICIPANT_ORDER = ID_USER_PACKET_ENUM+1,
    ID_GAME_STARTED,
    ID_DOOR_OPEN,
    ID_DOOR_CLOSE,
    ID_GENERATOR_ACTIVE,
};

#endif // NETCOMMON_H
