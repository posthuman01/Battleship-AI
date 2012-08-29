/*
	Battleship-AI Game Server

	main.cpp
*/

#include "GameServ.h"


std::string GameServ::handler(string input)
{
	std::vector<std::string> list_in = parse(input);

	
}





std::vector<std::string> GameServ::parse(std::string in)
{
	std::string sec = "";
	std::vector<std::string> ret;
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