/*
* Sudabot-core
*			
*	8/28/2014
*
*/
#include "sudabot-core.h"
void sudabot::init(){
//cout<<sudabot_version<<endl;
		cout<<timeStamp()<<"Starting bot...\n";
cout<<timeStamp()<<"Loading bot config....\n";
set_conf_defaults();
loadConfig();
loadAdmins();
loadBans();
reconnecting=false;

//cout<<conn.getURLTitle("https://www.youtube.com/watch?v=3A2IXsB7C0Q")<<endl;

}
void sudabot::start(){
	srand(time(NULL));
	
if(!conn.start(server,port)){
	if(!reconnecting){
		reconnect();
	}
	return;
}else{
	reconnecting=false;
}/**/



int numbytes;
char *buff;
int count=0;
while(1){
if(conn.connected==false){
cout<<timeStamp()<<"Connection Lost...\n";
if(!reconnecting){
reconnect();
}
break;
}

count++;
buff=conn.getData();
//cout<<buff;
switch(count){

case 2:conn.sendData(preData("NICK "+string(nick)+"\r\n"));
	cout<<timeStamp()<<"Sending nick...\n";   
conn.sendData(preData("USER "+string(nick)+" "+string(nick)+".com SB: "+string(nick)+"\r\n"));
     //conn.sendData("sudabot\r\n");
	//sendData("msg nickserv identify asdasd1\r\n");
	break;
case 3: conn.sendData(preData("USER "+string(nick)+" "+string(nick)+".com SB: "+string(nick)+"\r\n"));
break;


}


if (charSearch(buff,"End of MOTD") || charSearch(buff,"MOTD") ){

	conn.sendData(preData("JOIN "+string(channel)+"\r\n"));
	cout<<timeStamp()<<"Joning channel "<<channel<<"\n";

}else if (charSearch(buff,":NickServ!") && use_password){
	conn.sendData(preData("msg nickserv identify "+string(passwd)+"\r\n"));
	cout<<timeStamp()<<"Sending Nickserv Identification\n"; 

//}else if (charSearch(buff,"PING :")){
}else if (string(buff).substr(0,6)=="PING :"){
	      sendPong(buff);
	conn.sendData(preData("JOIN "+string(channel)+"\r\n"));
	cout<<timeStamp()<<"Joning channel "<<channel<<"\n";
}else if (charSearch(buff,"recognized") || charSearch(buff,"accepted")||charSearch(buff,"Password") ){
		  conn.sendData(preData("JOIN "+string(channel)+"\r\n"));
          cout<<timeStamp()<<"Joning channel #"<<channel<<"\n";
        }else{
		check_msg(buff);
		}



}



}


