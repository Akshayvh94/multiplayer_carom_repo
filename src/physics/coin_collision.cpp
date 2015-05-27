#include "../../inc/global_header.h"
#include "../../inc/physics_header.h"

                                                        //Code being build with its first function under construction

/*int collision_coins_3(coin_state  * coins,int i,int j,int k)
{
        float x1 = coins[i].center_x;
        float y1 = coins[i].center_y;
        float x2 = coins[j].center_x;
        float y2 = coins[j].center_y;  
        float x3 = coins[k].center_x;
        float y3 = coins[k].center_y;                      
        
        float vx1 = coins[i].vel_x;
        float vy1 = coins[i].vel_y;
        float vx2 = coins[j].vel_x;
        float vy2 = coins[j].vel_y;
        float vx3 = coins[k].vel_x;
        float vy3 = coins[k].vel_y;
        
        float rad1 = coins[i].rad_f;
        float rad2 = coins[j].rad_f;
        float rad3 = coins[k].rad_f;
        
        float mass1 = coins[i].mass;
        float mass2 = coins[j].mass;
        float mass3 = coins[k].mass;                       
        
        if(((vx1==vx2)&&(vy1==vy2))||((vx1==vx3)&&(vy1==vy3))||((vx2==vx3)&&(vy2==vy3)))
        {
                return 0;       //Not possible due to equal velocities
        }
        
        float  dist_centres_1_2 = sqrt(((x1 - x2)*(x1 - x2))  + ((y1 - y2)*(y1 - y2)));        
        float  dist_centres_1_3 = sqrt(((x1 - x3)*(x1 - x3))  + ((y1 - y3)*(y1 - y3)));        
        float  dist_centres_2_3 = sqrt(((x2 - x3)*(x2 - x3))  + ((y2 - y3)*(y2 - y3)));        
        
        
        if((dist_centres_1_2  > rad1 + rad2)||(dist_centres_1_3  > rad1 + rad3)||(dist_centres_2_3  > rad2 + rad3))
        {
                return 0 ;      //Not possible due to insufficient distance
        }
        else
        {
              float vr1 = ((x2 - x1)*(vx1) + (y2 - y1) *(vy1))/dist_centres;
              float vr2 = ((x1 - x2)*(vx2) + (y1 - y2) *(vy2)) / dist_centres;
              
              if(vr1 + vr2 > 0.00)
              {
                 float vr1x =( (x2 - x1) * (vr1) )/ dist_centres ;  
                 float vr1y =((y2 - y1) * (vr1))/ dist_centres;                            
                 float vr2x =( (x1 - x2) * (vr2) )/ dist_centres ;  
                 float vr2y =((y1 - y2) * (vr2))/ dist_centres;  
                 
                     coins[i].vel_x = (vx1 - vr1x) + vr2x;                          
                     coins[i].vel_y = (vy1 - vr1y) + vr2y;                                                 
                     coins[j].vel_x = (vx2 - vr2x) + vr1x;                    //Finally updated the velocities
                     coins[j].vel_y = (vy2 - vr2y) + vr1y;                                                                                                
                 return 1;
              }
               
               else
               {
                        if( ( vr1 +  vr2 )== 0)
                        {       
                                //do nothing  but has to handle the round off zero error
                        }
                        else
                        {
                                //do nothing
                        }    
                        return 0;    
               }
        }
}
*/



int collision_coins(int i ,int j,class coin_state * coins)
{
        float x1 = coins[i].center_x;
        float y1 = coins[i].center_y;
        float x2 = coins[j].center_x;
        float y2 = coins[j].center_y;                        
        
        float vx1 = coins[i].vel_x;
        float vy1 = coins[i].vel_y;
        float vx2 = coins[j].vel_x;
        float vy2 = coins[j].vel_y;
        
        float rad1 = coins[i].rad_f;
        float rad2 = coins[j].rad_f;        
        
        float mass1 = coins[i].mass;
        float mass2 = coins[j].mass;
        
        if(((vx1==vx2)&&(vy1==vy2)))
        {
                return 0;       //Not possible due to equal velocities
        }
        
        float  dist_centres = sqrt(((x1 - x2)*(x1 - x2))  + ((y1 - y2)*(y1 - y2)));                               
        
        if(dist_centres  > rad1 + rad2)
        {
                return 0 ; //Not possible due to insufficient distance
        }
        else
        {
                        
              float u1 = ((x2 - x1)*(vx1) + (y2 - y1) *(vy1))/dist_centres;
              float u2 = ((x1 - x2)*(vx2) + (y1 - y2) *(vy2)) / dist_centres;

              float vr1 = ( mass2 * (RESTITUITION * (u1 + u2) ) + mass2 * u2 - mass1 * u1)/(mass1 + mass2);
              float vr2 = ( mass1 * (RESTITUITION * (u2 + u1 ) ) + mass1 * u1  - mass2 * u2 )/(mass1 + mass2);
              
              if(u1 + u2 > 0.00)
              {
                 float vr1x_i =( (x2 - x1) * (u1) )/ dist_centres ;  
                 float vr1y_i =( (y2 - y1) * (u1) )/ dist_centres ;  
                 float vr2x_i =( (x1 - x2) * (u2) )/ dist_centres ;  
                 float vr2y_i =( (y1 - y2) * (u2) )/ dist_centres ;  
                                  
                 float vr1x = - ( (x2 - x1) * (vr1) )/ dist_centres ;  
                 float vr1y =- ((y2 - y1) * (vr1))/ dist_centres;                            
                 float vr2x =- ( (x1 - x2) * (vr2) )/ dist_centres ;  
                 float vr2y =- ((y1 - y2) * (vr2))/ dist_centres;  
                 
                     coins[i].vel_x = (vx1 - vr1x_i) + vr1x;                          
                     coins[i].vel_y = (vy1 - vr1y_i) + vr1y;                                                 
                     coins[j].vel_x = (vx2 - vr2x_i) + vr2x;                    //Finally updated the velocities
                     coins[j].vel_y = (vy2 - vr2y_i) + vr2y;                                                                                                
                     
                 return 1;
              }
               
               else
               {
                        if( ( vr1 +  vr2 )== 0)
                        {       
                                //do nothing  but has to handle the round off zero error
                        }
                        else
                        {
                                //do nothing
                        }    
                        return 0;    
               }
        }
}

