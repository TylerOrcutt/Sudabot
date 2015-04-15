/*
* SudaBot 
*		
*	6/2014
*
*/
#include <iostream>
#include "libsudabot/sudabot-core.h"

using namespace std;

void handle_args(int args,char *argv[]);
int main(int args, char *argv[])
{
#ifdef _WIN32
	system("title Sudabot");
#endif
    if(args>1){
	handle_args(args,argv);
	}

sudabot bot;
bot.init();
bot.start();


#ifdef _WIN32
system("pause");
#endif
    return 0;
}

void handle_args(int args,char*argv[]){


}
