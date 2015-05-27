#include "../../inc/global_header.h"


void draw_circle_outline(GLfloat rad,GLfloat center_x,GLfloat center_y,GLint acc_order,GLint num_point_1,GLint num_point_2)
{
       GLfloat eff_rad_L = B_L_F * rad ;
       GLfloat eff_rad_B = B_B_F * rad ;
       GLint i;
       GLfloat angle ;                                                                  //Making the in the field circles to be drawn                          
       glBegin (GL_LINE_STRIP);
                     for(i = num_point_1 ; i < num_point_2; i++) 
                     { 
                                        angle = 2*PI*i/acc_order;
                                        glVertex3f((B_L_F * center_x + eff_rad_L * cos(angle) ),(B_B_F * center_y + eff_rad_B *  sin(angle)),BOARD_Z);
                     }                    
        glEnd();
        glFlush();
}


void draw_circle_filled(GLfloat rad,GLfloat center_x,GLfloat center_y,GLint acc_order,float height)
{
        glBegin (GL_POLYGON);
               GLfloat eff_rad_L = B_L_F * rad ;
               GLfloat eff_rad_B = B_B_F * rad ;
               GLint i;                                                                                                 //Drawing the filled circles at the corners
               GLfloat angle ;
                    for(i = 0 ; i < acc_order; i++) 
                    { 
                                        angle = 2*PI*i/acc_order;
                                        glVertex3f((B_L_F * center_x + eff_rad_L * cos(angle) ),(B_B_F *center_y + eff_rad_B *  sin(angle)),height);
                    }
        glEnd();
}

