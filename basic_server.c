#include "pipe_networking.h"

char * reverse(char * s){
	int size = strlen(s);
	int i = size - 1;
	char * back = calloc(size,sizeof(char));
	while(i+1){ //while i isnt -1
		back[size-i-1] = s[i]; //beginning of back = end of s
		i--; 
	}
	back[size] = '\0';
	return back;
}

static void sighandler(int signo){
	if (signo == SIGINT){
		remove("wkp");			
		printf("wkp destroyed\n");
		exit(1);
	}
}


int main() {
  
  signal(SIGINT,sighandler);

  int to_client;
  int from_client;

  char * input = calloc(BUFFER_SIZE,sizeof(char));
  char * output = calloc(BUFFER_SIZE,sizeof(char));
  
  while(1){
	
        mkfifo("wkp",0666);
        printf("made wkp");

	from_client = server_handshake( &to_client ); //handshake each client

	if (fork()){
	  while (read(from_client,input,BUFFER_SIZE)){
	  	printf("recieved: %s\n",input);
		strcpy(output,reverse(input));
		printf("sending: %s\n",output);
		write(to_client,output,strlen(output));
		free(input);
		input = calloc(BUFFER_SIZE,sizeof(char));
		free(output);
		output = calloc(BUFFER_SIZE,sizeof(char));
	  }     
	}
	else{

		remove("wkp");
		printf("wkp gone");
	}
	
  }
}


