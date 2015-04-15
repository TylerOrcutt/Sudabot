/*
* SudaBot 
*		
*	6/../2014
*
*/
#include"sudabot-core.h"
#include<fstream>
#include<string.h>
void sudabot::loadConfig(){

	ifstream file("sudabot.conf");
	if(file.is_open()){
		char line[100];
		while(!file.eof()){
			file.getline(line,100);
//			cout<<line<<endl;
//process line
		string ln=string(line);//convert line to a string 
		//because i feel it is ezer that way so fuck it, i do what i want lol
		//need more tea, beer time soon...
//		cout<<ln<<endl;
		if(ln.substr(0,2)!="//"){
			if(ln.substr(0,7)=="server="){
				server=config_getValue(ln.substr(7));
				cout<<"SERVER:"<<server<<endl;
			}
				if(ln.substr(0,5)=="port="){
				port=config_getValue(ln.substr(5));
				cout<<"PORT:"<<port<<endl;
			}
				if(ln.substr(0,8)=="channel="){
				channel=config_getValue(ln.substr(8));
				cout<<"Channel:"<<channel<<endl;
			}

				if(ln.substr(0,6)=="nicks="){
				nick=config_getValue(ln.substr(6));
				cout<<"Nick:"<<nick<<endl;
			}

				if(ln.substr(0,11)=="use_passwd="){
						char *upw=config_getValue(ln.substr(11));
						if(string(upw)=="false"){
							
							use_password=false;
						}else{
							use_password=true;
						}
				cout<<"use_password:"<<use_password<<endl;
			 }

				if(ln.substr(0,7)=="passwd="){
				passwd=config_getValue(ln.substr(7));
				cout<<"passwd:*****"<<endl;
				}

				if(ln.substr(0,6)=="alias="){
				alias=config_getValue(ln.substr(6));
				cout<<"alias:!"<<alias<<endl;
				}
					if(ln.substr(0,6)=="owner="){
				owner=config_getValue(ln.substr(6));
				cout<<"owner:"<<owner<<endl;
				}

					if(ln.substr(0,16)=="Welcome_enabled="){
				Welcome_enabled=config_getValue(ln.substr(16));
				cout<<"Welcome_enabled:"<<Welcome_enabled<<endl;
				}

				if(ln.substr(0,12)=="Welcome_msg="){
		    	string msg;
				
				for(unsigned int i=13;i<ln.length()  && ln.substr(i,1)!="\"" && ln.substr(i,1)!="\n" ;i++){
						msg+=ln.substr(i,1);
					}
				Welcome_msg=(char*)malloc(100);
					strcpy(Welcome_msg,msg.c_str());

				cout<<"Welcome_msg:"<<Welcome_msg<<endl;
				}

		}

		//next line
		}
	
		file.close();

	}else{
		createConfig();
	}
		


}
char * sudabot::config_getValue(string data){
	
	string v;
	for(unsigned int i=0;i<data.length() && data.substr(i,2)!="//" && data.substr(i,1)!="\n"&& data.substr(i,1)!=" ";i++){
		v+=data.substr(i,1);

	}

	char *value=(char*)malloc(v.length()+1);
	strcpy(value,v.c_str());
	return value;
}

void sudabot::createConfig(){
	cout<<timeStamp()<<"Load failed. Creating example config...\n";
	ofstream file("sudabot.conf");
	if(file.is_open()){
		file<<"//Sudabot - an ircbot for Linix and Windows"<<endl;
		file<<"//  example sudabot.conf"<<endl;
		file<<"//"<<endl;
		file<<"server=irc.mibbit.net"<<endl;
		file<<"port=6667"<<endl;
		file<<"channel=#sudatest"<<endl;
		file<<"nicks=sudabot"<<endl;
		file<<"use_passwd=true"<<endl;
		file<<"passwd=password"<<endl;
		file<<"alias=suda"<<endl;
		file<<"owner=ty"<<endl;
			file<<endl;
			file<<endl;
		file<<"Welcome_enabled=true"<<endl;
		file<<"Welcome_msg=\"Welcome $user to the irc channel:$channel!\""<<endl;
		file.close();
	}

	
}


void sudabot::set_conf_defaults(){
	channel="#sudatest";
//usr="sudabot";
	owner="ty";
	nick="sudabot";
	passwd="password";
	alias="suda";
	server="irc.mibbit.net";
	port="6667";

	Welcome_msg="Welcome $user to the irc channel:$channel!";
	Welcome_enabled=true;
}


void sudabot::showStartup(){


}