void  DRAW_BOARD_LINE_1()
{    
                               float center_x ;
                               float center_y;
                               float rad;
                               
                                       glBegin(GL_LINES) ;
                                                glVertex3f(- B_L_F * BOARD_LINE_C_G_F_1, B_B_F * BOARD_LINE_C_G_F_1,BOARD_Z);
                                                glVertex3f(- B_L_F * BOARD_LINE_C_G_F_2 ,B_B_F * BOARD_LINE_C_G_F_2,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f( -(B_L_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( -(B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,(B_B_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( -(B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                       glEnd();
                                        
                                       center_x =  - (B_L_F * ( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2))));
                                       center_y = B_B_F * ( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2)));
                                       rad = (CENTER_C_R_F/2.0); 
                                        
                                       draw_circle_outline(rad,center_x/B_L_F,center_y/B_B_F,ACC_ORDER, - ACC_ORDER / 2,ACC_ORDER / 4+ ROUND_OFF_ERROR );
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x - rad * B_L_F - A_H_W / 2,center_y  ,BOARD_Z);
                                                glVertex3f(center_x - rad * B_L_F + A_H_W / 2,center_y ,BOARD_Z);
                                                glVertex3f(center_x - rad * B_L_F, center_y + A_H_W / 2,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x , center_y + rad * B_B_F + A_H_W/ 2,BOARD_Z);
                                                glVertex3f(center_x , center_y + rad * B_B_F - A_H_W/ 2,BOARD_Z);
                                                glVertex3f( center_x- A_H_W /2 ,center_y + rad * B_B_F ,BOARD_Z);
                                       glEnd();
                               return ;
}  
                                                                                                                                                                                                                                                                                                                          
void DRAW_BOARD_LINE_2()
{
                               float center_x ;
                               float center_y;
                               float rad;
                              
                                       glBegin(GL_LINES) ;
                                                glVertex3f( B_L_F * BOARD_LINE_C_G_F_1, B_B_F * BOARD_LINE_C_G_F_1,BOARD_Z);
                                                glVertex3f( B_L_F * BOARD_LINE_C_G_F_2 ,B_B_F * BOARD_LINE_C_G_F_2,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f( (B_L_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( (B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,(B_B_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( (B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                       glEnd(); 
                                        
                                       center_x =  (B_L_F * ( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2))));
                                       center_y = B_B_F * ( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2)));
                                       rad = (CENTER_C_R_F/2.0); 
                                        
                                       draw_circle_outline(rad,center_x/B_L_F,center_y/B_B_F,ACC_ORDER,ACC_ORDER / 4 ,ACC_ORDER + ROUND_OFF_ERROR );
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x + rad * B_L_F - A_H_W / 2,center_y  ,BOARD_Z);
                                                glVertex3f(center_x + rad * B_L_F + A_H_W / 2,center_y ,BOARD_Z);
                                                glVertex3f(center_x + rad * B_L_F , center_y + A_H_W / 2,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x , center_y + rad * B_B_F + A_H_W/ 2,BOARD_Z);
                                                glVertex3f(center_x , center_y + rad * B_B_F - A_H_W/ 2,BOARD_Z);
                                                glVertex3f( center_x+ A_H_W /2 ,center_y + rad * B_B_F ,BOARD_Z);
                                       glEnd();
                               return ;
}
                                                                             
void DRAW_BOARD_LINE_3()
{
                               float center_x ;
                               float center_y;
                               float rad;
                              
                                       glBegin(GL_LINES) ;
                                                glVertex3f(- B_L_F * BOARD_LINE_C_G_F_1,- B_B_F * BOARD_LINE_C_G_F_1,BOARD_Z);
                                                glVertex3f(- B_L_F * BOARD_LINE_C_G_F_2 ,- B_B_F * BOARD_LINE_C_G_F_2,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f( -(B_L_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,-(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( -(B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,-(B_B_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( -(B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,-(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                       glEnd();
                                       
                                       center_x = - (B_L_F * ( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2))));
                                       center_y = -B_B_F * ( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2)));
                                       rad = (CENTER_C_R_F/2.0); 
                                       
                                       draw_circle_outline(rad,center_x/B_L_F,center_y/B_B_F,ACC_ORDER,- ACC_ORDER / 4 - ROUND_OFF_ERROR,ACC_ORDER / 2 + ROUND_OFF_ERROR );
                                       
                                      glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x , center_y - rad * B_B_F - A_H_W / 2,BOARD_Z);
                                                glVertex3f(center_x ,center_y - rad * B_B_F + A_H_W / 2,BOARD_Z);
                                                glVertex3f( center_x - A_H_W / 2,center_y - rad * B_B_F ,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x - rad * B_L_F - A_H_W / 2, center_y,BOARD_Z);
                                                glVertex3f(center_x - rad * B_L_F + A_H_W / 2, center_y,BOARD_Z);
                                                glVertex3f( center_x - rad * B_L_F,center_y - A_H_W / 2 ,BOARD_Z);
                                       glEnd();
                               return ;
}

void  DRAW_BOARD_LINE_4()
{
                               float center_x ;
                               float center_y;
                               float rad;
                              
                                       glBegin(GL_LINES) ;
                                                glVertex3f( B_L_F * BOARD_LINE_C_G_F_1,-  B_B_F * BOARD_LINE_C_G_F_1,BOARD_Z);
                                                glVertex3f( B_L_F * BOARD_LINE_C_G_F_2 , - B_B_F * BOARD_LINE_C_G_F_2,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f( (B_L_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,-(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( (B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,-(B_B_F * BOARD_LINE_C_G_F_2  - A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                                glVertex3f( (B_L_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,-(B_B_F * BOARD_LINE_C_G_F_2  + A_H_W / 4 * ROOT2)*.99,BOARD_Z);
                                       glEnd();    
                                       center_x =  (B_L_F *( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2))));
                                       center_y = -B_B_F * ( BOARD_LINE_C_G_F_1 + (CENTER_C_R_F/(2.0*ROOT2)));
                                       rad = (CENTER_C_R_F/2.0); 
                                       
                                       draw_circle_outline(rad,center_x/B_L_F,center_y/B_B_F,ACC_ORDER, - ROUND_OFF_ERROR, 3 * ACC_ORDER / 4 + ROUND_OFF_ERROR );
                                       
                                      glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x , center_y - rad * B_B_F - A_H_W / 2,BOARD_Z);
                                                glVertex3f(center_x ,center_y - rad * B_B_F + A_H_W / 2,BOARD_Z);
                                                glVertex3f( center_x + A_H_W / 2,center_y - rad * B_B_F ,BOARD_Z);
                                       glEnd();
                                       glBegin(GL_TRIANGLES);
                                                glVertex3f(center_x + rad * B_L_F - A_H_W / 2, center_y,BOARD_Z);
                                                glVertex3f(center_x + rad * B_L_F + A_H_W / 2, center_y,BOARD_Z);
                                                glVertex3f( center_x + rad * B_L_F,center_y - A_H_W / 2 ,BOARD_Z);
                                       glEnd();
                                       
                               return ;
}    
                                  
void DRAW_EDGES()
{
                                  glBegin(GL_POLYGON); 
                                        glVertex3f(-B_L_F * (1 + EDGE_GAP_F),B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(-B_L_F * (1 + EDGE_GAP_F),-B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(-B_L_F ,- B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(-B_L_F , B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                  glEnd();   
                           

                                  
                                 glBegin(GL_POLYGON); 
                                        glVertex3f(B_L_F * (1 + EDGE_GAP_F),B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(B_L_F * (1 + EDGE_GAP_F),-B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(B_L_F ,- B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(B_L_F , B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                  glEnd();

                                glBegin(GL_POLYGON); 
                                        glVertex3f(- B_L_F * (1 + EDGE_GAP_F), B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(B_L_F * (1 + EDGE_GAP_F),B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(B_L_F * (1 + EDGE_GAP_F) , B_B_F,B_E_U_Z);  
                                        glVertex3f(- B_L_F * (1 + EDGE_GAP_F), B_B_F,B_E_U_Z);  
                                  glEnd();
                                  
                                glBegin(GL_POLYGON); 
                                        glVertex3f(- B_L_F * (1 + EDGE_GAP_F),- B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(B_L_F * (1 + EDGE_GAP_F), - B_B_F * (1 + EDGE_GAP_F),B_E_U_Z);  
                                        glVertex3f(B_L_F * (1 + EDGE_GAP_F) ,-  B_B_F,B_E_U_Z);  
                                        glVertex3f(- B_L_F * (1 + EDGE_GAP_F), - B_B_F,B_E_U_Z);  
                                  glEnd();
                                  
                           return ;                                 
}  
                                                                                                                                                                                         
void CORNER_VERTICES()
{                                
                                    glVertex3f(-B_L_F,B_B_F,BOARD_Z);  
                                    glVertex3f(B_L_F,B_B_F,BOARD_Z);  
                                    glVertex3f(B_L_F,- B_B_F,BOARD_Z);  
                                    glVertex3f(-B_L_F, - B_B_F,BOARD_Z);  
}
 
void DRAW_IN_LINES()
{                                            

                                    glBegin(GL_LINES);                         
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),(B_B_F*(1 - I_O_L_G_F)),BOARD_Z) ; 
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),(B_B_F*(1 - I_O_L_G_F)),BOARD_Z); 
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),(B_B_F*(1 - I_O_L_G_F -I_I_L_G_F)),BOARD_Z) ; 
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F)),BOARD_Z); 
                                    glEnd();
                                    
                                    glBegin(GL_LINES);                                                                                 
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),-(B_B_F*(1 - I_O_L_G_F)),BOARD_Z) ; 
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),-(B_B_F*(1 - I_O_L_G_F)),BOARD_Z); 
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),-(B_B_F*(1 - I_O_L_G_F -I_I_L_G_F)),BOARD_Z) ; 
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),-(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F)),BOARD_Z); 
                                    glEnd();
                                    
                                    glBegin(GL_LINES);                         
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F)),-(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z) ; 
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F)),(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z); 
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F - I_I_L_G_F)),-(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z); 
                                    glVertex3f(-(B_L_F*(1 - I_O_L_G_F - I_I_L_G_F)),(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z);
                                    glEnd();
                                                                                   
                                    glBegin(GL_LINES);                                                                                                                               
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F)),-(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z) ; 
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F)),(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z); 
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F - I_I_L_G_F)),-(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z); 
                                    glVertex3f((B_L_F*(1 - I_O_L_G_F - I_I_L_G_F)),(B_B_F*(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F)),BOARD_Z);
                                    glEnd();                                    
                                    
                             return ;
}


