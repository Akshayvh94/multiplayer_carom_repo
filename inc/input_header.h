
void keyboard(unsigned char key, int x, int y);                 //keyboard input trigger function registered for glutKeyboardFunc()
void shift_striker_left();                                               //used for shifting the striker left by updating the positions of the striker according to the turn value
void shift_striker_right();                                             //used for shifting the striker right by updating the positions of the striker according to the turn value
bool input_active(int hard_code_pc_id , int num_players, int turn);
