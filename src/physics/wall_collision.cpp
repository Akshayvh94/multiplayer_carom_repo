#include "../../inc/global_header.h"
#include "../../inc/physics_header.h"

int collision_edge(int i,class coin_state * coins)
{
        float x1 = coins[i].center_x;
        float y1 = coins[i].center_y;
                
        if(   (fabs(x1))     >=             (1 - coins[i].rad_f)              )
        {
                if(coins[i].center_x < 0)
                {
                        coins[i].center_x = - (1 - coins[i].rad_f) ;
                }
                if(coins[i].center_x > 0)
                {
                        coins[i].center_x =  (1 - coins[i].rad_f) ;
                }
                    coins[i].vel_x = (RESTITUITION)*(-1) * (coins[i].vel_x);                         
                return 1;
        }
        else if(fabs(y1) >= (1 - coins[i].rad_f))
        {
                if(coins[i].center_y < 0)
                {
                        coins[i].center_y = - (1 - coins[i].rad_f) ;
                }
                if(coins[i].center_y > 0)
                {
                        coins[i].center_y =  (1 - coins[i].rad_f) ;
                }
                   coins[i].vel_y = (RESTITUITION)*(-1)*(coins[i].vel_y);
               return 1;
        }
        else
        {
                return 0;               //collision with wall not possible
        }
        return 0;
}

