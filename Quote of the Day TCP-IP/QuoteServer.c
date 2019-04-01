//
//  QuoteServer
//
//  Created by <Vasilis Ieropoulos>
//  Username: <psyvi>
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>

#define kBufSize 512
#define kQUOTEPORT      1717
#define kMULTIQUOTEPORT 1818

int main(int argc, const char * argv[])
{
	int serverSocket, clientConnection;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char *PATH;
	char buffer[512];
	FILE *fptr;
	int n;
	unsigned int vass;

	printf("Listening for connections on port 1717\n");
	
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(1717);
	server.sin_addr.s_addr = INADDR_ANY;
	
	/* bind socket */
	if((bind(serverSocket, (struct sockaddr*)&server, sizeof(server)) < 0))
	{
		printf("bind() failed -- %d\n", errno);
		return 1; /* Error */
	}
	
	/* Mark the connection as listening */
	if(listen(serverSocket, 15) < 0)
	{
		fprintf(stderr, "Failed to listen()\n");
		return 2;
	}
	vass = sizeof(client); 
	listen(serverSocket,5);
	while(1)
	{
		PATH = argv[1];
		if((fptr=fopen(PATH, "r"))==NULL)
		fscanf(fptr, "%[^\n]", buffer);
		strcat(buffer,"r\n"); 
		fclose(fptr);   

		
		clientConnection = accept(serverSocket, (struct sockaddr*)&client, &vass);
		
		if(clientConnection < 0)
		{
			fprintf(stderr, "Accept failed -- %d %d\n", clientConnection, errno);
			return 3;
		}
		n = write(clientConnection,buffer,512);
		/* printf("Conenction from %x port %d...\n", ntohl(client.sin_addr.s_addr), ntohs(client.sin_port)); */
		
		
		/* Handle connection */
		/* ServerConnection(clientConnection); */
		
		close(clientConnection);
	}
	
	return 0;
}
