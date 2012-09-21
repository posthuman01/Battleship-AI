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

using namespace std;

vector<string> parse(string);

int main(int argc, char* argv[]){
	string input;
	vector<string> msgs;
	string output;
	ofstream log( (string(argv[0]) + ".log").c_str() );

	BattleshipAI ai;	// Create an AI instance.

	if(argc == 1)	// Check to see if there is a command line flag.
	{
		while(1)
		{
			input = "";
			getline(cin, input, '\n');	// Grab the next line of input from STDIN. (Ie. interface.py)
			log << time(NULL) << " : [in] " << input << endl;	// Log all input.
			
			output = ai.handler(input);	// Send the input to your AI class.

			log << time(NULL) << " : [out] " << output << endl;	// Log output with timestamp.

			if(output == "[end]")
			{
				break;
			} 

			else if(output != "") 
			{
				cout << output << endl;
			}
		}
	}
	else if(strcmp(argv[1], "--test") == 0)	// Expect only message as input. No sender, recipient, etc.
	{
		while(1)
		{
			input = "";
			getline(cin, input, '\n');	// Grab the next line of input from STDIN. (Ie. interface.py)
			
			input = "PRIVMSG:sender:recipient:" + input;

			output = ai.handler(input);	// Send the input to your AI class.

			cout << output << endl;

			if(output == "[end]")
			{
				break;
			}
		}
	}
	else 
	{
		cout << "Command line arguments invalid!\n" << endl;
	}

	log.close();
	return 0;
}
