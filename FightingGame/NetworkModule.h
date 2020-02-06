#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <ggponet.h>

#pragma comment(lib, "Ws2_32.lib")

#include <string>
using namespace std;

class NetworkModule
{
public:
	bool StartSendingRequest(string ipString, string portString);
	bool StartListeningForRequests(string portString);
	bool InitializeGGPO();
};

