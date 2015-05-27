#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include  <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

using namespace std;

                //UNIVERSAL CONSTANTS
                
#define PI 3.14159265358979323846
#define G 9.80

                //CAROM CONSTANTS
                
                                //COLOR RELATED CONSTANTS
                                                
#define BG_COLOR 1.0,1.0,1.0,1.0             //WHITE AND OPAQUE COLOR
#define BOARD_COLOR  0.9,.47,.1411    //BROWN COLOR
#define STRK_COLOR  0.0,0.0,1.0               //BLUE COLOR
#define GEN_COIN_COLOR_1 1.0,1.0,1.0  //WHITE COLOR
#define GEN_COIN_COLOR_2 0.0,0.0,0.0  //BLACK COLOR
#define GEN_COIN_COLOR_3 1.0,0.0,0.0   //RED COLOR
#define BOARD_LINE_COLOR 0.0,0.0,0.0   //BLACK COLOR
#define HOLE_COLOR  0.0,0.0,0.0   //WHITE COLOR
#define EDGE_COLOR .647,.164,.164  //BLACK_COLOR
#define I_L_COLOR 1.0,0.0,0.0  //RED_COLOR
#define POWER_DISPLAY_ON 1.0,1.0,0.0 //YELLOW COLOR
#define POWER_DISPLAY_OFF  1.0,1.0,1.0 //WHITE COLOR


                
#define BOARD_FR  3.0 //friction coefficient
#define INIT_ANGLE -90 //INITIAL  ANGLE
#define UNIT_LENGTH_F .25 //ARROW _ HEAD SIZE IN TERMS OF FRACTION OF UNIT SIZE OF CAROM BOARD
#define MAX_POWER 150 //UPPER LIMIT TO POWER READER                     // ***** MAX_POWER / UNIT < GEN_COIN_RAD_F + STRIKER_COIN_RAD_F *****
#define UNIT_POWER  1 //LOWER LIMIT TO POWER READER  AND ALSO THE UNIT INCREASE VALUE

#define P_G_B .10  //POWER DISPLAY GAP FROM EDGE OF THE BOARD AND ITS WIDTH ALSO

#define CORNER_SIZE 3
#define OUTLINE_WIDTH 2
#define ACC_ORDER  50
#define C_L_WIDTH 2
#define BOARD_Z -0.5
#define B_E_U_Z -0.2  //BOARD EDGE UPPER Z COORDINATE
#define I_W_W   800
#define I_W_H  700
                               // #define I_I_L_C_F .9 //HOW MUCH CIRCLE IS FILLED  : CURRENTLY IT IS KEPT 1 FOR SIMPLICITY SAKE
#define A_H_W  .04   //WIDTH  OF ARROW HEAD
#define U_W_F  .75	  //2 * P_G_B + U_W_F < 1.0 neither unexpected results will occur  USE WINDOW FRACTON
#define ROOT2 1.414
#define ROUND_OFF_ERROR 2
#define STOP_LIMIT  8
#define INFINITE 100000000000000000.00                  //assuming it to be float_max_positive_value 
//I have to use some value referring to the infinite but still real ; that value is immaterial but should not be used as a real value througout the program
#define DUMMY 2.000 //just a dummy value only used for removing the compile time warnings

#define A_L_G_F .10
#define CENTER_C_R_F  .20       
#define BOARD_LINE_C_G_F_1 .25
#define BOARD_LINE_C_G_F_2 .7

#define CORNER_C_R_F  .0601
#define I_O_L_G_F   .2743 
#define I_I_L_G_F  .0909                              //this bunch is calculated according to the standard carrom 
#define GEN_COIN_RAD_F .0429
#define STRK_COIN_RAD_F .0559
#define MASS_GEN 5.25 //in units of grams
#define MASS_STRIKE 15 //in units of grams  
#define FILL_F .03

#define EDGE_GAP_F .10
#define RESTITUITION 1
#define STRIK_POCK_LOSE 1
#define BLACK_VALUE 1
#define WHITE_VALUE 2
#define RED_VALUE 5
#define TRIGGER 1

#define UNIT 1700   //THE amount of vel WHICH WILL TAKE YOU TO THE OTHER EDGE from the center in one sec //This and TRIGGER decides ultimately how fast the coins will run visually

                //USER DEFINED CONTANTS ENDS                                               

#define B_L_F   U_W_F
#define B_B_F   U_W_F
#define NO_COINS 6                   //NO COINS TO BE PLAYED WITH   //IT IS  6 AT THIS POINT OF TIME AS PER THE REQUIREMENT OF ASSIGNMENT ( 2 WHITE , 2 BLACK , 1 RED , 1 STRIKER )
                                                 
