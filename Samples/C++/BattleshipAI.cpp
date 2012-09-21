/*
	Sample Battleship AI in C++

	BattleshipAI.cpp
*/

#include "BattleshipAI.h"


BattleshipAI::BattleshipAI()
{
	state = Idle;
}

string BattleshipAI::handler(string raw_in)
{
	vector<string> msg = parse(raw_in);
	// Typical in, MSGTYPE:sender:recipient:message
	string sender = msg[1];
	string recipient = msg[2];
	string input = msg[3];

	string output = "";

	switch(state)
	{
		case Idle:
			if(input == "[start]")
			{
				state = Prep;
				output = "PRIVMSG:" + recipient + ":!bs-test\n";
			}
			break;

		case Prep:
			//if(recipient ==  )
			//startNewGame();
			output = "PRIVMSG:" + msg[2] + ":" + move();
			break;
	}

	return output;
}


string BattleshipAI::move()
{

	return "";
}


vector<string> BattleshipAI::parse(string in)
{
	string sec = "";
	vector<string> ret;
	int l = in.length();
	for(int i = 0; i < l; ++i)
	{
		if(in[i] == ':')
		{
			ret.push_back(sec);
			sec = "";
		}
		else
		{
			sec += in[i];
		}
	}
	ret.push_back(sec);
	return ret;
}
