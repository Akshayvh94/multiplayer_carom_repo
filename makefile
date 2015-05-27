################################# To define Port by default
ifndef PORT
	PORT = 27015
endif
################################ To define Address
ifndef ADDRESS
	ADDRESS = localhost
endif
################################ To define number of players
ifndef NUM_PLAYERS
	NUM_PLAYERS = 2
endif
############################### To define the default level 
ifndef LEVEL
	LEVEL = 2
endif
############################### To define default MODE
ifndef SINGLEPLAYER
	SINGLEPLAYER = 1
endif
############################## To define default number of players in multiplayer mode
ifndef FRICTION
	FRICTION = 3 
endif
############################## To define the maximum power
ifndef POWER
	POWER = 150 
endif
############################## To define coefficient restitution
ifndef RESTITUTION
	RESTITUTION = 1
endif
############################## To define multiplayer mode
ifndef MULTIPLAYER
	MULTIPLAYER = 2
endif
############################## end 
custom_header = "\#define BOARD_FR  $(FRICTION)\n\
		  \#define MAX_POWER $(POWER)\n\
		  \#define RESTITUITION $(RESTITUTION)\n"
build:
	 echo $(custom_header) > inc/config.h
	 clear
	 g++ -o carom_multiplayer src/physics/*.cpp src/input/*.cpp src/display/*.cpp src/main/main.cpp src/initializer/*.cpp src/rules/*.cpp src/networking/networking.cpp src/threads/*.cpp src/AI/*.cpp -Wall  -w -lGLU -lglut -lGL
	
carom_singleplayer: 
	 echo $(custom_header) > inc/config.h
	 clear
	 g++ -o carom_singleplayer src/physics/*.cpp src/input/*.cpp src/display/*.cpp src/main/main.cpp src/initializer/*.cpp src/rules/*.cpp src/networking/networking.cpp src/threads/*.cpp src/AI/*.cpp -Wall  -w -lGLU -lglut -lGL
	 ./carom_singleplayer $(ADDRESS) $(PORT) $(SINGLEPLAYER) $(LEVEL)

carom_multiplayer:
	 echo $(custom_header) > inc/config.h
	 clear
	 g++ -o carom_multiplayer src/physics/*.cpp src/input/*.cpp src/display/*.cpp src/main/main.cpp src/initializer/*.cpp src/rules/*.cpp src/networking/networking.cpp src/threads/*.cpp src/AI/*.cpp -Wall  -w -lGLU -lglut -lGL
	 ./carom_multiplayer $(ADDRESS) $(PORT) $(MULTIPLAYER)

carom_server:
	 clear
	 g++ -w -o server src/server/server.cpp
	 ./server $(PORT) $(NUM_PLAYERS) $(LEVEL)
.PHONY:clean
clean:
	 rm -f carom_singleplayer carom_multiplayer carom_server
