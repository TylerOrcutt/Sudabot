/*
* SudaBot 
*	
*	6/../2014
*
*/
#include "sudabot-core.h"
#include <fstream>

void sudabot::loadAdmins(){
	ifstream file("admins.conf");
	if(file.is_open()){
		char *line=(char*)malloc(80);
		while(!file.eof()){
			file.getline(line,80);
			string s=string(line);
			
			if(s!=" " || s!=""|| s!="\n" || !s.empty()){
			char * buff=(char*)malloc(80);
			strcpy(buff,s.c_str());
			Admins.push_back(buff);
			}

		}

		file.close();
	}else{
		ofstream file("admins.conf");
		file.close();
	}
	int i;
for( i=0;i<Admins.size();i++){
	if(string(Admins[i])==""){
		Admins.erase(Admins.begin()+i);
	}else{
	//cout<<Admins[i]<<endl;
	}
	}
cout<<"Total admins:"<<i<<endl;
}


void sudabot::saveAdmins(){
	ofstream file("admins.conf");
	if(file.is_open()){
		for(int i=0;i<Admins.size();i++){
			if(i>=Admins.size()-1){
				file<<Admins[i];
			}else{
			file<<Admins[i]<<endl;
			}}
		file.close();
	}
}

bool sudabot::checkAdmin(string user){
	if(string(owner)==user){
		return true;
	}
	for(int i=0;i<Admins.size();i++){
		if(user==string(Admins[i])){
			return true;
		}}


	return false;
}
