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

//#include "GameBoard.h"

class BattleshipAI
{
private:
	// GameBoard op_field;
	// GameBoard my_field;
	int x;
	int y;

	int cur_x;
	int cur_y;

	unsigned int state;


	std::string move();

public:
	BattleshipAI();
	//~BattleshipAI();

	std::string handler(std::string input);
};

#include "BattleshipAI.cpp"
#endif