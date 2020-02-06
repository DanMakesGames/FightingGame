#include <iostream>
#include <fstream> 
#include <string>
#include "NetworkModule.h"
#include "GraphicsModule.h"
#define PORT_FILE "ipAndPort.txt"

#define DEFAULT_CLIENT_PORT "27666"
#define DEFAULT_SERVER_PORT "27666"

using namespace std;

int main(int argc, char** argv) {

	// read file to get ip and port
	char fileBuffer[100];
	bool bIsClient = false;
	NetworkModule netModule;
	ifstream is(PORT_FILE);
	
	/*
	if (!is.good())
	{
		printf("Error: Cannot open file: bad %d eof %d fail %d",is.bad(),is.eof(), is.fail());
		return 1;
	}
	*/
	
	// get ip
	is.getline(fileBuffer,100);
	string targetIp(fileBuffer);

	is.close();

	/*
	// loop attempt connection if port provided, otherwise listen for connection.
	// if the file is not empty;
	if (fileBuffer[0] != '\0' && argc == 1)
		bIsClient = true;
	*/
	/*
	if (bIsClient) {
		netModule.StartSendingRequest(targetIp, DEFAULT_CLIENT_PORT);
	}
	else {
		netModule.StartListeningForRequests(DEFAULT_SERVER_PORT);
	}
	*/

	
	GraphicsModule graphicsModule;
	graphicsModule.Initialize();

	// create network module

	// If connected. Create game and proceed. 
	

	return 0;
}