#include "../../inc/global_header.h"
#include "../../inc/input_header.h"

extern class global_var glob_var_pass;
extern class scenario start_scenario;
extern class data_to_send transfer_data;
extern int hard_code_pc_id;

void keyboard(unsigned char key, int x, int y)
{
       int num_players = glob_var_pass.get_num_players(); 
       int turn = start_scenario.turn ;
       float theta = glob_var_pass.get_theta();
       class coin_state * coins = glob_var_pass.get_coins();
       int current_p = glob_var_pass.get_current_p();
       
       
       if(input_active(hard_code_pc_id,num_players,turn)==true) 
       {
        switch(key)
        {
                case 27: //Escape key
                        exit(0);
                   break;
                   
                case 'l' :  //left shift the striker
                        shift_striker_left();
                        
                        //sending the left shifting information
                        transfer_data.coins[0] = coins[NO_COINS - 1];
                        transfer_data.id = SHIFT_EVENT ;                                          //2 for left shifting event
                                                  
                   break;
                   
                 case 'r':  //right shift the striker       
                         shift_striker_right();                                         //3 for right shifting event                    
                         
                         //sending the right shifting information
                        transfer_data.coins[0] = coins[NO_COINS - 1];
                        transfer_data.id = SHIFT_EVENT;
                   break;  
                    
                  case 'i':             //increase the angle     
                          glob_var_pass.update_theta( theta + 1 ) ;
                          transfer_data.theta = glob_var_pass.get_theta();
                          transfer_data.id = THETA_UPDATE_EVENT;
                     break;
                     
                  case 'd':             //decrease the angle
                          glob_var_pass.update_theta( theta - 1 );                         
                          transfer_data.theta = glob_var_pass.get_theta();
                          transfer_data.id = THETA_UPDATE_EVENT;
                     break;                   
                     
                  case 'h':   //hit the striker                        
                          glob_var_pass.update_hit_striker(0);
                          coins[NO_COINS - 1].vel_x =  current_p * cos( (float)(((float)theta / 360.00 )* ((float)(2 * PI))));
                          coins[NO_COINS - 1].vel_y = current_p * sin( (float)(((float)theta /  360.00 )* ((float)(2 * PI))));          //1 for hit event
                          transfer_data.coins[0] = coins[NO_COINS -1 ];    
                          transfer_data.id = HIT_EVENT;
                     break;   
                                     
        }
       } 
}

bool input_active(int hard_code_pc_id , int num_players, int turn)
{

	if(num_players == 1)
	{
	        if(turn == 0)
	        {
	                return true;
	        }
	        else
	        {
	                return false;
	        }
	}
	else
	{
		if(hard_code_pc_id == turn)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
}

void shift_striker_left()
{
        class coin_state * coins = glob_var_pass.get_coins();
        int turn = start_scenario.turn;
       
        float comp = (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F   );
           
        if( (turn % 2)  == 0 )
        {
                if(fabs(coins[NO_COINS-1].center_x) <= comp)
                { 
                         coins[NO_COINS-1].center_x  -= ( 1 - turn )  * .02;                                                     
                }
                else
                {    
                      if(coins[NO_COINS-1].center_x > 0)   
                      {
                            if(turn == 0)
                            {         
                                        coins[NO_COINS-1].center_x  -=  .02;
                            }
                                   coins[NO_COINS-1].center_x  =  (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing
                     }
                      else
                      {
                            if(turn == 2)
                            {         
                                        coins[NO_COINS-1].center_x  +=  .02;
                            }
                                   coins[NO_COINS-1].center_x  = - (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing
                     
                      }
                }
        }
        else
        {
                if(fabs(coins[NO_COINS-1].center_y) <= comp)
                {                          
                         coins[NO_COINS-1].center_y  -= ( 2 -  turn )  * .02;                              
                }
                else
                {    
                      if(coins[NO_COINS-1].center_y > 0)   
                      {
                            if(turn == 1)
                            {         
                                        coins[NO_COINS-1].center_y  -=  .02;
                            }
                                   coins[NO_COINS-1].center_y  =  (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing
                     }
                      else
                      {
                            if(turn == 3)
                            {         
                                        coins[NO_COINS-1].center_y  +=  .02;
                            }
                                   coins[NO_COINS-1].center_y  = - (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing                     
                      }
                 }
        }
}

void shift_striker_right()
{
        class coin_state * coins = glob_var_pass.get_coins();
        int turn = start_scenario.turn;
       
        float comp = (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F   );
           
        if( (turn % 2)  == 0 )
        {
                if(fabs(coins[NO_COINS-1].center_x) <= comp)
                { 
                         coins[NO_COINS-1].center_x  += ( 1 - turn )  * .02;                                                     
                }
                else
                {    
                      if(coins[NO_COINS-1].center_x < 0)   
                      {
                            if(turn == 0)
                            {         
                                        coins[NO_COINS-1].center_x  +=  .02;
                            }
                                   coins[NO_COINS-1].center_x  =  - (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing
                     }
                      else
                      {
                            if(turn == 2)
                            {         
                                        coins[NO_COINS-1].center_x  -=  .02;
                            }
                                   coins[NO_COINS-1].center_x  = + (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing
                     
                      }
                }
        }
        else
        {
                if(fabs(coins[NO_COINS-1].center_y) <= comp)
                {                          
                         coins[NO_COINS-1].center_y  += ( 2 -  turn )  * .02;                              
                }
                else
                {    
                      if(coins[NO_COINS-1].center_y < 0)   
                      {
                            if(turn == 1)
                            {         
                                        coins[NO_COINS-1].center_y  +=  .02;
                            }
                                   coins[NO_COINS-1].center_y  =  - (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing
                     }
                      else
                      {
                            if(turn == 3)
                            {         
                                        coins[NO_COINS-1].center_y  -=  .02;
                            }
                                   coins[NO_COINS-1].center_y  = + (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F );  //do nothing                     
                      }
                 }
        }
}

/*void mouse(int button,int state,int x,int y)
{
                float x_fr = x / gl_Width;
                float y_fr = y/gl_Height;
                
                if(x > glWidth || y > glHeight)
                {
                        return ; //do nothing
                }
                else if( (x_fr > (B_L_F + P_G_B)) && (x_fr < (B_L_F+ 2.00 * P_G_B)) && (y_fr > (- B_B_F / 2.00)) && (y_fr < (B_B_F / 2.00))) 
                {
                        power =  (int)(((float)(( y_fr +  (B_B_F / 2.00)) / (B_B_F))) * ((float) (power)));                           //setting the power 
                        trigger_unit();
                        glutPostRedisplay();
                   return ;     
                }
                else if(state == GLUT_LEFT_BUTTON)
                {                               
                                                //work in progress
                }                
}*/

