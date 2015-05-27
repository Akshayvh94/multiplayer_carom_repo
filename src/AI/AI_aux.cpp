#include "../../inc/global_header.h"
#include "../../inc/AI.h"

class AI_info_turn_hole * AI_info(int turn , float hole_x , float hole_y , coin_state * coins,int level)
{
        float * invalid_points_strk = in_val_pts_strk(coins,turn);
        float * strk_pos = strk_pos_arr(coins,hole_x,hole_y,turn);

        bool * is_pos_val = is_positions_valid(strk_pos , coins , turn , invalid_points_strk,level);
          
        class AI_info_turn_hole * AI_inf = new AI_info_turn_hole(hole_x,hole_y,turn,strk_pos,is_pos_val);
        
        return AI_inf;
}

float * in_val_pts_strk(coin_state * coins,int turn)                       //this function returns the range in an array of floating point numbers 
{        
        static float aban_range_strk[2 * (NO_COINS - 1) ];                
        
        //insering the abandon range values in the array
        
        for(int i = 0 ; i < NO_COINS - 1 ; i ++ )
        {
             if(coins[i].state == 0)
             {
                        aban_range_strk[2*i] = STANDARD_INVALID;                    //Standard invalid is the representative of all the invalid values i.e. it has the same effect as all invalid have
                        aban_range_strk[2*i + 1] = 0.00;                         
             }
             
             switch(turn)
             {
                case  0 :
                        aban_range_strk[2*i] = coins[i].center_x ;
                        aban_range_strk[2*i + 1] = abandon_range(0,i,coins); 
                   break ;
                case  1 :
                        aban_range_strk[2*i] = coins[i].center_y ;
                        aban_range_strk[2*i + 1] = abandon_range(1,i,coins);                    //Established correct  fully
                   break ;
                case  2 :
                        aban_range_strk[2*i] = coins[i].center_x ;
                        aban_range_strk[2*i + 1] = abandon_range(2,i,coins);                 
                   break ;
                case  3 :
                        aban_range_strk[2*i] = coins[i].center_y ;
                        aban_range_strk[2*i + 1] = abandon_range(3,i,coins);                                 
                   break ;
             }
                                                //filling the 2i and 2i + 1 th elements in this loop iteration corresponding to the ith coin
        }
        
        return aban_range_strk;
}

float abandon_range(int turn , int index , coin_state * coins)
{
        float x_coin = coins[index].center_x;
        float y_coin = coins[index].center_y;
        
        float rad_coin = coins[index].rad_f;
        float rad_strk = coins[NO_COINS - 1].rad_f;
        
        float min_dis_centers = rad_coin + rad_strk  ;
        float dis_line_center ;        
        
        switch(turn)
        {
                case  0 :                                                                                               //Established correct fully
                        dis_line_center = abs(y_coin - line_0);
                    break ;
                case  1 :
                        dis_line_center = abs(x_coin - line_1);   
                    break ;                        
                case  2 :
                        dis_line_center = abs(y_coin - line_2);
                    break ;                        
                case  3 :
                        dis_line_center = abs(x_coin - line_3);
                    break ;                        
        }
        
        if(dis_line_center >= min_dis_centers)                                                          
        {
                return 0.00 ;
        }
        
        else
        {
                return sqrt(((min_dis_centers)*(min_dis_centers))-((dis_line_center)*(dis_line_center)));
        }
}

