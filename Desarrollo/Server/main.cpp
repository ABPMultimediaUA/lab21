 /*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "BitStream.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include "Kbhit.h"
#include "NatPunchthroughServer.h"
#include "CloudServerHelper.h"
#include "CloudClient.h"
#include "RakNetStatistics.h"
#include "RelayPlugin.h"

#include "NetCommon.h"

#define MAX_CONNECTIONS 32

//#define VERBOSE_LOGGING

using namespace RakNet;
using namespace std;

static int DEFAULT_RAKPEER_PORT=61111;

///////////////////////////
///////////////////////////
///////////////////////////
int main(int argc, char **argv)
{
	RakNet::RakPeerInterface *rakPeer=RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor sd;
	sd.port = DEFAULT_RAKPEER_PORT;
	//strcpy(sd.hostAddress,"127.0.0.1");  // Forzamos a red local

//	printf("Using IP: %s port: %i\n", sd.hostAddress, sd.port);


	if (rakPeer->Startup(8096,&sd,1)!=RakNet::RAKNET_STARTED)
	{
		printf("Failed to start rakPeer! Quitting\n");
		RakNet::RakPeerInterface::DestroyInstance(rakPeer);
		return 1;
	}
	rakPeer->SetTimeoutTime(5000, UNASSIGNED_SYSTEM_ADDRESS);
	rakPeer->SetMaximumIncomingConnections(MAX_CONNECTIONS);

	printf("Using IP: %s port: %i\n", rakPeer->GetLocalIP(0), sd.port);


    // NatPunchthroughServer /////////////////////////////
    NatPunchthroughServer* natPunchthroughServer;
    natPunchthroughServer = new NatPunchthroughServer;
    rakPeer->AttachPlugin(natPunchthroughServer);


    // CloudServer //////////////////////////////////////
    CloudServer* cloudServer;
    cloudServer = new CloudServer;
    rakPeer->AttachPlugin(cloudServer);
    CloudClient* cloudClient;
    cloudClient = new CloudClient;
    rakPeer->AttachPlugin(cloudClient);
    CloudServerHelperFilter* cloudServerHelperFilter;
    cloudServerHelperFilter = new CloudServerHelperFilter;
    cloudServer->AddQueryFilter(cloudServerHelperFilter);
    cloudServer->SetMaxUploadBytesPerClient(65535);
    CloudServerHelper cloudServerHelper;
    cloudServerHelper.OnConnectionCountChange(rakPeer, cloudClient);

    printf("\n---------------------\nPress q to quit.\nPress s fot statistics\n---------------------\n");



    ///////////////////////////////////////////
	RakNet::Packet *packet;
	bool quit=false;
	while (!quit)
	{
		for (packet=rakPeer->Receive(); packet; rakPeer->DeallocatePacket(packet), packet=rakPeer->Receive())
		{
            switch (packet->data[0])
            {
            case ID_NEW_INCOMING_CONNECTION:
                {
                    cloudServerHelper.OnConnectionCountChange(rakPeer, cloudClient);

                    unsigned short num;
                    rakPeer->GetConnectionList(0, &num);

                    // Envio el num de participante
                    RakNet::BitStream bsOut;
                    bsOut.Write((RakNet::MessageID)ID_GAME_PARTICIPANT_ORDER);
                    bsOut.Write(num);
                    rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
                    break;
                }
            case ID_CONNECTION_LOST:
            case ID_DISCONNECTION_NOTIFICATION:
                cloudServerHelper.OnConnectionCountChange(rakPeer, cloudClient);
                break;
            case ID_GAME_STARTED:
                std::cout << "\n\n ---------------- ID_GAME_STARTED --------------------- \n\n";
                break;
            }
		}

		if (kbhit())
		{
			char ch = getch();
			if (ch=='q')
			{
				quit=true;
			}
			else if (ch=='s')
			{
				RakNetStatistics rns;
				char message[2048];
				bool hasStatistics = rakPeer->GetStatistics(0, &rns);
				if (hasStatistics)
				{
					StatisticsToString(&rns, message, 2);
					printf("SYSTEM 0:\n%s\n", message);

					memset(&rns, 0, sizeof(RakNetStatistics));
					rakPeer->GetStatistics(UNASSIGNED_SYSTEM_ADDRESS, &rns);
					StatisticsToString(&rns, message, 2);
					printf("STAT SUM:\n%s\n", message);
				}
				else
				{
					printf("No system 0\n");
				}

				DataStructures::List<SystemAddress> addresses;
				DataStructures::List<RakNetGUID> guids;
				rakPeer->GetSystemList(addresses, guids);
				printf("%i systems connected\n", addresses.Size());
			}
			else if (ch=='d')
            {
                cout << "\n\nDebug\n=====\n";

                cout << "\n=====\n";
            }
		}
		RakSleep(30);
	}

	// NatPunchthroughServer ///////////////
	if (natPunchthroughServer)
    {
        rakPeer->DetachPlugin(natPunchthroughServer);
        delete natPunchthroughServer;
        natPunchthroughServer = 0;
    }


    // CloudServer /////////////////////////
    if (cloudServer)
    {
        rakPeer->DetachPlugin(cloudServer);
        delete cloudServer;
        cloudServer=0;
        rakPeer->DetachPlugin(cloudClient);
        delete cloudClient;
        cloudClient=0;
        delete cloudServerHelperFilter;
        cloudServerHelperFilter=0;
    }


    //////////////////
	rakPeer->Shutdown(100);
	RakNet::RakPeerInterface::DestroyInstance(rakPeer);
	return 0;
}
