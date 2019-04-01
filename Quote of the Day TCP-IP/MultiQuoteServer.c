//
//  MultiQuoteServer
//
//  Created by <vasilis ieropoulos>
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
#define WAITING 0
#define SENTKNOCKKNOCK 1
#define SENTCLUE 2
#define ANOTHER 3
#define BYE 4

int main(int argc, const char * argv[])
{
    
    char *clues[] = { "Turnip", "Little Old Lady", "Atch", "Who", "Who" };
    char *answers[] = { "A man either lives life as it happens to him, meets it head-on and licks it, or he turns his back on it and starts to wither away.",
        "A star captain's most solemn oath is that he will give his life, even his entire crew, rather than violate the Prime Directive.",
        "A Vulcan can no sooner be disloyal than he can exist without breathing.",
        "After a time, you may find that having is not so pleasing a thing, after all, as wanting.  It is not logical, but it is often true.",
        "All your people must learn before you can reach for the stars.",
        "Another dream that failed.  There's nothing sadder."
        "Blast medicine anyway!",
        " We've learned to tie into every organ in the human body but one.  The brain!  The brain is what life is all about.",
        "But it's real.  And if it's real it can be affected ...  we may not be able to break it, but, I'll bet you credits to Navy Beans we can put a dent in it.",
       "Compassion -- that's the one things no machine ever had.", 
        "Maybe it's the one thing that keeps men ahead of them.",
        "Computers make excellent and efficient servants, but I have no wish to serve under them.",  
        "Captain, a starship also runs on loyalty to one man. And nothing can replace it or him.",
        "Do you know the one -- All I ask is a tall ship, and a star to steer her by ...",
        "[Doctors and Bartenders], We both get the same two kinds of customers -- the living and the dying.",
        "Either one of us, by himself, is expendable.",  
        "Both of us are not.",
        "Emotions are alien to me.",
        "I'm a scientist.",
        "Even historians fail to learn from history -- they repeat the same mistakes.",
        "Every living thing wants to survive.",
        "Fascinating is a word I use for the unexpected.",
        "Fascinating, a totally parochial attitude.",
       "Genius doesn't work on an assembly line basis.",  
       "You can't simply say, Today I will be brilliant.",
        "Hes dead,Jim",
        "History tends to exaggerate.",
       "Humans do claim a great deal for that particular emotion.",
        "I am pleased to see that we have differences.  May we together become greater than the sum of both of us.",
        "Im a soldier, not a diplomat.  I can only tell the truth.",
        "Im frequently appalled by the low regard you Earthmen have for life.",
       "If I can have honesty, its easier to overlook mistakes.",
        "Insufficient facts always invite danger.",
       " Insults are effective only where emotion is present.",
        "Intuition, however illogical, is recognized as a command prerogative.",
        "Is truth not truth for all?",
       " It is a human characteristic to love little animals, especially if theyre attractive in some way.",
       " It is necessary to have purpose.",
        "It would be illogical to assume that all conditions remain stable",
        "Knowledge, sir, should be free to all!",
        "Live long and prosper.",
        "Logic and practical information do not seem to apply here.",
        "To deny the facts would be illogical, Doctor",
        "Lots of people drink from the wrong bottle sometimes",
        "Love sometimes expresses itself in sacrifice",
        "Madness has no purpose.Or reason.  But it may have a goal",
        "Military secrets are the most fleeting of all",
        "Most legends have their basis in facts",
        "No more blah, blah, blah!"};

    #define kNUMCLUES 5
    void ServerConnection(int fd)
    {
        char outBuffer[512];
        char inputBuffer[512];
        int state = WAITING;
        int pits = 0;
        ssize_t n;
        
        sprintf(outBuffer, "%s\r\n",answers[pits]);
        write(fd, outBuffer, strlen(outBuffer));
        state = SENTKNOCKKNOCK;
    
        while(state != BYE)
        {
            /* read input */
            n = read(fd, inputBuffer, 510);
            if(n <= 0)
            {
                fprintf(stderr, "read error\n");
                return;
            }
            inputBuffer[n] = 0;
            
            if(state == SENTKNOCKKNOCK)
            {
                if(0 == strcasecmp(inputBuffer, "Who's there?\r\n"))
                {
                    sprintf(outBuffer, "%s\r\n", clues[pits]);
                    state = SENTCLUE;
                }
                else
                {
                    sprintf(outBuffer, "You're supposed to say \"Who's there?\"! Try again. Knock! Knock!\r\n");
                }
                
            }
            else if(state == SENTCLUE)
            {
                /* Expected response */
                sprintf(outBuffer, "%s who?\r\n", clues[pits]);
                
                if(0 == strcasecmp(inputBuffer, outBuffer))
                {
                    sprintf(outBuffer, "%s Want another? (y/n)\r\n", answers[pits]);
                    state = ANOTHER;
                }
                else
                {
                    sprintf(outBuffer, "You're supposed to say \"%s who?\"! Try again. Knock! Knock!\r\n", clues[pits]);
                }
    
            }
            else if(state == ANOTHER)
            {
                if(inputBuffer[0] == 'y' || inputBuffer[0] == 'Y')
                {
                    pits = (pits + 1) % kNUMCLUES;
                    sprintf(outBuffer, "Knock! Knock!\r\n");
                    state = SENTKNOCKKNOCK;
                }
                else
                {
                    sprintf(outBuffer, "Bye.\r\n");
                    state = BYE;
                }
                
            }
        
            /* Write the output */
            write(fd, outBuffer, strlen(outBuffer));
        }
        
        
    }
    
    
    int main(int argc, const char * argv[])
    {
        int serverSocket, clientConnection;
        struct sockaddr_in server;
        struct sockaddr_in client;
        unsigned int alen;
    
        printf("Listening for connections on port 4444\n");
        
        serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(4444);
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
        
        while(1)
        {
            alen = sizeof(client);
            clientConnection = accept(serverSocket, (struct sockaddr*)&client, &alen);
            if(clientConnection < 0)
            {
                fprintf(stderr, "Accept failed -- %d %d\n", clientConnection, errno);
                return 3;
            }
            
            printf("Conenction from %x port %d...\n", ntohl(client.sin_addr.s_addr), ntohs(client.sin_port));
            
            /* Handle connection */
            ServerConnection(clientConnection);
            
           
        }
        close(clientConnection);
        return 0;
    }
    
    
    
    
    
}
