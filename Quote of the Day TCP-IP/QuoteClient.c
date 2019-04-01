//
//  QuoteClient
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
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   int i=0;
   char buffer[512];
   int more;
   
   if (argc < 2) {
      fprintf(stderr,"usage %s hostname\n", argv[0]);
      exit(0);
   }
	
 /*   portno = atoi(argv[2]); */
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socks , get a  bigger size");
      exit(1);
   }
	
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"Aint no host when its gone\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = PF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(kQUOTEPORT);
   connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   n = read(sockfd, buffer, 512);
   buffer[n] = '\0';
   printf("%s", buffer);
   do
   {
       more = 1;
       n = read(sockfd, buffer, 512);
       buffer[n] = '\0';

       if(n <= 0)
           break;

       for(i = 0; i < n; i++)
       {
           if(buffer[i] == 512)
           {
               more = 0;
               break;
           }
       }
       
       printf("%s", buffer);
   } while(more);
   
   /* Now connect to the server */
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
	
/*    printf("Please enter the message: "); */   
    /* bzero(buffer,256);
   fgets(buffer,255,stdin); */
   
   /* Send message to the server */
   /* n = write(sockfd, buffer, strlen(buffer)); */
   
   /* Now read server response */
   
  

	close(sockfd);
   return 0;
}