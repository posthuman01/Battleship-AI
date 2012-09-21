/*
	Sample Battleship AI in C++

	BattleshipAI.cpp
*/

#include "BattleshipAI.h"


BattleshipAI::BattleshipAI()
{
	state = Config;

	nick = "";
	channel = "";
	referee = "";
}

string BattleshipAI::handler(string raw_in)
{
	vector<string> msg = parse(raw_in);
	// Typical in, MSGTYPE:sender:recipient:message
	if(msg[0] == "NOTICE")
	{
		return "";
	}
	string sender = msg[1];
	string recipient = msg[2];
	string input = msg[3];

	string output = "";


	switch(state)
	{
		case Config:
			if(channel == "")
			{
				if(recipient.compare(0,1,"#") == 0)	// Compare the first char of recipient to determine if it's the channel name.
				{
					channel = recipient;
				}
			}
			if(referee == "")
			{
				output = "PRIVMSG:" + recipient + ":!ref\n";
				referee = " ";
			} 
			else if (referee == " ")
			{
				if(recipient != channel)
				{
					nick = recipient;
					referee = sender;
				}
			}
			if(channel== "" && referee == "" && nick == "")
			{
				state = Prep;
			}
			break;

		case Idle:

			if(input == "[start]")
			{
				state = Prep;
				output = "PRIVMSG:" + channel + ":!bs-test\n";
			}
			break;

		case Prep:
			output = "PRIVMSG:" + channel + ":My nick: " + nick + "\n";
			output += "PRIVMSG:" + channel + ":Referee: " + referee + "\n";
			output += "PRIVMSG:" + channel + ":This channel: " + channel + "\n";
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
