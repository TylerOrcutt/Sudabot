/*
* SudaBot-core
*		
*	6/../2014
*
*/
#ifndef SUDABOT_H_
#define SUDABOT_H_


#include<iostream>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include <sstream>
#include<vector>
using namespace std;

#ifdef __linux__
#include "linux/linuxcon.h"
#endif
#ifdef _WIN32
#include "windows/wincon.h"
#endif
class sudabot{
private:
char *nick;
char * usr;
char *passwd;
char * channel;
char *alias;
bool use_password;
char *server;
char *port;
char *owner;
vector<char *> Admins;
vector<string>Bans;
char * Welcome_msg;
bool Welcome_enabled;



bool reconnecting;
public:
	void init();
void start();
void reconnect();

bool charSearch(char*,char*);
void sendPong(char*);
char *timeStamp();
void check_msg(char*);
void handle_msg(string,string,string);
char* preData(string);

//config functions in config.cpp
void loadConfig();
void createConfig();
void showStartup();
char* config_getValue(string);
void set_conf_defaults();

//
//command functions located in commandHandler.h
void roll(string,string,string,int min=1,int max=100);
void showHelp(string,string);
void kick(string,string,string);
void op(string);
void removeop(string);
void addadmin(string);
void removeadmin(string);
string getArg(string);

//end commands

//admin handle
void loadAdmins();
void saveAdmins();
bool checkAdmin(string);

//
void loadBans();
void saveBans();
bool checkBan(string);
void addBan(string);



#ifdef __linux__
linuxcon conn;
#endif
#ifdef _WIN32
wincon conn;
#endif

};
#endif
