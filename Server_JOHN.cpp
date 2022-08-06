// Server_JOHN.cpp UDP
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
struct sockaddr_in serveraddress, client;//Structs
int errState;//State of ERR
WSAData wsadata; // Структура WSADATA содержит сведения о реализации сокетов Windows.

//Параметр MAKEWORD(2, 2) WSAStartup запрашивает версию 2.2 Winsock в системе
//и задает переданную версию в качестве самой высокой версии Windows Sockets поддержки,
//которую может использовать вызывающий объект.

void processRequest() {
	
	//--------Checking of systems Windows ------
	errState = WSAStartup(MAKEWORD(2, 2), &wsadata);// Функция WSAStartup вызывается для запуска использования WS2_32.dll.

	if (errState != 0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		exit(1);
	}
	
	//------------------------------------------

	//------- Creating of the Socket ----------
	sockd = socket(AF_INET,SOCK_DGRAM,0);
			//or (sockd == -1)
	if (sockd == INVALID_SOCKET) {//  Socket's Checking   
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(sockd);
		WSACleanup();
		exit(1);
	}
	else {
		cout << "Server socket initialization is OK" << endl;
	}
	//------------------------------------------
	
	//-------- The filling into a struct of the serveraddress ---------

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddress.sin_port = htons(PORT);

	//-----------------------------------------------------------------


	//-------------- Sock's binding -----------------------------------
	//Для привязки созданного сокета к IP-адресу и номеру порта служит системный вызов bind().
				//	|---Приведение типа sockaddr_in К sockaddr
	bind(sockd, (sockaddr*)&serveraddress, sizeof(serveraddress));

	//-----------------------------------------------------------------
	int length = sizeof(client);// This var needed for client's length  
	
	
	
	//--- Recieving and sending of messages ------------
	recvfrom(sockd,buffer,sizeof(buffer), 0, (struct sockaddr*)&client, &length);
	
	cout << "Client's message: "<< buffer << endl;
	cout << "Enter message to client: ";
	cin >> message;
	sendto(sockd,message,sizeof(message),0, (sockaddr*)&client, sizeof(client));

	//--------------------------------------------------
	
	closesocket(sockd);
	WSACleanup();
}

int main() {

	cout<< "Starting serer: " <<endl;
	processRequest();

	return 0;
}