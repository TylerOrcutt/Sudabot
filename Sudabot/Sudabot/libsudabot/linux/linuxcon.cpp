/*
* SudaBot 
*		
*	6/../2014
*
*/
#include "linuxcon.h"

bool linuxcon::start(char*_server,char*_port){
//cout<<"Connecting to "<<_server<<":"<<port<<endl;
port=_port;
memset(&hints,0,sizeof hints);
hints.ai_family=AF_UNSPEC;//use ipv4 or ipv6
hints.ai_socktype=SOCK_STREAM;//tcp socket
int res;
//
if((res=getaddrinfo(_server,port,&hints,&servinfo))!=0){
	cout<<"host not found.\n";	
	return false;
	}
//setup socket
s=socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);
if(s==-1){
	cout<<"socket error.\n";
	return false;
}

if(connect(s,servinfo->ai_addr,servinfo->ai_addrlen)==-1){
//close(s);
cout<<"Unable to connect.\n";
return false;
}
connected=true;

return true;
}


char * linuxcon::getData(){

int numbytes;
char *buf = (char*)malloc(sizeof(char)*100);
//int count=0;
numbytes=recv(s,buf,100-1,0);
buf[numbytes]='\0';

//cout<<buff;
if(numbytes==0){
connected=false;
}
return buf;

}



bool linuxcon::sendData(char * msg){
int len=strlen(msg);
int bytes_sent=send(s,msg,len,0);
	if(bytes_sent==0){
	return false;
	cout<<">>>failed to send message\n";
	}
//cout<<">>>sent message\n";
return true;
}




