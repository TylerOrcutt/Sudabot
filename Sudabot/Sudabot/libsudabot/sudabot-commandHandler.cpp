/*
* SudaBot 
*			
*	6/../2014
*
*/
#include"sudabot-core.h"


void sudabot::handle_msg(string remote_user,string chan,string msg){
string data;
if(msg.substr(msg.length()-1,1)=="\n"){
msg=msg.substr(0,msg.length()-2);
}
cout<<timeStamp()<<"Command issued from "<<remote_user<<": "<<msg<<endl;

bool isAdmin=checkAdmin(remote_user);
if(msg==" "){
conn.sendData(preData("PRIVMSG "+chan+" :what can I do for you "+remote_user+"?\r\n"));
}
if(msg=="help"){
	showHelp(remote_user,chan);
}


if(msg.substr(0,4)=="say "){
conn.sendData(preData("PRIVMSG "+(string)channel+" :"+msg.substr(4)+"\r\n"));
}
if(msg.substr(0,4)=="roll"){
	
	roll(msg,chan,remote_user);
}
if(msg.substr(0,4)=="kick"){
	if(isAdmin){
	kick(remote_user,msg.substr(5),chan);
}}

if(msg.substr(0,5)=="about"){
string osinfo;
	#ifdef _WIN32 
		osinfo = "MS Windows";
	#endif
	
	#ifdef __linux__
		osinfo = "Linux";
	#endif

}
if(msg.substr(0,2)=="op"){
	if(isAdmin){
			string nad=getArg(msg.substr(3));
		if(nad!=""){
			op(nad);
		}
	}}
if(msg.substr(0,4)=="deop"){
	if(isAdmin){
			string nad=getArg(msg.substr(5));
		if(nad!=""){
			removeop(nad);
		}
	}}

if(msg.substr(0,6)=="addban"){
	if(isAdmin){
		string nad=getArg(msg.substr(7));
		if(nad!=""){
	       addBan(nad);
		}
	}}



if(msg.substr(0,8)=="addadmin"){
	if(isAdmin){
		string nad=getArg(msg.substr(9));
		if(nad!=""){
	       addadmin(nad);
		}
	}}

if(msg.substr(0,11)=="removeadmin"){
	if(isAdmin){
		string nad=getArg(msg.substr(12));
		if(nad!=""){
	       removeadmin(nad);
		}
	}}

if(msg=="showadmins"){
	if(isAdmin){
		string ams="Admins:";
		for(unsigned int i=0;i<Admins.size();i++){
			if(i>=Admins.size()-1){
			ams+=string(Admins[i]);
			}else{
			ams+=string(Admins[i])+",";
			}}
		conn.sendData(preData("PRIVMSG "+chan+" :"+ams+"\r\n"));

	}}

if(msg=="disable welcome"){
	if(isAdmin){
		Welcome_enabled=false;
	}}
if(msg=="enable welcome"){
	if(isAdmin){
		Welcome_enabled=true;
	}}
if(msg.substr(0,12)=="set welcome "){
	if(isAdmin){
		strcpy(Welcome_msg,msg.substr(12).c_str());
	}}



if(msg=="about"){

}
}


void sudabot::showHelp(string user,string chan){

	//conn.sendData(preData("PRIVMSG "+chan+" :Heres some of the commands I can do for you, "+user+".\r\n"));
	//conn.sendData(preData("PRIVMSG "+chan+" :all commands use the following context:\r\n"));
	//conn.sendData(preData("PRIVMSG "+chan+" :!"+string(alias)+" <command> <params>\r\n"));
	//conn.sendData(preData("PRIVMSG "+chan+" :roll <min> <max>	    rolls a die\r\n"));
	//conn.sendData(preData("PRIVMSG "+chan+" :about                  information about the bot\r\n"));
	/* if(checkAdmin(user)){
	conn.sendData(preData("PRIVMSG "+chan+" ::-------------------------------------------------:\r\n"));
	conn.sendData(preData("PRIVMSG "+chan+" ::             sudabot admin commands              :\r\n"));
	conn.sendData(preData("PRIVMSG "+chan+" ::-------------------------------------------------:\r\n"));
	conn.sendData(preData("PRIVMSG "+chan+" :kick <nick> <msg>      kicks client from channel\r\n"));
	conn.sendData(preData("PRIVMSG "+chan+" :op <nick>              gives user operator privileges\r\n"));
	conn.sendData(preData("PRIVMSG "+chan+" :deop <nick>            removes operator from a user\r\n"));
	conn.sendData(preData("PRIVMSG "+chan+" :addadmin <nick>        sets user to bot admin\r\n"));
	conn.sendData(preData("PRIVMSG "+chan+" :removeadmin <nick>     removes user from bot admin\r\n"));
	}
	conn.sendData(preData("PRIVMSG "+chan+" :also I can send dirty pictures to your mother =D.\r\n"));
	*/
	}

void sudabot::op(string user){

	//cout<<kuser<<"'"<<endl;
	if(user=="" || user==string(nick)){
	conn.sendData(preData("PRIVMSG "+string(channel)+" :cannot op that user\r\n"));
	return;
	}
	conn.sendData(preData("MODE "+string(channel)+" +o "+user+"\r\n"));
}
void sudabot::removeop(string user){

	if(user=="" || user==string(nick)){
	conn.sendData(preData("PRIVMSG "+string(channel)+" :cannot deop that user\r\n"));
	return;
	}
	conn.sendData(preData("MODE "+string(channel)+" -o "+user+"\r\n"));
}



void sudabot::kick(string user,string cmd,string chan){
	if(cmd.length()<2){return;}
	string kuser;
	for(unsigned int i=0;i<cmd.length() && cmd.substr(i,1)!=" ";i++){
		kuser+=cmd.substr(i,1);
	}
	//cout<<kuser<<"'"<<endl;
	if(kuser=="" || kuser==string(nick)){
	conn.sendData(preData("PRIVMSG "+chan+" :cannot kick that user\r\n"));
	return;
	}
	conn.sendData(preData("KICK "+string(channel)+" "+kuser+"\r\n"));

}




void sudabot::addadmin(string newadmin){
	char * na=(char*)malloc(80);
	strcpy(na,newadmin.c_str());
	Admins.push_back(na);
	saveAdmins();
}
void sudabot::removeadmin(string admin){
	
	for(unsigned int i=0;i<Admins.size();i++){
		if(string(Admins[i])==admin){
			Admins.erase(Admins.begin()+i);
			i--;
		}
	}

	saveAdmins();
}





void sudabot::roll(string msg,string chan,string remote_user,int min,int max){
	
	string arg1,arg2;
	unsigned int i;
	if(msg.length()>5){
	for(i=5;i<msg.length() &&msg.substr(i,1)!=" ";i++){
		arg1+=msg.substr(i,1);
	}
	i++;
	for(;i<msg.length() && msg.substr(i,1)!=" ";i++){
		arg2+=msg.substr(i,1);
	}
	if(atoi(arg1.c_str())){
	min=atoi(arg1.c_str());
	}
	if(atoi(arg2.c_str())){
	max=atoi(arg2.c_str());
	}
	if(min>max){max=100;min=1;}
	}

ostringstream s,range;
s<<rand()%max+min<<" ["<<min<<"-"<<max<<"]";
conn.sendData(preData("PRIVMSG "+chan+" :"+remote_user+" rolls "+s.str()+".\r\n"));
}

string sudabot::getArg(string data){
	if(data.length()<2){return "";}
	string kuser;
	for(unsigned int i=0;i<data.length() && data.substr(i,1)!=" ";i++){
		kuser+=data.substr(i,1);
	}
	return kuser;
}
