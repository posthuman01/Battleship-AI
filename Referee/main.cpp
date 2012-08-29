/*
	Battleship-AI Game Server

	main.cpp
*/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstring>

#include "GameServ.h"


int main(int argc, char* argv[]){

	std::string input;	// String to hold the input.
	std::string output;	// String that will hold the raw output from the server.

	std::ofstream log("log.txt");	// Log file to store all input and output.

	GameServ serv;	// Create an AI instance.

	if(argc == 1)	// Check to see if there is a command line flag.
	{
		while(1)
		{
			input = "";
			std::getline(std::cin, input, '\n');	// Grab the next line of input from STDIN. (Ie. interface.py)
			log << time(NULL) << " : [in] " << input << std::endl;	// Log all input.
			
			
			output = serv.handler(input);	// Send the input to the server.


			log << time(NULL) << " : [out] " << output << std::endl;	// Log output with timestamp.

			if(output != "")	// Don't send anything to the interface if there is no output from the AI.
			{
				std::cout << "PRIVMSG:" << output << std::endl;
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


