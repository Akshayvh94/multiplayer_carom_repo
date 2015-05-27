#include "../../inc/global_header.h"
#include "../../inc/display_header.h"

extern class global_var glob_var_pass;

void carom_coins_display()
{
        class coin_state * coins = glob_var_pass.get_coins();        
        
        int loop_var = 0 ;                   

             
       for(loop_var = 0 ; loop_var < ( NO_COINS - 2 ) / 2  ; loop_var ++)
       {               
                 glColor3f(GEN_COIN_COLOR_1);
                 
             if(coins[loop_var].state==0)                                       //here the white coins are displayed
             {
                    glColor3f(HOLE_COLOR);
                    draw_circle_filled(coins[loop_var].rad_f,coins[loop_var].center_x ,coins[loop_var].center_y,ACC_ORDER,B_E_U_Z);                   
             }
             else
             {
                     draw_circle_filled(coins[loop_var].rad_f,coins[loop_var].center_x ,coins[loop_var].center_y,ACC_ORDER,B_E_U_Z);
             }
       }
       
            
       
       for(loop_var = ( NO_COINS - 2 ) / 2 ; loop_var <  NO_COINS - 2   ; loop_var ++)
       {               
                 glColor3f(GEN_COIN_COLOR_2);
                 
             if(coins[loop_var].state==0)                                       //here the black coins are displayed
             {
                    glColor3f(HOLE_COLOR);
                    draw_circle_filled(coins[loop_var].rad_f,coins[loop_var].center_x ,coins[loop_var].center_y,ACC_ORDER,B_E_U_Z);                   
             }
             else
             {
                     draw_circle_filled(coins[loop_var].rad_f,coins[loop_var].center_x ,coins[loop_var].center_y,ACC_ORDER,B_E_U_Z);
             }
       }
       
       
       
       
         glColor3f(GEN_COIN_COLOR_3);
                 
       if(coins[NO_COINS - 2].state==0)                                       //here the QUEEN is displayed
       {
                 glColor3f(HOLE_COLOR);
                 draw_circle_filled(coins[NO_COINS - 2].rad_f,coins[NO_COINS - 2].center_x ,coins[NO_COINS - 2].center_y,ACC_ORDER,B_E_U_Z);                   
       }
       else
       {
                 draw_circle_filled(coins[NO_COINS - 2].rad_f,coins[NO_COINS - 2].center_x ,coins[NO_COINS - 2].center_y,ACC_ORDER,B_E_U_Z);
        }
        
        
        
         glColor3f(STRK_COLOR);                                                 //here the striker is displayed
        

       if(coins[NO_COINS - 1].state==0)                                       
       {

                 glColor3f(HOLE_COLOR);
                 draw_circle_filled(coins[NO_COINS - 1].rad_f,coins[NO_COINS - 1].center_x ,coins[NO_COINS - 1].center_y,ACC_ORDER,B_E_U_Z);                   
       }
       else
       {

                 draw_circle_filled(coins[NO_COINS - 1].rad_f,coins[NO_COINS - 1].center_x ,coins[NO_COINS - 1].center_y,ACC_ORDER,B_E_U_Z);
        }


}

void reshape(GLint width, GLint height)
{      
        glob_var_pass.update_glWidth(width);
        glob_var_pass.update_glHeight(height);   // reshaping the window
}

void power_display()
{
        int current_p = glob_var_pass.get_current_p();                                                
        
          glColor3f(POWER_DISPLAY_ON);
        
          glBegin(GL_POLYGON);
                  glVertex3f(B_L_F + P_G_B, B_B_F * ( - 1.00 + 2.00 * (float)(((float)current_p)/((float)MAX_POWER))) / 2.00,BOARD_Z);  
                  glVertex3f(B_L_F + 2 * P_G_B,B_B_F *( -1.00  + (2.00 * (float) (((float)current_p)/((float)MAX_POWER))))/2.00 ,BOARD_Z);  
                  glVertex3f(B_L_F + 2 * P_G_B,- B_B_F / 2.00 ,BOARD_Z);  
                  glVertex3f(B_L_F + P_G_B,- B_B_F / 2.00 ,BOARD_Z);                 
          glEnd();
                 
          glColor3f(POWER_DISPLAY_OFF);
          glBegin(GL_POLYGON);
                  glVertex3f(B_L_F + P_G_B,B_B_F / 2.00,BOARD_Z);  
                  glVertex3f(B_L_F+ 2 * P_G_B,B_B_F /2.00 ,BOARD_Z);  
                  glVertex3f(B_L_F + 2 * P_G_B,B_B_F*(- 1.00 + (2.00 * (float)(((float)current_p)/((float)MAX_POWER))))/2.00 ,BOARD_Z);  
                  glVertex3f(B_L_F + P_G_B,B_B_F*( -1.00  + (2.00 * (float) (((float)current_p)/((float)MAX_POWER))))/2.00 ,BOARD_Z);                 
          glEnd();    
                                                
}

void dir_display()
{      
         class coin_state * coins = glob_var_pass.get_coins();
         
         int hit_striker = glob_var_pass.get_hit_striker();   
         
         float theta = glob_var_pass.get_theta();
       
         if(hit_striker == 1)
         {              
          float striker_x = B_L_F*(coins[NO_COINS-1].center_x);
          float striker_y = B_B_F*(coins[NO_COINS-1].center_y);                    
                   
          float other_end_x = striker_x + B_L_F*(UNIT_LENGTH_F * cos((float)(theta * (float)(2 * PI))/ 360.000));                     
          float other_end_y = striker_y + B_B_F * (UNIT_LENGTH_F * sin((float)(theta * (float)(2 * PI))/360.00));                        

             glColor3f(BOARD_LINE_COLOR);
             
             glBegin(GL_LINES);
                         glVertex3f(striker_x,striker_y,BOARD_Z);
                         glVertex3f(other_end_x,other_end_y,BOARD_Z);
             glEnd();
        }           
           return ;
}
