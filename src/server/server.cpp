#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
using namespace std;
#define PORT "27015"										// default port for listening
#define BUFFER_LENGTH 1024   									//buffer for msg transfer	
//###################################################### get address function #################################################################### 

struct server_send
{
        int hard_code_pc_id ;
        int level_computer;
        int num_players;
};				
								// get socket address
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)								// for IPv4 
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);						// for IPv6
}
//############################################################# main function
int init_num_players()
{  
      
       //accessing part of the global variable
       int num_players ;  
             
             
        printf("Enter the num_players : ");      
       
        scanf("%d" , &num_players ); 
        
      while(num_players > 4 || num_players < 1)
      { 
                printf("INVALID NUMBER . ENTER BETWEEN 1 AND 4 ONLY : ");
                scanf("%d" , &num_players);                                       
      }
      
      return num_players ;      
                
}


int pc_id_dec(int num_players,int connected)
{
        if(num_players == 2)
        {
                if(connected == 1)
                {
                        return 0;
                }
                else
                {
                        return 2;
                }
        }
        else
        {
                return ( connected - 1 );
        }
}


int init_level_computer(int num_players)
{
       int level_computer;
       
       if(num_players == 1 || num_players == 3)
        {
                printf("WHAT LEVEL OF COMPUTER DO YOU WANT TO PLAY WITH : 1 . NOVICE  2 . MEDIUM 3 . HARD ?");
                printf("ENTER THE CORRESPONDING CODE : ");
                
                scanf("%d" , &level_computer);
                
            while(level_computer > 3 || level_computer < 1)
            { 
                      printf("INVALID NUMBER . ENTER BETWEEN 1 AND 3 ONLY : ");
                      scanf("%d" , &level_computer);                                       
            }
                                        
        }
        else
        {
                level_computer = 0 ;                //Initialized to a dummy value if there is no computer playing
        }     
        
        return level_computer;
}


// ####################################################################
int main(int argc, char *args[])
{
   int connected = 0;
   int check;
    fd_set master_fd_set;    									// master file descriptor set
    fd_set read_fd_set;										// temp file descriptor set
    int fd_max;        										// maximum file descriptor number
    int server_fd;     										// server's socket descriptor
    int newfd;       			 							// newly accepted socket descriptor
    struct sockaddr_storage remoteaddr;								// client address
    socklen_t addrlen;
    char buf[BUFFER_LENGTH];    								// buffer for client data
    int num_bytes;
    char remoteIP[INET6_ADDRSTRLEN];
    int yes=1;        										// for setsockopt() SO_REUSEADDR, below
    int i, j, rv;										// various counters
    struct addrinfo hints, *ai, *p;
   
    int pc_id ;   
    int num_player = atoi(args[2]); 
    int level_comp = atoi(args[3]); 

   struct server_send send_object ;

    send_object.num_players = atoi(args[2]);
    send_object.level_computer = atoi(args[3]);
         
    printf("Request the connection in the order of the sitting in the carom game : (mandatory)");
    
    FD_ZERO(&master_fd_set);    									// resetting the master and temp sets
    FD_ZERO(&read_fd_set);
    memset(&hints, 0, sizeof hints);   								// initialising to zero
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;								// adding server address details
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, args[1], &hints, &ai)) != 0) 
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));				// checking address info error
        exit(1);
    }
    for(p = ai; p != NULL; p = p->ai_next) 
    {
        server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);			// creating a new socket for server
        if (server_fd < 0) 
        { 
        	perror("Error Creating Socket");
        	continue;
        }
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));			// lose "address already in use" error message

        if (bind(server_fd, p->ai_addr, p->ai_addrlen) < 0) 
        {
            close(server_fd);
            continue;
        }

        break;
    }

    if (p == NULL)										// report if failed to bind 
    {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(2);
    }
    freeaddrinfo(ai); 										// address info freed
    if (listen(server_fd,4) == -1) 
    {
        perror("Error-listen");
        exit(3);
    }
    FD_SET(server_fd, &master_fd_set);									// adding server to the master set 
    fd_max = server_fd; 									// identifying max file fd
    cout << "Now Listening.\n";
    while(1)
    {
        read_fd_set = master_fd_set; 								// copy contents of master set to read set
        if (select(fd_max+1, &read_fd_set, NULL, NULL, NULL) == -1)				// implement select() 
        {
            perror("Error-select");
            exit(4);
        }

        for(i = 0; i <= fd_max; i++) 								// check the sets for a client 
        {
            if (FD_ISSET(i, &read_fd_set)) 
            { 
                if (i == server_fd) 
                {
                    addrlen = sizeof remoteaddr;						// accepting new connections from clients
                    newfd = accept(server_fd, (struct sockaddr *)&remoteaddr, &addrlen);     
		    if (newfd == -1) 
		    {
                        perror("Error-accept");
                    } 
                    else 
                    {
                                connected++;
                                pc_id = pc_id_dec(num_player,connected);
                                send_object.hard_code_pc_id = pc_id;
                                check = send(newfd, &send_object,sizeof(send_object), 0);
                          if (check < 0) 
                          {
                                        perror("PC_ID allotment failed.");
                                        exit(0);        
                          }            
                              cout << "pc_id :" << pc_id;       
                                FD_SET(newfd, &master_fd_set); 						// add connected client to the master set
                        if (newfd > fd_max) 
                        {    									// agian identify the max_fd of the set
                                fd_max = newfd;
                        }
                        printf("Game Server: new connection from %s on ""socket %d\n",inet_ntop(remoteaddr.ss_family,get_in_addr((struct sockaddr*)&remoteaddr),remoteIP, INET6_ADDRSTRLEN),newfd);
                    }
                } 
                else 
                {
                    	if ((num_bytes = recv(i, buf, sizeof buf, 0)) <= 0) 			// handle data from a client 
                    	{
                       		if (num_bytes == 0) 						// handle data from a client
                       		{
                            		printf("Game Server: socket %d hung up\n", i);		// connection closed
                            	} 
                        	else 
                        	{
                            		perror("Error-receive");
                        	}
                        	close(i); 								// close the socket fd if error occurs
                        	FD_CLR(i, &master_fd_set); 							// remove from master set
                    	} 
                    	else 
                    	{
                        	for(j = 0; j <= fd_max; j++) 					// we got some data from a client
                        	{
                            		if (FD_ISSET(j, &master_fd_set))				// check if it exists in our master_fd_set set 
                            		{
                                		if (j != server_fd && j != i) 			// if it is not server or the client itself
                                		{
                                    			if (send(j, buf, num_bytes, 0) == -1) 	// send message
                                    			{
                                        		perror("Error in sending message");	// report error if failure
                                    			}
                                    			cout << "Message relayed.\n";
                                		}
                            		}
                        	}
                   	}
                } 										// END handle data from client
            } 											// END got new incoming connection
        } 											// END looping through file descriptors
    } 												// END while() loop
    return 0;
}

        
