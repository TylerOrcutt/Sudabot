/*
* SudaBot 
*	
*	6/../2014
*
*/
#ifndef LINUX_CON_H
#define LINUX_CON_H
#include<iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <time.h>
using namespace std;
class linuxcon{
private:
char *port;
int s;
struct addrinfo hints,*servinfo;

public:

bool start(char*,char*);
bool sendData(char*msg);
bool connected;
char *getData();
};
#endif

