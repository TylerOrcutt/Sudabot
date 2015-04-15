#include"sudabot-core.h"
#include <fstream>
void sudabot::loadBans(){
	ifstream file("bans.conf");
	int totalbs=0;
	cout<<"Loading bans..\n";
	if(file.is_open()){
		char* ln=(char*)malloc(100);
		while(!file.eof()){

			file.getline(ln,100);
			string str=(string)ln;
			if(str!="" || str !=" " || str !="\n"|| !str.empty()){
				Bans.push_back(str);
				totalbs++;
			}
		}
		file.close();


	}else{
		ofstream file("bans.conf");
		file.close();

	}
	cout<<"Total bans:"<<totalbs<<endl;
}

void sudabot::saveBans(){
	ofstream file("bans.conf");
	if(file.is_open()){
	
		for(int i=0;i<Bans.size();i++){
			if(i>=Admins.size()-1){
			file<<Bans[i];
			}else{
				file<<Bans[i]<<endl;
			}


		}


	file.close();
	}


}

bool sudabot::checkBan(string nick){
	for(int i=0;i<Bans.size();i++){
		if(Bans[i]==nick){
			return true;
		}
	}


	return false;

}

void sudabot::addBan(string nick){
	Bans.push_back(nick);
	saveBans();

}