// Client_JOHN.cpp UDP

#include "pch.h"
#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

#define MESSAGE_BUFFER 4096
#define PORT 7777

char buffer[MESSAGE_BUFFER];
char message[MESSAGE_BUFFER];

SOCKET sockd;
struct sockaddr_in server_address;
WSAData wsadata;


void clientRequest() {
	//--------Checking of systems Windows ------
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		exit(1);
	}
	//------------------------------------------

	//-------- The filling into a struct of the serveraddress ---------
	
	//server_address.sin_addr.s_addr = inet_addr ("127.0.0.1"); -- Так уже нельзя
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr.s_addr);//Preferred option
	server_address.sin_port = htons(PORT);
	server_address.sin_family = AF_INET;
	//-----------------------------------------------------------------


	//------- Creating of the Socket ----------
	sockd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockd == INVALID_SOCKET) {//  Socket's Checking   
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(sockd);
		WSACleanup();
		exit(1);
	}
	else {
		cout << "Client socket initialization is OK" << endl;
	}
	//------------------------------------------


	//--- Recieving and sending of messages ------------
	cout << "Enter your request to the server: ";
	cin >> message;
	sendto(sockd, message, MESSAGE_BUFFER, 0, (sockaddr*)&server_address, sizeof(server_address));
	recvfrom(sockd, buffer, sizeof(buffer),0,0,0);
	cout << "server's message: " << buffer << endl;
	closesocket(sockd);
	//--------------------------------------------------

	closesocket(sockd);
	WSACleanup();

};



int main()
{
	cout << "Client starting:" << endl;
	clientRequest();
}
