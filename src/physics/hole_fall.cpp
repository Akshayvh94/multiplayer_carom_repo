#include "../../inc/global_header.h"
#include "../../inc/physics_header.h"

extern class data_to_send transfer_data;

int falling_hole(int i,class coin_state * coins)
{
        float x1 = coins[i].center_x;
        float y1 = coins[i].center_y; 
        float hole = 1 - CORNER_C_R_F;
        float limit =  CORNER_C_R_F;
        
        float  dist_centre_1 = sqrt(((x1 - hole)*(x1 - hole))  + ((y1 - hole)*(y1 - hole)));               
        float  dist_centre_2 = sqrt(((x1 + hole)*(x1 + hole))  + ((y1 - hole)*(y1 - hole)));       
        float  dist_centre_3 = sqrt(((x1 - hole)*(x1 - hole))  + ((y1 + hole)*(y1 + hole)));       
        float  dist_centre_4 = sqrt(((x1 + hole)*(x1 + hole))  + ((y1 + hole)*(y1 + hole)));       
 
        if(coins[i].state == 1)
        {
                if(dist_centre_1 <= limit)
                {
                                coins[i].center_x = hole;
                                coins[i].center_y = hole;  
                                coins[i].vel_x =   0.0;
                                coins[i].vel_y = 0.0;
                                coins[i].state = 0;
                                
                                  transfer_data.fall_coin_index = i;          
                                transfer_data.fall_coin_state = coins[i] ;          
                                transfer_data.id = HOLE_FALL_EVENT ;
                        return 1;               
                }
                else if(dist_centre_2 <= limit)
                {
                              coins[i].center_x = (-1)*hole;
                              coins[i].center_y = hole;    
                              coins[i].vel_x =   0.0;
                              coins[i].vel_y = 0.0;
                              coins[i].state = 0;
                                                                                                        //This all networking part is precisely for preventing the adverse impacts of the calculation difference error
                                  transfer_data.fall_coin_index = i;    
                                  transfer_data.fall_coin_state = coins[i] ;          
                                transfer_data.id = HOLE_FALL_EVENT ;
                             return 1;                               
                }
                else if(dist_centre_3 <= limit)
                {
                              coins[i].center_x = hole;
                              coins[i].center_y = (-1) * hole;
                              coins[i].vel_x =   0.0;
                              coins[i].vel_y = 0.0;    
                              coins[i].state = 0;
                          
                          transfer_data.fall_coin_index = i;    
                                  transfer_data.fall_coin_state = coins[i] ;          
                                transfer_data.id = HOLE_FALL_EVENT ;
                     return 1;                            
                }
                else if(dist_centre_4 <= limit)
                {
                            coins[i].center_x = (-1)*hole;
                            coins[i].center_y = (-1)*hole;    
                            coins[i].vel_x =   0.0;
                            coins[i].vel_y = 0.0;
                            coins[i].state = 0;
                            
                          transfer_data.fall_coin_index = i;                                
                                transfer_data.fall_coin_state = coins[i] ;          
                                transfer_data.id = HOLE_FALL_EVENT ;
                     return 1;                            
               }
               else
               {
                        return 0 ;      //IT WILL NOT FALL INTO ANY HOLE
               }
       }
       
        else
        {
                return 1;   //IT IS ALREADY  INTO THE HOLE
        }
}
