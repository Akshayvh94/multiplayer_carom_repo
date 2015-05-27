#include "../../inc/global_header.h"
#include "../../inc/rules_header.h"
#include "../../inc/init_header.h"

void rule_init_new_turn(class global_var * glob_var_fin,class scenario * start)
{
                                        //implementing the point based carom rules                                                            
                    int curent_team = (*start).current_team;                                                                
                    class coin_state * fin_coins = (*glob_var_fin).get_coins();
                    class coin_state * start_coins = (*start).coins;
                                            
                    if((fin_coins[NO_COINS - 1]).state == 0 )   
                    {                    
                          //if the striker goes in the hole then  make -1 point from the current team account take out all all the  pieces out of the pocket pocketed at that shot     */
                          if(curent_team == 1)
                          {
                                (*start).num_points_team1 -= STRIK_POCK_LOSE;
                          }
                          else
                          {
                                (*start).num_points_team2 -= STRIK_POCK_LOSE;
                          }
                                                                                                                    
                                 hole_board(start_coins,fin_coins);
                                 
                                 finalise(glob_var_fin,start,false);                                                                                                                               
                    }
                    
                    else                                                        //if the striker is not in the hole
                    {
                           int initial_point ;
                           int final_point ;
                           
                           if(curent_team == 1)
                           {
                                        initial_point  = (*start).num_points_team1;
                                (*start).num_points_team1 += BLACK_VALUE * ( num_active_black(start_coins) - num_active_black(fin_coins) );   //due to the carrommen_black     
                                (*start).num_points_team1 += WHITE_VALUE * ( num_active_white(start_coins) - num_active_white(fin_coins) ) ; // due to the carrommen_white
                                (*start).num_points_team1 += RED_VALUE * ( is_active_queen(start_coins) - is_active_queen(fin_coins)) ; //due to the queen                
                                        final_point = (*start).num_points_team1;
                           }
                           else
                           {
                                        initial_point = (*start).num_points_team2;
                                (*start).num_points_team2 += BLACK_VALUE * ( num_active_black(start_coins) - num_active_black(fin_coins) );   //due to the carrommen_black     
                                (*start).num_points_team2 += WHITE_VALUE * ( num_active_white(start_coins) - num_active_white(fin_coins) ) ; // due to the carrommen_white
                                (*start).num_points_team2 += RED_VALUE * ( is_active_queen(start_coins) - is_active_queen(fin_coins)) ; //due to the queen                                                
                                        final_point = (*start).num_points_team2;                                
                           }
                           
                          if(initial_point == final_point)
                          {
                                        finalise(glob_var_fin,start,false); 
                          }
                          else
                          {
                                        finalise(glob_var_fin,start,true); 
                          }
                    }                    
}

void  finalise(class global_var * glob_var_fin,class scenario * start,bool strike_state)
{
        int high_lev_debug = (*glob_var_fin).get_high_lev_debug();
        class coin_state * coins_f = (*glob_var_fin).get_coins();
        int num_coins_left = (num_active_white(coins_f)) + (num_active_black(coins_f)) + (is_active_queen(coins_f));
        
        if(num_coins_left == 0)
        {
                init_new_board(glob_var_fin,start);
             return;
        }                               
        
        else
        {           int num_players = (*glob_var_fin).get_num_players();                    
                    int turn = (*start).turn;
                     
                    if(high_lev_debug==1)
                    {
                               printf("The initial turn value and current_team is : %d , %d \n \n" , turn , (*start).current_team );
                    }
                                                                                
                    if(strike_state == false)
                    {
                             if(num_players < 3 )
                             {
                                            turn =  ( turn + 2 ) % 4;
                                    (*start).current_team =  (int)(turn / 2 ) + 1;
                             }
                             else                                                                                                       //we are changing the turn value if and only if there is striker falled into the hole 
                             {
                                            turn = ( turn + 1 ) % 4;
                                   (*start).current_team = (turn % 2 ) + 1;
                             }
                     }
                     
                     //Now finally deciding that who is going to have the turn
                     (*start).turn = turn;
                                                                                                                                                                                                                                                                                                        
                     if(high_lev_debug==1)
                     {
                               printf("The final turn value and current_team is : %d , %d " , turn , (*start).current_team );
                     }                                                                                                                          
                                                             
                     //initialising the striker finally according to the turn decided                       
                          init_striker(glob_var_fin,turn);                                      //We are currenly having the big assumption that the striker will not be initialised to some other coin position exacly
                          
                     //now finally updating the starting scenario for the next turn                                 
                          copy_coin_arrays((*glob_var_fin).get_coins() , (*start).coins , NO_COINS);    //copying the updated position of the coins                                           
         }
}


