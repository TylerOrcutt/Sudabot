/*
* SudaBot 
*		
*	6/../2014
*
* 
* 
*
*/
#include "wincon.h"
bool wincon::start(char * _server,char*_port){
	connected=false;
	port=_port;
	sock=INVALID_SOCKET;
	int iresult;
	if((iresult=WSAStartup(MAKEWORD(2,2),&wsaData))!=0){
		cout<<"Failed to init winsock\n";
		return false;
	}
	ZeroMemory(&hints,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=IPPROTO_TCP;

	if((iresult=getaddrinfo(_server,port,&hints,&result))!=0){
		cout<<"Could not find remote host\n";
		WSACleanup();
		return false;
	}
	sock=socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	if(sock==INVALID_SOCKET){
		cout<<"failed to init socket\n";
		WSACleanup();
		return false;

	}
	//get ip
 HOSTENT * phost;
	if(!(phost=gethostbyname(_server))){
		cout<<"could not resolve hostname\n";
		return false;
	}
	struct sockaddr_in s;
	s.sin_family=AF_INET;
	s.sin_port=htons(strtoul(port,NULL,0));
	s.sin_addr.s_addr=*((unsigned long*)phost->h_addr);

	iresult=connect(sock,(struct sockaddr *) &s,sizeof s);
	if(iresult<0){
		cout<<"failed to connect to remote host\n";
		return false;
	}

//	sendData("");
	connected=true;
	return true;
}


bool wincon::sendData(char * msg){
int len=strlen(msg);
int bytes_sent=send(sock,msg,len,0);
	if(bytes_sent==0){
	return false;
	//cout<<">>>failed to send message\n";
	}
//cout<<">>>sent message\n";
return true;
}



char * wincon::getData(){
int numbytes;
//char *buf = " ";
//int count=0;

char *buff=(char *)malloc(128);
numbytes=recv(sock,buff,128,0);

buff[numbytes]='\0';


if(numbytes<=0){
connected=false;
WSACleanup();
}
return buff;
}



char * wincon::getURLTitle(string url){
	//cout<<"looking up url...\n";
	int uport=80;
	if(url.substr(0,7)=="http://" ){
	url=url.substr(7);
	}else{
      url=url.substr(8);
	  int uport=8080;
	}
	string page;
	for(int i=0;i<url.length();i++){
		if(url.substr(i,1)=="/"){
		
			for(int k=i+1;k<=url.length();k++){
				page+=url.substr(k,1);
		}
				url=url.substr(0,i);
		//	cout<<url<<endl<<page<<endl;
			break;
		}
	}
		char *title;

		WSADATA wsa;
		ZeroMemory(&wsa,sizeof(wsa));
		int sockU;
		char *urlhost=(char*)malloc(url.length()+1);
		strcpy(urlhost,url.c_str());

	struct sockaddr_in  SockAddr;
	
		

		struct hostent *hst;
		char *htmlheader=(char*)malloc(500);
		strcpy(htmlheader,"GET /");
		strcat(htmlheader,page.c_str());
		strcat(htmlheader," HTTP/1.1\r\nHOST: ");
	//	strcat(htmlheader,"www.");
   	strcat(htmlheader,url.c_str());
	//strcat(htmlheader,"/b/thread/551214048/get-slappin");
		strcat(htmlheader,"\r\nConnection: close\r\n\r\n");
		if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
			return false; 
		}


		sockU=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		hst=gethostbyname(urlhost);
		
 HOSTENT * phost;
	if(!(phost=gethostbyname(urlhost))){
		cout<<"could not resolve hostname\n";
		return false;
	}
	struct sockaddr_in s;
	s.sin_family=AF_INET;
	s.sin_port=htons((short)uport);
	s.sin_addr.s_addr=*((unsigned long*)phost->h_addr);
		int iresult=connect(sockU,(struct sockaddr *) &s,sizeof s);
	if(iresult<0){
		cout<<"failed to connect to remote host\n";
		return false;
	}/**/

		send(sockU,htmlheader,strlen(htmlheader),0);
		char buff[500];
		int bytes;
		string t;
		while((bytes=recv(sockU,buff,sizeof(buff),0))>0){
			//cout<<buff<<endl;
			string data=string(buff);
			for(int i=0;i<=data.length();i++){
				if(data.substr(i,7)=="<title>"){
				for(int k=i+7;k<=data.length()&&data.substr(k,8)!="</title>";k++){
					t+=data.substr(k,1);
					}
				
				//	title=(char*)malloc(sizeof(t.length()+1));
				//	strcpy(title,t.c_str());
			
					closesocket(sockU);
					title=(char*)malloc(t.length()+1);

						strcpy(title,t.c_str());
	
			//	cout<<title<<endl;
						WSACleanup();
						return title;
						break;
				}

			}


		}/**/
		closesocket(sockU);
	title=(char*)malloc(80);
	title="N/A";
	//strcpy(title,t.c_str());
	
	//	cout<<t<<endl;
	WSACleanup();
		return title;

}