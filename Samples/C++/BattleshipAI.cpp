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

std::string BattleshipAI::handler(std::string in)
{
	std::string output = "";

	switch(state)
	{
		case 0:
			if(in == "[start]")
			{
				state = 1;
				output = move();
			}
			break;

		case 1:
			output = move();
			break;
	}

	return output;
}


std::string BattleshipAI::move()
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
	std::stringstream stream;
	stream << cur_x++ << "," << cur_y;
	return stream.str();
}



/*

struct recv_message{
	char* msg_type;
	char* sender;
	char* recipient;
	char* message;
};

recv_message parse_message(char* message){
	recv_message recv = {message,NULL,NULL,NULL};
	char* pC = message;
	char** pFields[] = {&recv.msg_type, &recv.sender, &recv.recipient, &recv.message};
	if(message == NULL)
		return recv;
	for(int i=1; i<4; ++i){
		while(*pC != ':' && *pC != '\0')
			++pC;		
		if(*pC == ':'){
			*pC = '\0';
			++pC;
			*pFields[i] = pC;
		}else{
			return recv;
		}
	}
	//*pFields[3] = pC;
	return recv;
}

recv_message parse_message_c(const char* message){
	if(message == NULL)
		return (recv_message){NULL,NULL,NULL,NULL};
	char* buffer = (char*)malloc(strlen(message));
	if(buffer == NULL || message == NULL)
		return (recv_message){NULL,NULL,NULL,NULL};
	strcpy(buffer, message);
	return parse_message(buffer);
}

*/