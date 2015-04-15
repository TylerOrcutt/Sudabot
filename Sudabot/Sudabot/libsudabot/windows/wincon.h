/*
* SudaBot 
*			
*	6/../2014
*
*/
#ifndef WIN_CON_H
#define WIN_CON_H
#include<iostream>

#include<WinSock2.h>
#include<WS2tcpip.h>
#include<stdlib.h>
#include<stdio.h>
#include <string>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")
using namespace std;
class wincon{
	private:
char *port;
int s;
WSADATA wsaData;
int sock;
struct addrinfo hints,*result,*ptr;
//struct addrinfo hints,*servinfo;

public:

bool start(char*,char*);
bool sendData(char*msg);
bool connected;
char * getData();
char * getURLTitle(string);
};


#endif