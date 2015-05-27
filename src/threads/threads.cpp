#include "../../inc/global_header.h"
#include "../../inc/main_header.h"
#include "../../inc/networking.h"
//######################################################################################################################
class global_var glob_var_pass;
class scenario start_scenario;                  
class data_to_send transfer_data;        //**** only these three variables are global to all ***** 
int hard_code_pc_id;
//######################################################################################################################
void* monitorCLIENT(void *argv)				//thread for client network
{
          set_global_var(mem_alloc());   //allocates the value to all the coins objects needed to store their attributes and all global variables and after that only global_var is used      
	initClient(((struct thread_data *) argv )-> args);
}
//######################################################################################################################
void* monitorOPENGL(void* argv)				//thread for display
{
	class scenario * start = init_new_game();       //here all the game characteristics are initialised and assigned to the start_scenario object    
     
        start_scenario  = (*start);
             
        glutInit( & ( ( (struct thread_data *) argv) -> arg), ((struct thread_data *) argv) -> args);        
        
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
        
        glutInitWindowSize(I_W_W,I_W_H);  
                    
        glutCreateWindow("Multiplayer Carom");                  
      
        glutDisplayFunc(display);       
        
        glutTimerFunc(TRIGGER,trigger,UNIT);
        
        glutReshapeFunc(reshape);       
        
        glutKeyboardFunc(keyboard); 
                
        glutMainLoop();

}
//#################################################### end ##############################################################
