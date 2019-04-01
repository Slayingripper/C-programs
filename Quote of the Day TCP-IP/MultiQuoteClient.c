//
//  MultiQuoteClient
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
#define kQUOTEPORT      1717
#define kMULTIQUOTEPORT 1818

int main(int argc, char *argv[]) {
   int sockfd,n, i;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   int quotes;
   quotes = atoi(argv[2]);
   i=1;
   sockfd=0;
   char buffer[512];
   
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname NUMBER OF QUOTES\n", argv[0]);
      exit(0);
   }

   
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(kMULTIQUOTEPORT);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
	
    /* printf("Please enter the message: ");
   bzero(buffer,512);
   fgets(buffer,255,stdin);  */
   
   /* Send message to the server */
   
   n = write(sockfd, buffer, strlen(buffer));
    
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   for(i=1; i<=quotes; i++){
   memset(buffer,0,512);
   n = read(sockfd, buffer, 511);
   printf("%s\n",buffer);
   write(sockfd,"ANOTHER\r\n",9);

   /* i++; */
}
write(sockfd,"CLOSE\r\n",7);   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
	
   close(sockfd);
   return 0;
}