bool *  is_positions_valid(float * positions ,coin_state * coins , int turn , float * abandon_range_strk,int level)
{
     static bool pos_valid[NO_COINS - 1];
     
     float strk_rad_f = coins[NO_COINS - 1].rad_f;             
       
     for(int i = 0 ; i < NO_COINS - 1 ; i ++ )
      {
              float pos = positions[i];
                  pos_valid[i] = true;
              
              if(abs ( pos ) > IN_LINE_END_F )
              {
                        pos_valid[i] = false;
                   continue;                               //here in this case the coin in the hole state is also adjusted as false since the dummy value for them is greater than IN_LINE_END_F
              }
      
              else if( ( abs ( pos ) < IN_LINE_END_F ) && ( abs ( pos ) >  ( IN_LINE_END_F - strk_rad_f  - ( I_I_L_G_F / 2.00 ))))
              {
                        pos_valid[i] = false;
                   continue;
              }      
                      
              else
              {
                        for( int j = 0 ; j < NO_COINS - 1 ; j ++)
                        {
                                if( ( pos < ( abandon_range_strk[2 * j ] + abandon_range_strk[2 * j + 1] ) ) && ( pos > ( abandon_range_strk[2 * j ] - abandon_range_strk[2 * j + 1] ) ) )
                                {
                                                pos_valid[i] = false;
                                      break;
                                }
                        }                                                
                        
                        if(level == 1 || pos_valid[i] == false)
                        {
                                continue ;
                        }
                        
                        switch(turn)
                        {
                                case 0 :
                                    if(coins[i].center_y < line_0)                      //coins i refer to the coin which is going to be hit
                                    {
                                                  pos_valid[i] = false;
                                        continue;
                                    }
                                    break ;                                    
                                case 1:
                                    if(coins[i].center_x > line_1)
                                    {
                                                  pos_valid[i] = false;
                                        continue;                                                  
                                    }
                                    break ;                                                                        
                                case 2:                                          //here nothing as such of back shot not permitted is there , we have to do it in one level thats why i am doing it invalid here
                                    if(coins[i].center_y > line_2)
                                    {
                                                  pos_valid[i] = false;
                                        continue;                                                  
                                    }                                                                                   //correctness proved fully 
                                    break ;                                                                        
                                case 3:
                                    if(coins[i].center_x < line_3)
                                    {
                                                  pos_valid[i] = false;
                                        continue;                                                  
                                    }
                                    break ;                                                                        
                        }               
              }                 
     }
     
     return pos_valid ;
}

float * strk_pos_arr(coin_state * coins,float hole_x,float hole_y,int turn)
{
//in each index of the array there will be the point of intersection of the line joining the   hole center and  the coin with index i center , and the striker line depending on the turn value              
         static float strk_pos[NO_COINS - 1];   //strk_pos corresponding to the ith coin
  
         float coin_x , coin_y;
  
         for(int i = 0 ; i < NO_COINS - 1 ; i++)
         {
               if(coins[i].state == 0)
               {
                         strk_pos[i] = DUMMY;           //if the coin is in the hole there is no point of striking it and so no meaning of striker pos corresponding to this coin and hence dummy value is used
               }
               else
               {
                        coin_x = coins[i].center_x;
                        coin_y = coins[i].center_y;                                                                          //established correct fully
                 
                        strk_pos[i] = point_intersect(hole_x, hole_y , coin_x , coin_y , turn );
               }  
         }
         
         return  strk_pos;  
}

float point_intersect(float x1 , float y1 , float x2 , float y2 , int turn)
{
       float point_int ; 
       
       switch(turn)
          {
                case  0 :
                     if(y1 == y2)
                     {
                        return INFINITE;
                     }
                     else
                     {
                              point_int = ( x2 - (y2 - line_0) * ((x2 - x1) / (y2 - y1)) ) ;
                        return  point_int;
                     }
                    break ;                                                         
                                                                   
                case  1 :
                     if(x1 == x2)
                     {
                        return INFINITE;
                     }
                     else
                     {
                              point_int = ( y2 - (x2 - line_1) * ((y2 - y1) / (x2 - x1)) ) ;
                        return  point_int;
                     }
                      break ;                     
                     
                case  2 :
                     if(y1 == y2)
                     {
                        return INFINITE;                                                                        //Established correct fully
                     }
                     else
                     {
                              point_int = ( x2 - (y2 - line_2) * ((x2 - x1) / (y2 - y1)) ) ;
                        return  point_int;
                     }
                     break ;
                     
                case  3 :
                     if(x1 == x2)
                     {
                        return INFINITE;
                     }
                     else
                     {
                              point_int = ( y2 - (x2 - line_3) * ((y2 - y1) / (x2 - x1)) ) ;
                        return  point_int;
                     }
                     break ;
          }
          
          return DUMMY ;  //this is a dummy value because this value cannot be reached in any case  just used for removing the compiler tie warnings no significance at all
}

