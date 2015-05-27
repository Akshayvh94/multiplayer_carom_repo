#include "../../inc/global_header.h"
#include "../../inc/display_header.h"


extern  class scenario start_scenario;
extern  class global_var glob_var_pass;
extern int hard_code_pc_id;  
                                      
void display()                                  // display callback function which will be called again and again 
{        
      int glWidth = glob_var_pass.get_glWidth();
      int glHeight = glob_var_pass.get_glHeight();
      
        glLoadIdentity();
        
      if(glWidth > glHeight)
      {
                glScalef((float)((float)glHeight / (float)glWidth),1.0,1.0);
      }    
      else
      {
                glScalef(1.0,(float)((float)glWidth / (float)glHeight),1.0);
      }          
       
        glViewport(0,0,(GLsizei)glWidth,(GLsizei)glHeight);     
        
        glRotatef( - (hard_code_pc_id%4)*(90.00),0.0,0.0,1.0);           //Rotating according to the turn around the z axis clockwise
        
        permanent_display();                            //displaying the permanent part
                      
        carom_coins_display();                          //displaying all the coins                     
        
        dir_display();                                                       //displaying the direction in which the striker has to be hit        
        
        glRotatef( (hard_code_pc_id%4)*(90.00),0.0,0.0,1.0);           //Undoing the rotation effect for power reader
        
        power_display();                                   //displaying the power reader 
        
        glFlush();
        
        glutSwapBuffers();              //Swapping the buffers for smooth animation
        
        glutPostRedisplay();
        
}       
