class scenario * init_scenario(class global_var  glob);     //initializing the whole scenario which is updated at the end of each turn update
class global_var  * mem_alloc();                                 //Allocating the lifetime memory for glob_var_pass to be used throughout the program
class scenario  * init_new_game();                             //initialize the whole new game
void init_rem_var(class global_var * glob_var);           //initializing the remaining values of the glob_var_pass
void init_striker(class global_var * glob_var,int turn);  //initialize the striker to its initial attributes according to the turn  value   
void init_carrommen(class global_var * glob_var);        //initialize all the carrommen to their initial attributes  according to the rules of the game
void init_level_computer(int level);  //having sense only when 1 or 3 players are playing and have the value of level_computer from user 
void init_num_players();     //having the num_players value from user
void copy_coin_arrays(class coin_state * coins_from , class coin_state  * coins_to , int size) ; //copying the data from one coins array to other on each turn update
void set_global_var(class global_var * glo_var );
void init_single_player(int level);
