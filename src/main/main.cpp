//############################################# begin ##########################################################
#include "../../inc/global_header.h"
#include "../../inc/main_header.h"
//############################################ main ############################################################
int main(int argc,char *argv[])				//main for multiplayer carom
{           
	int option = atoi(argv[3]);
	struct thread_data threadData;			// structure as arguement to thread
	threadData.args = argv;
	threadData.arg = argc;
	if(option == 1)					// single player
	{
		set_global_var(mem_alloc()); //allocates the value to all the coins objects needed to store their attributes and all global variables and after that only global_var is
	          // used                                     
   		int level = atoi(argv[4]);
	        init_single_player(level);
	      	pthread_t opengl_thread;
	   	pthread_create(&opengl_thread,NULL,monitorOPENGL,(void *) &threadData);
	   	pthread_join(opengl_thread,NULL);
	}
	else if(option == 2)				// double player
	{
		pthread_t network_thread, opengl_thread;
	   	pthread_create(&opengl_thread,NULL,monitorOPENGL,(void *) &threadData);
	   	pthread_create(&network_thread,NULL,monitorCLIENT,(void *) &threadData);
	   	pthread_join(network_thread,NULL);
	   	pthread_join(opengl_thread,NULL);
	}
        else cout << "Invalid Option.";
        return 0;
}
//######################################## end ###################################################################

