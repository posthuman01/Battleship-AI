#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_MESSAGE_LENGTH 512



struct inbound_message{
	char* msg_type;
	char* sender;
	char* recipient;
	char* message;
};

struct outbound_message{
	char* msg_type;
	char* recipient;
	char* message;
};
struct inbound_message parse_inbound(char* msg);
struct inbound_message parse_inbound_c(const char* msg);
int send_message(struct outbound_message msg);

#define LOG(format,args...) if(logging) fprintf(log, format,##args);
FILE* log;
int logging = 0;
int main(int argc, char** argv){
	log = fopen("log.txt", "w"); // Open file for logging
	if(log != (FILE*)-1)
		logging = 1;

	char * message = (char*)malloc(MAX_MESSAGE_LENGTH);
	size_t message_size = MAX_MESSAGE_LENGTH;
	struct outbound_message outbound;
	outbound.msg_type = "PRIVMSG";
	while(1){
		size_t message_length = getline(&message, &message_size, stdin);
		if(message_length == -1){
			LOG("Error retrieving input!\n");
			fclose(log);
			return 1;
		}
		struct inbound_message msg = parse_inbound(message);
		outbound.message = msg.message;
		outbound.recipient = msg.recipient;
		if(msg.msg_type[0] != 'P')
			continue;
		if(msg.recipient[0] == '#'){
			send_message(outbound);			
			outbound.recipient = msg.sender;
			outbound.message = "You need to stop Fucking talking like that in public you little shit\n";
			send_message(outbound);
		}else{
			outbound.recipient = msg.sender;
			send_message(outbound);	
		}
	}
	fclose(log);
	return 0;
}

struct inbound_message parse_inbound(char* msg){
	struct inbound_message message = {msg,msg,msg,msg};
	if(msg == NULL){
		return message;
	}
	size_t len = strlen(msg);
	char** sections[] = {&message.msg_type, &message.sender, &message.recipient, &message.message};
	*sections[0] = msg;
	int parsed_sections = 1;
	char* pC = msg;
	for(int i = 0; (i<len && parsed_sections < 4); ++i){
		if(*pC == ':'){
			*pC = '\0';
			*sections[parsed_sections++] = ++pC;
			continue;
		}else if(*pC == '\0'){
			break;
		}
		++pC;
	}
	if(parsed_sections < 4){
		--pC;
		for(int i = parsed_sections; i < 4; ++i){
			*sections[i] = pC;
		}
	}
	return message;
}

struct inbound_message parse_inbound_c(const char* msg){
	size_t length = strlen(msg) + 1;
	char* new_msg = (char*)malloc(length);
	memcpy(new_msg, msg, length);
	return parse_inbound(new_msg);
}

int send_message(struct outbound_message msg){
	if(msg.msg_type == NULL || msg.recipient == NULL)
		return 1;
	if(msg.message == NULL){
		LOG("%s:%s:", msg.msg_type, msg.recipient);
		printf("%s:%s:", msg.msg_type, msg.recipient);
	}else{
		LOG("%s:%s:%s", msg.msg_type, msg.recipient, msg.message);
		printf("%s:%s:%s", msg.msg_type, msg.recipient, msg.message);
	}
	fflush(stdout);
}