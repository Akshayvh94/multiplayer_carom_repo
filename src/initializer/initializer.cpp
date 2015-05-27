#include  "../../inc/global_header.h"
#include "../../inc/init_header.h"
#include "../../inc/rules_header.h"

extern class global_var glob_var_pass;
extern class data_to_send transfer_data;
extern int hard_code_pc_id ;

class global_var * mem_alloc()
{
      class coin_state * coins   =  new coin_state[NO_COINS];
      class global_var * glob_var = new global_var();     //default constructor is being used    
       (*glob_var).update_coins(coins);
                                                 
      return glob_var;
}

void set_global_var(class global_var * glo_var )
{
        glob_var_pass = (*glo_var);
}

void init_num_players()
{  
      glob_var_pass.update_num_players(1);                                      //here we need to change the name of the function for clarity sake
}

void init_level_computer(int level)
{
       //accessing part of the global variable
     /*  int num_players = glob_var_pass.get_num_players();
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
       */ 
        glob_var_pass.update_level_computer(level);
}

void init_striker(class global_var *  glob_var,int turn)
{
       //accessing part of the global variable
       class coin_state * coins  = (*glob_var).get_coins();
       int high_lev_debug = (*glob_var).get_high_lev_debug();                 
       float  theta = 90.00* ( (1 + turn) % 4);                

        coins[NO_COINS - 1].center_x =  (turn % 2)*(2 - turn) * ((1 - I_O_L_G_F - (I_I_L_G_F / 2.00)));
        coins[NO_COINS - 1].center_y =  - ( ( turn + 1 ) % 2)*(1 - turn) * ((1 - I_O_L_G_F - (I_I_L_G_F / 2.00)));
        coins[NO_COINS - 1].vel_x =  0 ;        
        coins[NO_COINS - 1].vel_y =  0 ;
                                                            
       coins[NO_COINS - 1].state = 1;
       coins[NO_COINS - 1].mass = MASS_STRIKE;
       coins[NO_COINS - 1].rad_f =STRK_COIN_RAD_F;

      if(high_lev_debug==1)
      {
                 printf(" STRIKER . %g    " ,  coins[NO_COINS - 1].center_x); 
                 printf(" STRIKER . %g    " , coins[NO_COINS - 1].center_y);            
      } 
        
       //updating part of the global variable
        (*glob_var).update_theta(theta);
}      
 
void init_rem_var(class global_var * glob_var)
{
       (*glob_var).update_low_lev_debug (0);              //extensive debugging
       (*glob_var).update_high_lev_debug (1);            //minute debugging                       //******Here the debugging values will be decided**********
       (*glob_var).update_glWidth (I_W_W);        //Defined from macro
       (*glob_var).update_glHeight (I_W_H);       //defined from macro
       (*glob_var).update_hit_striker (1);            //initialised to have control in users hand
       (*glob_var).update_current_p (0);           //initialised to zero power
}


class scenario * init_scenario(class coin_state  * coins)
{
        class scenario * scenario_mem = new scenario(0,0,coins,0,1);             //last 1 stands for white breaking team and last 2 stands for another team
        return scenario_mem;
}
     
void copy_coin_arrays(class coin_state * coins_from , class coin_state  * coins_to , int size)
{

       for(int i = 0 ; i < size ; i ++)
       {
                coins_to[i] = coins_from[i];
       }                 
}

void init_single_player(int level)
{
        init_num_players();
        init_level_computer(level);
        hard_code_pc_id = 0 ;
}
     
class scenario * init_new_game()
{
        printf("Press enter to start play : ");
        
        getchar();
        getchar();
        
        init_rem_var(&glob_var_pass);     
        rule_init_carrommen(&glob_var_pass);              //initialize all the carrommen to their initial attributes in each bord        
        init_striker(&glob_var_pass, 0 );                        //initialize the striker to its initial attributes  assuming first turn as 0                       
                                 
      class coin_state * copy_to = new coin_state[NO_COINS] ;
        copy_coin_arrays(glob_var_pass.get_coins(),copy_to,NO_COINS);     
       
      class data_to_send * transferr = new data_to_send(); 
        
        transfer_data = (*transferr);
       
       transfer_data.id = 0;                                    //initialising to ideal state
        
      return init_scenario(copy_to);    
            
}

