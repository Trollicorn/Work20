#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
//	int n = mkfifo("wkp",0666);
//	printf("made wkp\n");
	
	int fd = open("wkp", O_RDONLY);
	printf("opened wkp\n");
	
	char client[HANDSHAKE_BUFFER_SIZE];
	read(fd,client,HANDSHAKE_BUFFER_SIZE);
	printf("client says %s\n", client);
//	remove("wkp");
//	printf("bye bye wkp\n");

	printf("writing a letter\n");
	*to_client = open(client, O_WRONLY);
	write(*to_client, ACK, sizeof(ACK));

	printf("oooh a reply!\n");
	char stuff[BUFFER_SIZE];
	read(fd, stuff, BUFFER_SIZE);
	printf("it says: %s\n", stuff);

	return fd;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
	mkfifo("private",0666);
	*to_server = open("wkp", O_WRONLY);
	printf("made private\n");
	
	write(*to_server, "private", 8);
	printf("sent my name (if you get stuck here, then you opened the client before the server. this only works when the client is opened while the server is already open (open the server first))  \n");

	char stuff[HANDSHAKE_BUFFER_SIZE];
	int fd = open("private",O_RDONLY);
	read(fd, stuff, HANDSHAKE_BUFFER_SIZE);
	printf("stuff:%s\n",stuff);
	remove("private");
	printf("private is gone\n");

	write(*to_server, ACK, sizeof(ACK));

	return fd;
}