void sudabot::check_msg(char*data){
string str(data);
string remote_user;
string msg;
string chan;
//get user whom sent the message
//if(str.substr(0,1)==":"){
for(int i=1;i<str.length() && str.substr(i,1)!="!";i++){
	remote_user+=str.substr(i,1);
}
//}
//get message
for(int i=1;i<str.length();i++){
	if(str.substr(i,1)==":"){	
	msg=str.substr(i+1);
	str=str.substr(0,i);//remove message from data string
	break;
	}
}
if(msg.length()<2){return;}
if(msg.substr(msg.length()-1,1)=="\n"){
msg=msg.substr(0,msg.length()-2);
}
if(msg.substr(0,7)=="http://" || msg.substr(0,8)=="https://" ){
#ifdef _WIN32	
	conn.sendData(preData("PRIVMSG "+string(channel)+" :"+string(conn.getURLTitle(msg))+"\r\n")); 
#endif
//	cout<<conn.getURLTitle(msg)<<endl;
//	cout<<"'"<<msg<<"'"<<endl;
}

//get channel
for(int i=1;i<str.length();i++){
	if(str.substr(i,8)=="PRIVMSG "){
		for(int k=i+8;k<str.length() && str.substr(k,2)!=" :";k++){
			chan+=str.substr(k,1);
		}
		
	}
//KICK check if bot has been kicked
	if(str.substr(i,5)=="KICK "){
//---CLUGY needs to be fixed
		//cout<<str<<endl;
		if(str.substr(str.length()-(string(alias).length()+4),string(alias).length())==string(alias)){
			//bot has been kicked from channel rejoin
			conn.sendData(preData("JOIN "+string(channel)+"\r\n"));
			cout<<timeStamp()<<"kicked from channel."<<channel<<"\n";
		}
	}
//USER QUIT CHANNEL
		if(str.substr(i,5)=="PART "){
		for(int k=i+5;k<str.length() && str.substr(k,2)!=" :";k++){
			chan+=str.substr(k,1);
		}
		//cout<<str<<endl;
		cout<<timeStamp()<<remote_user<<" has left "<<chan<<"\n";
		}

//USER JOINED CHANNED	
	if(str.substr(i,5)=="JOIN "){
		chan=msg;
//	cout<<str<<endl;
		if(remote_user==string(nick)){
			cout<<timeStamp()<<"joined channel "<<channel<<endl;
		}else{
		cout<<timeStamp()<<remote_user<<" has joined "<<chan<<"\n";
		}
		if(checkBan(remote_user)){
			kick("",remote_user,"");
			cout<<timeStamp()<<remote_user<<" kicked - on ban list. "<<chan<<"\n";
		}else{
		
			if(checkAdmin(remote_user)){
			op(remote_user);
			cout<<timeStamp()<<"Giving OPs to "<<remote_user<<endl;
		}
//Send WELCOME MSG


		if(Welcome_enabled){
			string wmsg=string(Welcome_msg);
			int i;
			for( i=0;i<=wmsg.length();i++){
				if(wmsg.substr(i,5)=="$user"){
					wmsg.replace(i,5,remote_user);
				}
				if(wmsg.substr(i,8)=="$channel"){
					wmsg.replace(i,8,string(channel));
				}
			}
			conn.sendData(preData("PRIVMSG "+chan+" :"+wmsg+"\r\n"));
		}
		}//else checkbans
	}
	

}
//dont want to pm outselfs 
if(chan==string(nick)){
	chan=remote_user;
}


	//HANDLE COMMAND
if(msg.substr(0,string(alias).length()+1)=="!"+string(alias)){
	//cout<<">>HANDLING MESSAGE\n";
	if(msg.length()>string(alias).length()+2){
	handle_msg(remote_user,chan,msg.substr(string(alias).length()+2));
	}else{
		handle_msg(remote_user,chan," ");
	}
}
//HANDLE PM COMMAND
if(chan==remote_user){
	handle_msg(remote_user,chan,msg);
}


}



//prepare data
char* sudabot::preData(string data){
	char *ndata=new char[data.length()+1];
	strcpy(ndata,data.c_str());

	return ndata;

}



void sudabot::reconnect(){
	long lastattempt=time(0);
	int tries=10;
	reconnecting=true;
	for(int i=0;i<tries && conn.connected==false;){
		if((time(0)-lastattempt)>=10){
		lastattempt=time(0);
		i++;
			cout<<timeStamp()<<"Attempting to reconnect..\n";
			start();
		}

	}

}






bool sudabot::charSearch(char *toSearch, char *searchFor)
{
    int len = strlen(toSearch);
    int forLen = strlen(searchFor); // The length of the searchfor field
 
    //Search through each char in toSearch
    for (int i = 0; i < len;i++)
    {
        //If the active char is equil to the first search item then search toSearch
        if (searchFor[0] == toSearch[i])
        {
            bool found = true;
            //search the char array for search field
            for (int x = 1; x < forLen; x++)
            {
                if (toSearch[i+x]!=searchFor[x])
                {
                    found = false;
                }
            }
 
            //if found return true;
            if (found == true)
                return true;
        }
    }
 
    return 0;
}





void sudabot::sendPong(char *buf)
{
buf[0]='P';
buf[1]='O';
buf[2]='N';
buf[3]='G';
buf[4]=' ';
 //send the pong
 if (conn.sendData(buf))
     {
		
		 cout<< timeStamp()<<"PING from server\n";
     }
 
}

char *sudabot::timeStamp()
{//returns the current date and time
    time_t t;
    struct tm * ti;
	 time ( &t );
    ti = localtime ( &t );
char *buff=(char*)malloc(80);
strftime(buff,80,"%Y-%m-%d  %H:%M:%S :",ti);
return buff;
}
