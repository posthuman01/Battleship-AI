#include <iostream>
#include <string>
#include <fstream>

#ifndef GAMESERV
#define GAMESERV

class GameServ
{
private:
	unsigned int game_state;
	
	string player1;
	string player2;
	
public:
	GameServ();
	~GameServ();

	string handler(string);
	
	
	static std::vector<std::string> parse(std::string);
};


#include "BattleshipAI.cpp"
#endif
