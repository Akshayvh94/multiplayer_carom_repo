void display();                                                         //display_callback function registered in glutDisplayFunc() function
void trigger(int value);                                             //trigger_func used to update the coin_positions and is registered in gkutTimerFunc() , called againafter a particular interval of time

void permanent_display();                                        //used for displaying the part of carom ,like board ,edge which does not update
void carom_coins_display();                                      //display the updated positions of the carom coins
void dir_display();                                                    //display the direc of striker in which it will go if hit at that point of time
void power_display();                                                //displaying the power reader used for judging the power with which the striker is to be hit
void debug();                                                           //gives the present state of all the coins in text format on terminal
void reshape(GLint width, GLint height);                      //used for updating the value of the windows size if reshaped  


void draw_circle_outline(GLfloat rad,GLfloat center_x,GLfloat center_y,GLint acc_order,GLint num_point_1,GLint num_point_2);    
void draw_circle_filled(GLfloat rad,GLfloat center_x,GLfloat center_y,GLint acc_order,float height);
void  DRAW_BOARD_LINE_1();
void  DRAW_BOARD_LINE_2();
void  DRAW_BOARD_LINE_3();
void  DRAW_BOARD_LINE_4();                              //These functions cluster is , just  displaying the permanent features of carom board , each with a particular part
void DRAW_EDGES();
void CORNER_VERTICES();
void DRAW_IN_LINES();
void permanent_display();