void init_new_board(class global_var * glob_var_fin,class scenario * start)
{
        rule_init_carrommen(glob_var_fin);      //initialised the carromemns
      (*start).turn = 0;                                 //initialising the turn to the same player who has breaked earlier
      (*start).current_team = 1;                    //initiasing to the same team who breaked earlier
        init_striker(glob_var_fin, ((*start).turn));                    //initialised the striker after updating the turn to suitable value              
        copy_coin_arrays((*glob_var_fin).get_coins() , (*start).coins , NO_COINS);    //now finally updating the starting scenario for the next board                        
}

void hole_board(class coin_state * start_coins,class coin_state * fin_coins)
{                  
         
        for(int i = 0 ; i < NO_COINS - 1 ; i ++)                                                                        
        {
                if(start_coins[i].state != fin_coins[i].state)
                {
                                  fin_coins[i].state = 1;
                                                                     //these are the coins eligible for replacement    
                                  fin_coins[i].vel_x = 0;
                                  fin_coins[i].vel_y  = 0;
                                  fin_coins[i].center_x = (float)( ( ( i + 1 ) % 2 - ( i  % 4 ) )*( (i + 1) % 2 ) * 2 * ( 1 + ( i / 4 ) ) *GEN_COIN_RAD_F );
                                  fin_coins[i].center_y =  (float)( ( ( i) % 2 - ( i + 3) % 4 ) )*( (i  % 2 ) * 2 * ( 1 + ( i / 4 ) ) *GEN_COIN_RAD_F );    
                }
        }              
}

void rule_init_carrommen(class global_var * glob_var)
{       
       
       class coin_state * coins  = (*glob_var).get_coins();
       int high_lev_debug = (*glob_var).get_high_lev_debug();            
                                
       coins[NO_COINS - 2].center_x = 0;
       coins[NO_COINS - 2].center_y = 0;                //Placing the red at the center              
              
       for(int i = 0; i < NO_COINS - 2; i++)
       {    
                                        //*******here we have to implement the rule that all carrommen should be in the central circle        

                coins[i].center_x = (float)( ( ( i + 1 ) % 2 - ( i  % 4 ) )*( (i + 1) % 2 ) * 2 * ( 1 + ( i / 4 ) ) *GEN_COIN_RAD_F );   
                coins[i].center_y = (float)( ( ( i) % 2 - ( i + 3) % 4 ) )*( (i  % 2 ) * 2 * ( 1 + ( i / 4 ) ) *GEN_COIN_RAD_F );    
                
                                                
              if(high_lev_debug==1)                                                                              //Placing the rest of the coins in the counter_clockwise direction
              {
                         printf(" %d . %g    ", ( i + 1) , coins[i].center_x); 
                         printf(" %d . %g    ",  ( i + 1) , coins[i].center_y);            
              }                    
       }
         
                        //Initializing other attributes
       for(int i = 0; i < NO_COINS - 1; i++)                                
       {        
               coins[i].vel_x = 0;
               coins[i].vel_y = 0;
               coins[i].state = 1;                        //initialised to active state            
               coins[i].mass = MASS_GEN;          //There is no need to update the mass and rad_f any more since they are not going to be changed once initiaized
               coins[i].rad_f = GEN_COIN_RAD_F;          
       } 
}


int num_active_white(class coin_state * coins)
{
        int count = 0;
        
        int i;
        for( i = 0 ; i < ( NO_COINS - 2 ) / 2 ; i ++)
        {
                if(coins[i].state == 1)   
                {
                         count = count + 1;      
                }
        }
        return count;
}

int num_active_black(class coin_state * coins)
{
        int count = 0;
        
        int i;
        for( i = ( NO_COINS - 2 ) / 2 ; i < ( NO_COINS - 2 ) ; i ++)
        {
                if(coins[i].state == 1)   
                {
                         count = count + 1;      
                }
        }
        return count;
}

int is_active_queen(class coin_state * coins)
{
        if(coins[NO_COINS - 2].state == 1)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}
