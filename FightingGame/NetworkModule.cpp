#include "NetworkModule.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define LISTEN_BACKLOG 5

bool NetworkModule::StartSendingRequest(string ipString, string portString)
{
	WSADATA wsaData;
	int iResult;
	printf("Start Client\n");
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	struct addrinfo* result = NULL, * ptr = NULL, hints;

	// set up info for the socket type
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	SOCKET ConnectSocket = INVALID_SOCKET;

	// convert ip string and port string
	int getAddrResult = getaddrinfo(ipString.c_str(), portString.c_str(), &hints, &result);
	
	

	// attempt connection
	int connectResult=0;
	
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		
		// create socket
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return false;
		}

		connectResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (connectResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	
	freeaddrinfo(result);
	struct sockaddr serverAddr;
	int serverAddrSize = (int)sizeof(struct sockaddr);
	char serverBuffer[30];

	

	getpeername(ConnectSocket, &serverAddr, &serverAddrSize);

	inet_ntop(serverAddr.sa_family,serverAddr.sa_data, serverBuffer, 30);

	printf("Client conntect: %d %s \n",connectResult, serverBuffer);

	if (connectResult == INVALID_SOCKET)
	{
		printf("Connection failed\n");
		WSACleanup();
		return false;
	}

	// Send message
	const char* msgBuffer = "send test";

	auto sendResult = send(ConnectSocket, msgBuffer, (int)strlen(msgBuffer), 0);
	printf("Sent: %d\n", sendResult);

	closesocket(ConnectSocket);
	WSACleanup();
	return true;
}

bool NetworkModule::StartListeningForRequests(string portString)
{
	WSADATA wsaData;
	int iResult;

	printf("Starting server.\n");

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	struct addrinfo* result = NULL, * ptr = NULL, hints;
	struct sockaddr clientAddr;
	// set up info for the socket type
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// convert ip string and port string
	int getAddrResult = getaddrinfo(NULL, portString.c_str(), &hints, &result);

	// create socket
	SOCKET listenSocket = INVALID_SOCKET;
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (listenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	// bind listen Socket
	int bindResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	// start listening
	int listenResult = listen(listenSocket, SOMAXCONN);
	printf("listen start\n");
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// accept connection
	socklen_t clientAddrSize = sizeof(clientAddr);
	SOCKET connectSocket = INVALID_SOCKET;

	while (connectSocket == INVALID_SOCKET)
	{
		connectSocket = accept(listenSocket, &clientAddr, &clientAddrSize);
	}

	if (connectSocket == INVALID_SOCKET)
	{
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}

	closesocket(listenSocket);

	// recieve message from client.
	char recvBuffer[300];
	recv(connectSocket, recvBuffer,sizeof recvBuffer, 0);

	printf("Recieved: %s\n",recvBuffer);

	return 1;
}