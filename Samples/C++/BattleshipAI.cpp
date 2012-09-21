/*
	Sample Battleship AI in C++

	BattleshipAI.cpp
*/

#include "BattleshipAI.h"


BattleshipAI::BattleshipAI()
{
	x = 10;
	y = 10;
	cur_x = 0;
	cur_y = 0;
	state = 0;
}

string BattleshipAI::handler(string in)
{
	vector<string> msg = parse(in);
	// Typical in, MSGTYPE:sender:recipient:message

	string output = "";

	switch(state)
	{
		case 0:
			if(msg[3] == "[start]")
			{
				state = 1;
				output = "PRIVMSG:" + msg[2] + ":" + move();
			}
			break;

		case 1:
			output = "PRIVMSG:" + msg[2] + ":" + move();
			break;
	}

	return output;
}


string BattleshipAI::move()
{
	if(cur_x == x)
	{
		if(cur_y == y)
		{
			state = 0;
			cur_y = 0;
			cur_x = 0;
			return "[end]";
		}
		else
		{
			cur_x = 0;
			++cur_y;
		}
	}
	stringstream stream;
	stream << cur_x++ << "," << cur_y;
	return stream.str();
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
