/*
	Sample Battleship AI in C++

	main.cpp
*/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstring>

#include "BattleshipAI.h"

std::vector<std::string> parse(std::string);

int main(int argc, char* argv[]){
	std::string input;
	std::vector<std::string> msgs;
	std::string output;
	std::ofstream log("log.txt");

	BattleshipAI ai;	// Create an AI instance.

	if(argc == 1)	// Check to see if there is a command line flag.
	{
		while(1)
		{
			input = "";
			std::getline(std::cin, input, '\n');	// Grab the next line of input from STDIN. (Ie. interface.py)
			log << time(NULL) << " : [in] " << input << std::endl;	// Log all input.
			msgs = parse(input);
			
			output = ai.handler(msgs[3]);	// Send the input to your AI class.

			if(output != "")	// Don't send anything to the interface if there is no output from the AI.
			{
				std::cout << "PRIVMSG:" << msgs[2] << ":" << output << std::endl;
			}

			log << time(NULL) << " : [out] " << output << std::endl;	// Log output with timestamp.

			if(output == "[end]")
			{
				break;
			}
		}
	}
	else if(strcmp(argv[1], "--test") == 0)	// Expect only message as input. No sender, recipient, etc.
	{
		while(1)
		{
			input = "";
			std::getline(std::cin, input, '\n');	// Grab the next line of input from STDIN. (Ie. interface.py)
			
			output = ai.handle(input);	// Send the input to your AI class.

			std::cout << output << std::endl;

			if(output == "[end]")
			{
				break;
			}
		}
	}
	else 
	{
		std::cout << "Command line arguments invalid!\n" << std::endl;
	}

	log.close();
	return 0;
}


std::vector<std::string> parse(std::string in)
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