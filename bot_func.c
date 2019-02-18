#include "bot.h"

int init_channel (char *ip, int port, char *name){

	char msg[CMD_LENGTH];
	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	int socket_return = socket(server.sin_family, SOCK_STREAM, 0);

	if(socket_return < 0){

		perror("socket:");

		exit(1);
	}

	int connection_status = connect(socket_return, (struct sockaddr *) &server, sizeof(server));

	if(connection_status < 0){

		perror("connect:");
			
		exit(1);
	}

	snprintf(msg, CMD_LENGTH, "%s\n", "plz work");

	int msg_size = strlen(msg);

	int send_return = send(socket_return, msg, msg_size, 0);

		if(send_return < 0){
			printf("send didnt live up to the hype.\n");
		}

	return (socket_return);
}


