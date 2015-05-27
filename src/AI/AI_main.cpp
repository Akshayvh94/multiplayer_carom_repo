#include "../../inc/global_header.h"
#include "../../inc/AI.h"
 
void AI_real_simulate(int turn,class coin_state * AI_strk,class coin_state * coins)
{

        coins[NO_COINS - 1].center_x = (*AI_strk).center_x;
        coins[NO_COINS - 1].center_y = (*AI_strk).center_y;
        coins[NO_COINS - 1].vel_x = (*AI_strk).vel_x;
        coins[NO_COINS - 1].vel_y = (*AI_strk).vel_y;                                
}
                
class coin_state * AI_strk_state(int level , int turn ,class coin_state * coins )
{
                
        class coin_state * AI_strk = new coin_state();                                              
          
          strk_state(level,turn,coins,AI_strk);                  //We will set only the pos and velocity of the striker and else is fixed throughout the program and we will not bother about that
          
        return AI_strk;
}



void set_one_coord(class coin_state * AI_strk , int turn)
{
        //according to the turn value fix one coordinate of the striker
                                
        switch(turn)
        {
                case  0 :
                        (*AI_strk).center_y = line_0;
                        break ;
                case  1 :
                        (*AI_strk).center_x = line_1;
                        break ;
                case  2 :
                        (*AI_strk).center_y = line_2;
                        break ;
                case  3 :
                        (*AI_strk).center_x = line_3;
                        break ;
        }       
                 
}

void strk_state(int level,int turn,class coin_state * coins,class coin_state * AI_strk)
{
       //according to the turn value fix one coordinate of the striker
        
       //having the memory for four objects of AI_info object 
                                                       
        class AI_info_turn_hole * AI_info1 = AI_info(turn,hole_0_center_x,hole_0_center_y,coins,level);
        class AI_info_turn_hole * AI_info2 = AI_info(turn,hole_1_center_x,hole_1_center_y,coins,level);   
        class AI_info_turn_hole * AI_info3 = AI_info(turn,hole_2_center_x,hole_2_center_y,coins,level);   
        class AI_info_turn_hole * AI_info4 = AI_info(turn,hole_3_center_x,hole_3_center_y,coins,level);   
        
        //two objects are created now                     
 
        float  pos_arr_merge[NO_COINS - 1] ;
        bool  is_pos_valid_merge[NO_COINS - 1];
        
          merge(pos_arr_merge,is_pos_valid_merge,AI_info1 ,AI_info2 ,AI_info3 ,AI_info4);
          
          //now the last two arrays  will go through  a test function if they pass then the current function returns if not then it proceeds according to the level
          
         if( if_any_valid_pos(pos_arr_merge,is_pos_valid_merge,turn,level,AI_strk,coins) == true )
         {
                return ;
         }
         else
         {
                    no_valid_pos(AI_strk,turn);                                   //proceed according to the levels     
                return ;
         }
}


void no_valid_pos(class  coin_state * AI_strk,int turn)
{
       
       switch(turn)
       {
                case 0 :
                       (*AI_strk).center_x = 0.0 ;
                       (*AI_strk).vel_x = 0.0;
                       (*AI_strk).vel_y = (float) ( MAX_POWER ) ;
                       break ;
                       
                case 1 :
                        (*AI_strk).center_y = 0.0;
                        (*AI_strk).vel_x = (float)( - MAX_POWER );
                        (*AI_strk).vel_y = 0.0;                                 //if not find any valid pos then givethese values to the striker irrespective of the level
                        break ;
                        
                case 2 :
                        (*AI_strk).center_x = 0.0;                
                        (*AI_strk).vel_x = 0.0;
                        (*AI_strk).vel_y = (float) ( - MAX_POWER );
                        break ;
                                                                                                //YET TO EXTEND IT FOR ALL THE COINS
                case 3 :
                        (*AI_strk).center_y = 0.0;                
                        (*AI_strk).vel_x = (float)( MAX_POWER );
                        (*AI_strk).vel_y = 0.0;
                        break ;
                                                 
        } 
        
}



