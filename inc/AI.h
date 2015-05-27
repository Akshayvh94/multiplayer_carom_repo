#define line_0  -(1 - I_O_L_G_F -  ( I_I_L_G_F / 2.00 ) ) 
#define line_1  (1 - I_O_L_G_F -  ( I_I_L_G_F / 2.00 ) ) 
#define line_2  (1 - I_O_L_G_F -  ( I_I_L_G_F / 2.00 ) ) 
#define line_3  -(1 - I_O_L_G_F -  ( I_I_L_G_F / 2.00 ) ) 

#define IN_LINE_END_F (1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)

#define hole_0_center_x  -( 1 - CORNER_C_R_F ) 
#define hole_0_center_y  -( 1 - CORNER_C_R_F )
#define hole_1_center_x  ( 1 - CORNER_C_R_F )
#define hole_1_center_y -( 1 - CORNER_C_R_F )
#define hole_2_center_x  ( 1 - CORNER_C_R_F )
#define hole_2_center_y  ( 1 - CORNER_C_R_F )
#define hole_3_center_x -( 1 - CORNER_C_R_F )
#define hole_3_center_y ( 1 - CORNER_C_R_F )


#define STANDARD_INVALID 1.00
#define NUM_HIN_INACT -1                                //specially designated for the inactive coins

class AI_info_turn_hole
{
    public :
    
    float hole_x;
    float hole_y;
    int turn;
    float  strk_pos_array[NO_COINS - 1];
//    int  num_hind_array[NO_COINS - 1];
    bool is_locations_valid[NO_COINS - 1];
        
    public :
    
     AI_info_turn_hole(float hol_x , float hol_y , int trn , float * strk_pos , bool * is_pos_valid)    
    {
                hole_x = hol_x;
                hole_y = hol_y;
                turn = trn;
                
             for(int i = 0 ; i  < NO_COINS - 1 ; i ++)
             {
                        strk_pos_array[i] = strk_pos[i];
                     //   num_hind_array[i] = num_hindrances[i];
                        is_locations_valid[i] = is_pos_valid[i];
             }
    }
    
     AI_info_turn_hole()
    {
                //default constructor
    }
};
                
                //AI_aux.cpp functions
class AI_info_turn_hole * AI_info(int turn , float hole_x , float hole_y , coin_state * coins,int level);                 
float * in_val_pts_strk(coin_state * coins,int turn);
bool *  is_positions_valid(float * positions ,coin_state * coins , int turn , float * abandon_range_strk,int level);
float abandon_range(int turn , int index , coin_state * coins);
float * strk_pos_arr(coin_state * coins,float hole_x,float hole_y,int turn);
int * num_hindrance_arr(coin_state * coins , float hole_x , float hole_y );
bool points_same_side_line(float x_point1 , float y_point1 , float x_point2 , float y_point2 , float x_line , float y_line , float m_line);
float point_intersect(float x1 , float y1 , float x2 , float y2 , int turn);
void debug_AI(class coin_state * coin);

                //AI_main.cpp functions
bool if_any_valid_pos(float *  pos_arr_merge ,bool * is_pos_valid_merge ,int turn ,int  level ,class  coin_state * AI_strk,class coin_state * coins);
void no_valid_pos(class  coin_state * AI_strk,int turn);
void strk_state(int level,int turn,class coin_state * coins,class coin_state * AI_strk);
void set_one_coord(class coin_state * AI_strk , int turn);
void AI_real_simulate(int turn,class coin_state * AI_strk,class coin_state * coins);
class coin_state * AI_strk_state(int level , int turn ,class coin_state * coins );               
void merge(float * merge_pos,bool * merge_valid , AI_info_turn_hole * AI_info1 , AI_info_turn_hole  * AI_info2 , AI_info_turn_hole  * AI_info3 , AI_info_turn_hole  * AI_info4);
