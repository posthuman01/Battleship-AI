/*
	Sample Battleship AI in C++

	BattleshipAI.h
*/
#ifndef BATTLESHIP_AI
#define BATTLESHIP_AI

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "GameBoard.h"

using namespace std;

class BattleshipAI
{
private:
	//GameBoard op_field;
	//GameBoard my_field;

	enum State {
		Config,
		Idle,
		Prep,
		Search,
		Engage
	};

	State state;

	string channel;
	string referee;
	string nick;


	string move();

public:
	BattleshipAI();
	//~BattleshipAI();

	string handler(string input);

	static vector<string> parse(string);
};

#include "BattleshipAI.cpp"
#endif