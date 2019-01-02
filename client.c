#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  
  char * input = calloc(BUFFER_SIZE,sizeof(char));
  char * output = calloc(BUFFER_SIZE,sizeof(char));
  
  while(1){
	printf("what would you like to say?: ");
	fgets(input,BUFFER_SIZE,stdin);
	input[strlen(input)-1] = '\0';
	write(to_server,input,strlen(input));
	read(from_server,output,BUFFER_SIZE);
	printf("we got a message: %s\n",output);
	free(input);
	input = calloc(BUFFER_SIZE,sizeof(char));
	free(output);
	output = calloc(BUFFER_SIZE,sizeof(char));
  }

}


