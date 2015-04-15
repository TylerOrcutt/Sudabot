all: sudabot

sudabot: main.o sudabot-core.o linuxcon.o sudabot-commandHandler.o sudabot-config.o sudabot-admins.o sudabot-bans.o
	g++  main.o sudabot-core.o linuxcon.o sudabot-commandHandler.o sudabot-config.o sudabot-admins.o sudabot-bans.o -o sudabot

main.o: main.cpp
	g++ -c main.cpp

sudabot-core.o: libsudabot/sudabot-core.cpp
	g++ -c libsudabot/sudabot-core.cpp


linuxcon.o: libsudabot/linux/linuxcon.cpp
	g++ -c libsudabot/linux/linuxcon.cpp

sudabot-commandHandler.o: libsudabot/sudabot-commandHandler.cpp
	g++ -c  libsudabot/sudabot-commandHandler.cpp

sudabot-config.o: libsudabot/sudabot-config.cpp
	g++ -c  libsudabot/sudabot-config.cpp

sudabot-admins.o: libsudabot/sudabot-admins.cpp
	g++ -c  libsudabot/sudabot-admins.cpp
	
sudabot-bans.o: libsudabot/sudabot-bans.cpp
	g++ -c  libsudabot/sudabot-bans.cpp
clean:
	rm -rf *o sudabot
