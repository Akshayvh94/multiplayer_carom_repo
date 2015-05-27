#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include "../../inc/networking.h"
#include "../../inc/global_header.h"
#include "../../inc/init_header.h"
//################################################## begin ##################################################################
#define iterate 1
int socketfd,port_num;
struct hostent *server;
struct sockaddr_in server_addr,client_addr;
//##################################### structure for sending data to server ################################################

extern class global_var glob_var_pass;
extern class scenario start_scenario;                          //**** only these variables are global to all ***** 
extern class data_to_send transfer_data;
extern int hard_code_pc_id;

void* monitorSend(void* args)				//FUNCTION FOR SENDING DATA 				
{
	int bitsent;
	while(iterate)
	{
		if(transfer_data.id != ERROR_CHECK)
		{
			bitsent = send(socketfd ,&transfer_data, sizeof(transfer_data),FLAG);
			if(bitsent < ERROR_CHECK) perror("Error Writing to Socket");
			transfer_data.id = ERROR_CHECK;
		}
	}
}

void* monitorListen(void* args)				//FUNCTION FOR RECEIVING DATA
{
	int bitrecv;
	data_to_send * mem_recv_data = new data_to_send();
	data_to_send recv_data = (* mem_recv_data);
	while(iterate)
	{
		bitrecv = recv(socketfd ,&recv_data , sizeof(recv_data),FLAG);
		if(bitrecv < ERROR_CHECK) 
		{
			perror("ERROR reading from socket");
			exit(ERROR_CHECK);
		}			
		else
		{
		        int id_recv = recv_data.id; 		
		        class coin_state * coins  = glob_var_pass.get_coins();
		        
			switch(id_recv)
			{
			        case HIT_EVENT :
        				
	                			coins[NO_COINS - 1] = recv_data.coins[0];
	                			glob_var_pass.update_hit_striker(0);     
	                                break ;
	                                
        		        case SHIFT_EVENT :
                	
	                			coins[NO_COINS - 1] = recv_data.coins[0];
        		                break ;
        		                
        		        case THETA_UPDATE_EVENT :
                              		glob_var_pass.update_theta(recv_data.theta);
        		                break ;  
		                
		                case HOLE_FALL_EVENT :
            		                   coins[recv_data.fall_coin_index] = recv_data.fall_coin_state;   
            		                   break;   		                        	
		        }
			
		}
	}
}

void initClient(char *args[])
{                                    
        struct server_send server_object;
        pthread_t send_thread,listen_thread;		//THREAD DECLARATION
	port_num = atoi(args[2]);	
	socketfd = socket(AF_INET,SOCK_STREAM,FLAG);	//CREATION OF SOCKET
	if(socketfd < FLAG)
	{
		perror("Error Creating Socket.");	//CHECKING VALID SOCKET ESTABLISHMENT
		exit(ERROR_CHECK);
	}
	server = gethostbyname(args[1]);		//FETCHING SERVER ADDRESS AND PORT
	if(server == NULL)
	{
		fprintf(stderr,"ERROR,No such host.\n");	//CHECKING FOR THE SERVER AVAILABILITY
		exit(ERROR_CHECK);
	}
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
	server_addr.sin_port = htons(port_num);		//PORT NUMBER OF SERVER
	if (connect(socketfd,(struct sockaddr *) &server_addr,sizeof(server_addr)) < FLAG)
		{
			printf("Error Connecting to Socket.\n");	//CONNECTING TO SERVER
			exit(ERROR_CHECK);				
		}	
	printf("Connected to %s.\n",args[1]);
	recv(socketfd, &server_object,sizeof(server_object), FLAG);
	
	//process of receiving data
	       glob_var_pass.update_num_players(server_object.num_players);
     	       glob_var_pass.update_level_computer(server_object.level_computer);
               hard_code_pc_id = server_object.hard_code_pc_id;
	//done
	pthread_create(&send_thread,NULL,monitorSend,NULL);          //THREADS TO INITIATE MONITORING SEND/RECEIVE STREAM
	pthread_create(&listen_thread,NULL,monitorListen,NULL);
	pthread_join(listen_thread,NULL);		
	pthread_join(send_thread,NULL);
	close(socketfd);					//SOCKET CLOSED		
}