void permanent_display()
{             
      // glLineWidth(OUTLINE_WIDTH);    option for choosing the outline lines width
        
        glClearColor(BG_COLOR);
        glClear(GL_COLOR_BUFFER_BIT);                              
                
                
                                        //CAROM BOARD                
                
        glColor3f(BOARD_COLOR);
        glBegin(GL_POLYGON);
                glEdgeFlag(GL_TRUE);                
                CORNER_VERTICES();  
                glEdgeFlag(GL_FALSE);      
        glEnd();
        
        glColor3f(BOARD_LINE_COLOR);        
        
        DRAW_IN_LINES();
                            
        glLineWidth(C_L_WIDTH);       
        
        draw_circle_outline(CENTER_C_R_F,0.0,0.0,ACC_ORDER,-3,ACC_ORDER);    //Central circle       
        
        draw_circle_outline(( I_I_L_G_F / 2.00 ),-(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),ACC_ORDER,-3,ACC_ORDER);
        draw_circle_outline(( I_I_L_G_F / 2.00 ),(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),ACC_ORDER,-3,ACC_ORDER);
        draw_circle_outline(( I_I_L_G_F / 2.00 ),(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),ACC_ORDER,-3,ACC_ORDER);
        draw_circle_outline(( I_I_L_G_F / 2.00 ),(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),-(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),ACC_ORDER,-3,ACC_ORDER);
        
        draw_circle_outline(( I_I_L_G_F / 2.00 ),-(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),- (1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),ACC_ORDER,-3,ACC_ORDER);
        draw_circle_outline(( I_I_L_G_F / 2.00 ),(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),- (1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),ACC_ORDER,-3,ACC_ORDER);
        draw_circle_outline(( I_I_L_G_F / 2.00 ),-(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),ACC_ORDER,-3,ACC_ORDER);
        draw_circle_outline(( I_I_L_G_F / 2.00 ),-(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),-(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),ACC_ORDER,-3,ACC_ORDER);
        
        glColor3f(I_L_COLOR);
        
        draw_circle_filled(FILL_F,-(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),ACC_ORDER,BOARD_Z);  //I_I_L_C_F will be used here if required 
        draw_circle_filled(FILL_F,(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),ACC_ORDER,BOARD_Z);
        draw_circle_filled(FILL_F,(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),ACC_ORDER,BOARD_Z);
        draw_circle_filled(FILL_F,(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),-(1 - I_O_L_G_F - I_I_L_G_F -A_L_G_F),ACC_ORDER,BOARD_Z);
        
        draw_circle_filled(FILL_F,-(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),- (1 - I_O_L_G_F - (I_I_L_G_F /2.0)),ACC_ORDER,BOARD_Z);
        draw_circle_filled(FILL_F,(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),- (1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),ACC_ORDER,BOARD_Z);
        draw_circle_filled(FILL_F,-(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),(1 - I_O_L_G_F - I_I_L_G_F - A_L_G_F),ACC_ORDER,BOARD_Z);
        draw_circle_filled(FILL_F,-(1 - I_O_L_G_F - (I_I_L_G_F / 2.0)),-(1 - I_O_L_G_F - I_I_L_G_F -A_L_G_F),ACC_ORDER,BOARD_Z); //upto this point
        
        glColor3f(HOLE_COLOR);
        
        draw_circle_filled(CORNER_C_R_F,- (1 - CORNER_C_R_F) , ( 1 - CORNER_C_R_F),ACC_ORDER,BOARD_Z);
        draw_circle_filled(CORNER_C_R_F,(1 - CORNER_C_R_F) , ( 1 - CORNER_C_R_F),ACC_ORDER,BOARD_Z);
        draw_circle_filled(CORNER_C_R_F, (1 - CORNER_C_R_F) , - ( 1 - CORNER_C_R_F),ACC_ORDER,BOARD_Z);
        draw_circle_filled(CORNER_C_R_F,-(1 - CORNER_C_R_F) ,-  ( 1 - CORNER_C_R_F),ACC_ORDER,BOARD_Z);
                        
        glColor3f(EDGE_COLOR);
        
        DRAW_EDGES();
      
        
        glColor3f(BOARD_LINE_COLOR); 
        
        DRAW_BOARD_LINE_1();      
        DRAW_BOARD_LINE_2();
        DRAW_BOARD_LINE_3();
        DRAW_BOARD_LINE_4();              
        
      return ; 
}