void merge(float * merge_pos,bool * merge_valid , AI_info_turn_hole * AI_info1 , AI_info_turn_hole  * AI_info2 , AI_info_turn_hole  * AI_info3 , AI_info_turn_hole  * AI_info4)
{
         float * pos1 = (*AI_info1).strk_pos_array;
         bool * valid1 = (*AI_info1).is_locations_valid;
        
         float * pos2 = (*AI_info2).strk_pos_array;
         bool * valid2 = (*AI_info2).is_locations_valid;
        
         float * pos3 = (*AI_info3).strk_pos_array;
         bool * valid3 = (*AI_info3).is_locations_valid;
        
         float * pos4 = (*AI_info4).strk_pos_array;
         bool * valid4 = (*AI_info4).is_locations_valid;
        
         for(int i = 0 ; i < NO_COINS - 1 ; i ++)
         {
                   if(valid1[i]==false && valid2[i]==false&&valid3[i] == false &&valid4[i] == false)
                   {
                             merge_valid[i] = false;                                                               //corresponding two values of the other two arrays are junk
                               
                   }
                   else
                   {
                                merge_valid[i] = true;
                          for(int local = 1 ; local < 5 ; local ++)
                          {
                                
                                switch(local)
                                {
                                        case 1 :
                                              if(valid1[i]==true)
                                              {
                                                                merge_pos[i] = pos1[i];
                                                                local = 5;                            //set out of the loop
                                              }
                                              break;
                                        case 2 :
                                              if(valid2[i]==true)
                                              {
                                                                merge_pos[i] = pos2[i];
                                                                local = 5;                            //set out of the loop
                                              }
                                              break;
                                        case 3 :
                                              if(valid3[i]==true)
                                              {
                                                                merge_pos[i] = pos3[i];
                                                                local = 5;                            //set out of the loop
                                              }
                                              break;
                                        case 4 :
                                              if(valid4[i]==true)
                                              {
                                                                merge_pos[i] = pos4[i];
                                                                local = 5;                            //set out of the loop
                                              }
                                              break;
                                }     
                          }                                       
                    }
            }                
}       
        
bool if_any_valid_pos(float *  pos_arr_merge ,bool * is_pos_valid_merge ,int turn ,int  level ,class  coin_state * AI_strk,class coin_state * coins)
{
        float  priority_coins[NO_COINS - 1];        
        int bool_val[NO_COINS - 1];
        
        for(int i = 0 ; i < NO_COINS - 1 ; i++)
        {
                if(is_pos_valid_merge[i]==true)
                {
                                  bool_val[i] = 1;
                }
                else
                {
                                  bool_val[i] = 0;
                }
                 
                if(level==1 || level==2)
                {
                                  priority_coins[i] = (float)bool_val[i] ;//*( 1 + (float)hin_arr_merge[i]));  
                }       
                else 
                {                                           
                           if(i < ( NO_COINS - 2 ) / 2)
                           {
                                       priority_coins[i] = ((float)bool_val[i] *(1.00 / ( WHITE_VALUE )));//*( 1 + (float)hin_arr_merge[i]));
                           }
                           else if (i < NO_COINS - 2)
                           {
                                       priority_coins[i] = ((float)bool_val[i] *(1.00 / (BLACK_VALUE )));//*( 1 + (float)hin_arr_merge[i]));
                           }
                           else
                           {
                                       priority_coins[i] = ((float)bool_val[i] *(1.00 / (RED_VALUE )));//*( 1 + (float)hin_arr_merge[i]));
                           }                 
                }
        } 
        
        bool return_val = false;
        float min_val = NO_COINS - 2;        
        int req_index;
                
        //priority coin is calculated and has to be manipulated now
        for(int i = 0 ; i < NO_COINS - 1 ; i++)
        {
               float current_val = priority_coins[i];
               
               if(current_val != 0.00)
               {
                        return_val = true;
                   if(current_val < min_val)
                   {
                                min_val = current_val;                                                  //***** imp minute point *****here some randomness should be there but is not present
                                req_index = i ;      
                   }                
               }                                                     
        }
        
        if(return_val == false)
        {        
                return return_val;
        }
        else
        {
                switch(turn)
                {
                        case 0 :
                                (*AI_strk).center_x = pos_arr_merge[req_index]; 
                                break ;
                        case 1 :
                                (*AI_strk).center_y = pos_arr_merge[req_index];                         
                                break ;
                        case 2 :
                                (*AI_strk).center_x = pos_arr_merge[req_index];                         
                                break ;
                        case 3 :
                                (*AI_strk).center_y = pos_arr_merge[req_index]; 
                                break ;
                }        
                
                int power = (int) ( (float)( MAX_POWER / 4 ));          //there should be some factor its constant at this point of time
                           
                float target_x = coins[req_index].center_x;
                float target_y = coins[req_index].center_y;
                float striker_x = (*AI_strk).center_x;
                float striker_y = (*AI_strk).center_y;
                
                float dis_coins = sqrt((target_x - striker_x)*(target_x - striker_x) + (target_y - striker_y)*(target_y - striker_y));  
                   
                (*AI_strk).vel_x = power * (target_x - striker_x) / dis_coins ;   
                (*AI_strk).vel_y = power * (target_y - striker_y) / dis_coins ;   
   
                             
                return return_val;               
        }                      
} 
