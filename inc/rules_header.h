void rule_init_new_turn(class global_var * glob_var_fin,class scenario * start);                //initialise the global_vaariables and the starting scenario on each update of turn
void rule_init_carrommen(class global_var * glob_var);                                                  //initialise the  carrommen positions and velocities on each new board
int is_active_queen(class coin_state * coins);                                                                //return whether queen is in hole or not
int num_active_black(class coin_state * coins);                                                             //return the number of active black coins
int num_active_white(class coin_state * coins);                                                             //return the number of active white coins
void hole_board(class coin_state * start_coins,class coin_state * fin_coins);                     //replacing the coins from hole to board when striker falls into the hole i.e. foul is done
void init_new_board(class global_var * glob_var_fin,class scenario * start);                     //initialise new board 
void  finalise(class global_var * glob_var_fin,class scenario * start,bool strike_state);         //on each update of turn , what is to be updated and how , is done by this function

//in all cases the arguments are coins array storing the attributes of each coin or global_var object storing the globally used values or scenario object storing the values used on each new turn