#define HIT_EVENT 1
#define SHIFT_EVENT 2                                   ///THE VALUES ARE IMMATERIAL THE POINT IS THAT ACCORDING TO THAT ID IT WILL PROCESS AND SEND THE DATA WHEN INPUT IS GIVEN
#define THETA_UPDATE_EVENT 3
#define HOLE_FALL_EVENT 4
 
class coin_state
{
        public :
                
                float rad_f;
                float mass;        
                float center_x;       //centre_x coordinate
                float center_y;       //centre_y coordinate
                float vel_x;           //velocity in the x direction 
                float vel_y;           //velocity in the y direction
                int  state;             //1 when active and 0 when inactive i.e. in hole                                                          
                
                   coin_state(float cen_x,float cen_y,float velc_x,float velc_y,int status,float coin_rad_f,float weight)                
               {        
                             center_x = cen_x;
                             center_y = cen_y;
                             vel_x = velc_x;                                    //Initialising constructor 
                             vel_y = velc_y;            
                             state = status;
                             rad_f = coin_rad_f;                                
                             mass = weight;
               }
               
                   coin_state()
               {
                                
               }
} ;

#define GEN_COIN_RAD_F .0429
#define STRK_COIN_RAD_F .0559
#define MASS_GEN 5.25 //in units of grams
#define MASS_STRIKE 15 //in units of grams
#define ERROR_CHECK 0
#define FLAG 0

struct server_send
{
        int hard_code_pc_id ;
        int level_computer;
        int num_players;
};

class scenario
{
        public :
                   
                   int num_points_team1;
                   int num_points_team2;                  
                   class coin_state * coins;                   
                   int turn;                                      
                   int  current_team;
                   
       public :
       
                       scenario(int points_team1,int points_team2,class coin_state * coin,int trn,int curent_team )
                       {
                                num_points_team1 = points_team1;
                                num_points_team2 = points_team2;
                                coins = coin;
                                turn = trn;
                                current_team = curent_team;
                       }      
                      scenario()     
                      {
                      }
};
                   
class global_var
{
        private :
                                   
                   int hit_striker;
                   int num_players;
                   int level_computer;
                      
                   int low_lev_debug;
                   int high_lev_debug;                                      
                   
                   int current_p;
                   int glWidth;
                   int glHeight;
                   
                   float theta;
                                      
                   class coin_state * coins;
                   
       public :
       
        global_var()                 
       {
                
       }
       
        global_var(int hit,int players,int level,int low_debug,int high_debug,int curent_p,int glWidt,int glHeigt,float thet,class coin_state * coin)
      {                         
                   hit_striker = hit;
                   num_players = players;
                   level_computer = level;
                   low_lev_debug = low_debug;
                   
                   high_lev_debug = high_debug;               
                   current_p = curent_p;
                   glWidth = glWidt;
                   glHeight = glHeigt;
                   theta = thet;
                   
                   coins = coin;
      }
      
      
                        //getting the values of the object      
      
      int get_hit_striker() { return hit_striker; }
      
      int get_num_players() { return num_players; }
      
      int get_level_computer() { return level_computer; }
      
      int get_low_lev_debug() { return low_lev_debug; }
      
      int get_high_lev_debug() { return high_lev_debug; }
      
      int get_current_p() { return current_p; }
      
      int get_glWidth() { return glWidth; }
      
      int get_glHeight() { return glHeight; }
      
      float get_theta() { return theta; }
      
      class coin_state *  get_coins() { return coins; }
      
       
                        //updating the values of the object     
      
      void update_hit_striker(int new_val) {  hit_striker = new_val; }
      
      void update_num_players(int new_val) { num_players = new_val; }
      
      void update_level_computer(int new_val) { level_computer = new_val; }
      
      void update_low_lev_debug(int new_val) { low_lev_debug = new_val; }
      
      void update_high_lev_debug(int new_val) { high_lev_debug = new_val; }
      
      void update_current_p(int new_val) { current_p = new_val; }
      
      void update_glWidth(int new_val) { glWidth = new_val; }
      
      void update_glHeight(int new_val) { glHeight = new_val; }
      
      void update_theta(float new_val) { theta = new_val; }
      
      void update_coins(class coin_state * new_val) { coins = new_val; }                                  
      
};

class data_to_send
{
	 public :	
	
	int id;		
	class coin_state  coins[1];				//only 1 for the striker
	float theta ;
	class coin_state  fall_coin_state ;
	int fall_coin_index ;
	
	public :
			
	data_to_send()
	{
	}
};

