//#undef UNICODE

//This needs to be defined for somereason and before the <winsock2.h>
//Most likely because function calls conflict in namespace with winsock1 and winsock2
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fstream>
#include <iostream>
//#include "C:\Users\Dalton\Builds\Official\OpenCV2.4\opencv\build\include\opencv2\core\core.hpp"


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib") 

#define BUFLEN 512
#define DEFAULT_PORT "27015"


using namespace std;

int __cdecl main(void) {

	//Initialize Window Sockets API (WSA)
	WSADATA API;
	int returnValue;

	//Create two sockets identifiers, one for listening to the client and one for sending information back to the client
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	WORD Version = MAKEWORD(2, 2);
	returnValue = WSAStartup(Version, &API);
	if (returnValue == 0) {
		cout << "API initialized properly" << endl;
	}
	else {
		cout << "API failed to initialize" << endl;
	}

	//create addrinfo hints to get client info and result to store client info
	addrinfo *result = NULL;
	addrinfo hints;

	//Zero out the memory of address so no funny business happens
	SecureZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	//the socket address will be used in a call to the bind function (flag set)
	hints.ai_flags = AI_PASSIVE;

	//Get the address information of the host running the server
	returnValue = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (returnValue == 0) {
		cout << "host server address information gathered successfully" << endl;
	}
	else {
		cout << "could not get the host (server) address information" << endl;
		cout << WSAGetLastError() << endl;
	}

	//create a listening socket that the client will be able to connect to
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		cout << "socket descriptor for the listening socket could not be created" << endl;
		cout << WSAGetLastError() << endl;
	}
	else {
		cout << "Listening socket descriptor successfully made" << endl;
	}

	//bind the listening socket to the host(server) machine
	//This must be called before any listen() functions may be called
	returnValue = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (returnValue == 0) {
		cout << "Successfully bound the listening socket to the host server machine" << endl;
	}
	else {
		cout << "Binding the host machines IP Address to the listening socket failed" << endl;
		cout << WSAGetLastError() << endl;
	}

	//place the listen socket in a state in which it is listening for the incoming connection
	returnValue = listen(ListenSocket, SOMAXCONN);
	//SOMAXCONN means the service provider is responsible for the maximum lenght of the queue of pending connections
	if (returnValue == 0) {
		cout << "the listen socket has been successfully put in a state ready to listen to incoming connections" << endl;
	}
	else {
		cout << "the listen socket was not put in a state ready for listening to incoming connections" << endl;
		cout << WSAGetLastError() << endl;
	}

	cout << endl << endl << "listening for connection..." << endl << endl;

	//Make a client socket and permit an incoming connection attempt on that socket by using the accept() function
	//The connection to the client is actually made with the value socket return by the accept funciton
	//However, a listening socket needs to be made and passed to the accept function to get this socket
	//The last two parameters store the incoming address information and are optional
	//The accept function waits until the client actually tries to connect to the server
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		cout << "could not create an accepting socket for the client with the listening socket" << endl;
		cout << WSAGetLastError() << endl;
	}
	else {
		cout << "Successfully created an accepting socket to recieve info from client using the listening socket created before" << endl;
	}
	

	cout << endl << endl << "Accepting connection from client..." << endl << endl;

	//no longer need the listen socket but still need the client socket
	closesocket(ListenSocket);

	//Receive information until client ends the connection
	int iSendResult;
	char recvbuf[BUFLEN];
	int recvbuflen = BUFLEN;

	do {
		returnValue = recv(ClientSocket, recvbuf, recvbuflen, 0);
		//if the returnValue is greater than 1 then info is being received
		if (returnValue > 0) {
			cout << returnValue << " Bytes recieved by the client" << endl;
			ofstream out;
			out.open("test.txt");
			out.write(recvbuf, sizeof(recvbuf));
			out.close();
			//now that we recieved information, we will send it back to the client
			iSendResult = send(ClientSocket, recvbuf, returnValue, 0);
			if (iSendResult == SOCKET_ERROR) {
				cout << "could not send back the data to the client" << endl;
			}
			else {
				cout << iSendResult << " Bytes sent back to the client" << endl;
			}
		}
		else if (returnValue == 0) {
			cout << "closing connection" << endl;
		}
		else {
			cout << "an error occured when trying to recieve the information from the client" << endl;
			cout << WSAGetLastError() << endl;
		}
	} while (returnValue > 0);

	//Shutdown the connection
	returnValue = shutdown(ClientSocket, SD_BOTH);
	if (returnValue == SOCKET_ERROR) {
		cout << "an error occured when trying to shutdown the clientsocket" << endl;
		cout << WSAGetLastError() << endl;
	}
	else {
		cout << "Shutdown of the client socket was successful" << endl;
	}

	closesocket(ClientSocket);
	WSACleanup();

	system("pause");

	return 0;
}