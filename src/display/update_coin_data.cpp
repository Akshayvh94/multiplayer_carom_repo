#include "../../inc/global_header.h"
#include "../../inc/display_header.h"
#include "../../inc/physics_header.h"
#include "../../inc/rules_header.h"
#include "../../inc/AI.h"

extern class global_var glob_var_pass;
extern class scenario start_scenario;

void trigger(int value)
{
     
      
         int hit_striker = glob_var_pass.get_hit_striker();
         int turn = start_scenario.turn;
         int level = glob_var_pass.get_level_computer();
         int num_players = glob_var_pass.get_num_players();
         int low_lev_debug = glob_var_pass.get_low_lev_debug();
         class coin_state * coins = glob_var_pass.get_coins();
         class coin_state * AI_strk;      
          
         int i , j;
         
         float rec = 1.00/ (float) value ;
         
         if(hit_striker == 1)
         {
         
                                //AI IS IMPLEMENTED HERE
                
                        if(num_players == 1 && turn == 2 )                        //i.e. a computer is involved                         //always 2 is made the computer
                        {
                                     AI_strk =  AI_strk_state(level,turn,coins) ;                                     
                                     AI_real_simulate(turn,AI_strk,coins);                                  
                                     glob_var_pass.update_hit_striker(0);
                        }
                
                        if(num_players == 3 && turn == 3)               //i.e. a computer is involved                         //always 3 is made the computer
                        {
                                       AI_strk =  AI_strk_state(level,turn,coins) ;
                                       AI_real_simulate(turn,AI_strk,coins);
                                       glob_var_pass.update_hit_striker(0);         
                        }       
                
                              glob_var_pass.update_current_p( ( glob_var_pass.get_current_p() + UNIT_POWER ) % MAX_POWER ) ;                                                                  
         }                       
         
         else
         {
                if(low_lev_debug == 1)
                {
                                debug();
                }
                
                for(i = 0 ; i < NO_COINS; i ++)
                {                        
                        for(j = (i  + 1); j < NO_COINS ; j++)
                        {
                                 if((coins[i].state == 1) && (coins[j].state == 1))                                
                                 {
                                                 collision_coins(i , j,coins);
                                 }
                        }
                }                                
                
                for(i = 0; i  < NO_COINS ; i++)
                {
                         if(coins[i].state == 1)                                
                         {
                                         collision_edge(i,coins);
                         } 
                } 
                
                for(i = 0; i < NO_COINS ; i++)
                {                       
                         if(coins[i].state == 1)                                
                         {
                                         falling_hole(i,coins);
                         }                                                  
                }
                
                for(i = 0;i < NO_COINS ; i ++)                                          //UPDATING THE POSITIONS
                {
                        if(coins[i].state == 1) 
                        {
                              
                                     coins[i].center_x = (float)(coins[i].center_x + coins[i].vel_x * rec);                          
                                     coins[i].center_y = (float)(coins[i].center_y + coins[i].vel_y * rec);                             //TELL THE USER THAT THE 1/2 of edge as 100 unit IS IN THE RANGE 
                                     
                              if(coins[i].vel_x > 0)
                              {
                                                coins[i].vel_x -= (float)((float)( G *  BOARD_FR ) * rec);                    
                               }
                               else 
                               {
                                               coins[i].vel_x += (float)((float)( G *  BOARD_FR ) * rec);                     //calculating the friction part
                               }
                               if(coins[i].vel_y > 0)
                               {
                                               coins[i].vel_y -= (float)((float)( G *  BOARD_FR ) * rec);
                               }
                               else
                               {
                                               coins[i].vel_y += (float)((float)( G *  BOARD_FR ) * rec);
                               }
                          }
                 }
                 
               
                        //UPDATING THE HIT_STRIKER TO THE 1 SO THAT I CAN CHECK WHETHER THERE IS ANY NEED TO CONTINUE TRIGGERING AT ALL
                        
                    glob_var_pass.update_hit_striker(1); 
                    
                for(i = 0;i < NO_COINS ; i ++)
                {
                        if(((fabs)(coins[i].vel_x)) <= STOP_LIMIT   && ((fabs)(coins[i].vel_y) <= STOP_LIMIT)) 
                        {
                                     coins[i].vel_x = 0;
                                     coins[i].vel_y = 0;
                        }
                        else
                        {
                                   glob_var_pass.update_hit_striker(0); 
                        }
                }
                
                if(glob_var_pass.get_hit_striker() == 1 )
                {                             
                              rule_init_new_turn(&glob_var_pass,&start_scenario);                  //here the rule part will apply 
                } 
                                                                
         }
             
           glutPostRedisplay();                                      //CALLING DISPLAY FUNCTION SO THAT WE CAN SEE THE UPDATED CHANGES
           
           glutTimerFunc(TRIGGER,trigger,UNIT);                       //TRIGGERING FURTHER UPDATES 
           
}

void debug()
{
        int low_lev_debug = glob_var_pass.get_low_lev_debug();
        class coin_state * coins = glob_var_pass.get_coins();
          
}

