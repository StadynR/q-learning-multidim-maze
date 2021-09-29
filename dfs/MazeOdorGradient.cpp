 /************************ Maze Odor Gradient.cpp **********************************

Group Project of Artificial Intelligence 

July 22 2021
/*********************************************************************/ 
//
//  Students name:  Stadyn Román, Samantha Quintachala, Arianna Armijos, Washington Pijal
//
//------------------------------------------------------------------------------------------------
// GLOBALS
   
#define  files 28
#define  columns 28    //       size of the graphic maze   

int b_flag;
int stop;
char dummy[1];
//--
char key, color;

int x_agent, y_agent;
int x_cheese, y_cheese;

int x_plot_maze=30;
int y_plot_maze=30;

int square_size=50-33;        //
int captured_color;


//const int qSize = 6;
const float gamma = 0.8;

//int R[files][columns];
int S[files][columns];    //
int Q[files][columns];
int Q_p[files][columns];

int R[files][columns] = {
    {0,-1,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
    {0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,0,-1,0,-1},
    {0,0,0,-1,0,-1,0,-1,0,-1,0,-1,0,0,0,0,0,-1,0,-1,0,-1,0,0,0,-1,0,-1},
    {-1,-1,-1,-1,0,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1},
    {0,0,0,0,0,0,0,-1,0,-1,0,0,0,-1,0,0,0,-1,0,-1,0,0,0,-1,0,0,0,-1,},
    {0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,-1,-1,0,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1},
    {0,-1,0,0,0,-1,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,-1,0,0,0,-1,0,-1},
    {0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,0,-1,0,-1},
    {0,-1,0,0,0,0,0,-1,0,0,0,0,0,-1,0,0,0,0,0,-1,0,0,0,-1,0,-1,0,-1},
    {0,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,0,-1,0,-1},
    {0,-1,0,-1,0,-1,0,-1,0,-1,0,0,0,-1,0,0,0,0,0,0,0,0,0,-1,0,-1,0,-1},
    {0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,0,-1,0,-1},
    {0,-1,0,-1,0,0,0,0,0,0,0,-1,0,-1,0,-1,0,-1,0,-1,0,0,0,0,0,-1,0,-1},
    {0,-1,-1,-1,-1,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,0,-1},
    {0,0,0,-1,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
    {0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,0,-1,0,-1,-1,-1,0,-1},
    {0,-1,0,-1,0,0,0,0,0,-1,0,0,0,-1,0,-1,0,0,0,-1,0,-1,0,0,0,0,0,-1},
    {0,-1,-1,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1},
    {0,0,0,-1,0,-1,0,-1,0,-1,0,-1,0,0,0,-1,0,-1,0,-1,0,0,0,0,0,-1,0,-1},
    {0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1},
    {0,-1,0,-1,0,-1,0,-1,0,-1,0,0,0,-1,0,-1,0,-1,0,0,0,-1,0,0,0,0,0,-1},
    {-1,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1},
    {0,0,0,-1,0,0,0,-1,0,0,0,-1,0,-1,0,0,0,-1,0,-1,0,0,0,-1,0,-1,0,-1},
    {0,-1,-1,-1,-1,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1},
    {0,-1,0,0,0,-1,0,-1,0,-1,0,-1,0,-1,0,0,0,-1,0,-1,0,-1,0,0,0,-1,0,-1},
    {0,-1,0,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1},
    {0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,-1,0,0,0,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        };

int screen_image[files][columns];   //   presence  in pixels of the agent  and environment in the screen. Alter_ego  

int currentState;    

int move_flag;

int file_agent;    // file
int column_agent;  // column

int file_NPC;    // file
int column_NPC;  // column

int sensor[4];
int MAX;
int grad_pointer;

int path[files*columns*3][2];
int visited[files*columns][2];
int cont;
int stcont;
int mov;
int episode, step;

int file_cheese, column_cheese;
int player_captured_color;

unsigned t0, t1;

//----------------------------------------)))
//    end globals
//----------------------------------------)))
#include <sstream>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip.h>
#include <windows.h>
#include <ctime> 
#include <fstream>

#include "read_write_Q_matrix.h"
#include "plot_maze_items.h"
#include "Q_structures_lib.h"
#include "all_possible_mazes.h"    


//******************* variables globales ***************************************/
using namespace std;


//-----------------------------------------
//    inicia el modo grafico             
//-------------------------------------    
void grafico(void)
{
    int    GraphDriver;  /* The Graphics device driver */
    int    GraphMode;    /* The Graphics mode value */
    int    ErrorCode;    /* Reports any graphics errors */
   
    initgraph(&GraphDriver, &GraphMode, "");

    ErrorCode = graphresult();            /* Read result of initialization*/
    if( ErrorCode != grOk )              /* Error occured during init    */
    {-
       printf(" Graphics System Error: %s", grapherrormsg( ErrorCode ) );
       exit( 1 );
    }
}
//-------------------------------------  
void erase_screen(void)
{
    setcolor(LIGHTGRAY);
    bar(0,0,2400,900);  
}
//-------------------------------------------------------


void loadingBar()
{

    system("color 0A");

    char a = 177, b = 219;
  
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t + Loading...\n\n");
    printf("\t\t\t\t\t");
  
    for (int i = 0; i < 26; i++)
        printf("%c", a);

    printf("\r");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++) {
        printf("%c", b);
        Sleep(100);
    }

    system("cls");

    printf("\t\t Maze Gradient Odor\n");


}

void Start_Message(void){
  
  moveto(0,250); 
  settextstyle(4,0,4); 
  setcolor(GREEN);
  outtext("Welcome to the Maze Gradient Program ");


  moveto(0,300); 
  settextstyle(9,0,4); 
  setcolor(GREEN);
  outtext("Maximize the window size ");

  //loadingBar();

  erase_screen();

  moveto(600,0); 
  settextstyle(9,0,2); 
  setcolor(WHITE);
  outtext(" Maze Gradient Program  ");

}
//-------------------------------------------------------------
void loop(void)  //                                                           loop  !!                        &&&/&&/&&/////
{
    bool go=true;
    
    string datas;
    episode=1;             // 

    do{
        //plot_maze();
        //plot_olor_gradient();
        //plot_agent();
        //print_R();
        //print_S();   //  gradiente de olor
        
        cout <<" ready to exploit-- " <<endl; 
         
        //getch();        
        Q_explore();
        
        go = check_q(go); //ver si esta estable Q
        if(go){
            string str; // a variable of str data type
            string strtim; // a variable of str data type
            string strcc; // a variable of str data type
    
            stringstream ss; 
            stringstream tt; 
            stringstream cc;  
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
      
            ss << episode;  
            ss >> str;  
    
            datas.append("episode: "+str+"\n");
    
            tt << time;  
            tt >> strtim; 
            datas.append("Execution Time: "+strtim+"\n");
            
            cc << step;  
            cc >> strcc; 
            datas.append("Ciclos: "+strcc+"\n\n");
            
            episode++;
            cout<<datas<<endl;
        }
        random_agent();
    }while(go);
    
    print_visited();
    print_path();
    plot_path();
    print_S();   

    salvar_Q();    
    salvar_data(datas);   
    Beep(700, 50);
    Beep(2700,50);
  
}   
//------------------------------------------------------
void choose(void)
{
        //erase_screen();
        
    
        moveto(40,420+100); 
        settextstyle(4,0,4); 
        setcolor(GREEN);
        outtext(" Do you want to restart the environment? Press 'R' "); 
        
        moveto(20,470+100); 
        settextstyle(4,0,4); 
        setcolor(GREEN);
        outtext(" Do you want change the cheese position? Press 'C' "); 
        
        moveto(50,520+100); 
        settextstyle(4,0,4); 
        setcolor(GREEN);
        outtext(" Do you want change the maze? Press 'M' ");
    
        moveto(50,570+100); 
        settextstyle(4,0,4); 
        setcolor(GREEN);
        outtext(" Do you want change the agent position? Press 'A' ");     
        
        do{
            key=getch();
            switch(key){
                case 'R': case 'r':  //cambia todo el ambiente
                {
                    init_R();
                    random_cheese();
                    init_S();
                    random_agent();
                    plot_maze();
                    plot_agent();
                    plot_cheese();
                } break;
                case'C': case 'c':   // cambia solo el queso
                {
                    random_cheese();
                    init_S();
                    plot_maze();
                    plot_agent();
                    plot_cheese();
                } break;
                case'M': case 'm':    //cambia el maze
                {
                    init_R();
                    init_S();
                    plot_maze();
                    plot_agent();
                    plot_cheese();
                    
                } break;
                case'A': case 'a':     //cambia el agente
                {
                    random_agent();
                    plot_maze();
                    plot_agent();
                    plot_cheese();
                } break;
                case ' ':
                {
                    loop();
                    random_agent();
                }
            }
        }while(key!='x' && key!='X');
}
//===================================================================================================
void main(void)
{ 
    int rand_seed=37;     // 26
    int temp;
    char str[10];  
    grafico();
    setcolor(LIGHTGRAY);
    bar(0,0,2400,900);  

    srand(rand_seed);  

    randomize();

    //file_agent=0;               
    //column_agent=0;             

    Start_Message();       // Messegae of welcome
    
    //init_R();                  //We get a random MAZE
    //random_cheese();
    file_cheese=14;   //  x_cheese:  coordinate x of agent in the screen    
    column_cheese=12;   //  y_cheese:  coordinate y of agent in the screen  
    
    init_S();
    random_agent();

    x_agent=x_plot_maze;   //  x_agent:  coordinate x of agent in the screen    
    y_agent=y_plot_maze;   //  y_agent:  coordinate y of agent in the screen  

    print_R();
    print_S();   //  gradiente de olor
    plot_maze();
    plot_agent();
    plot_cheese();
    //plot_olor_gradient();
    
    stop=0;
    //loop();
    choose();

    /*
    moveto(120,0);  // PRINT SCORE
    setcolor(WHITE);
    outtext("Score: ");
    outtextxy(175,0,gcvt(score,6,str)); 
    loop();

    do {
       //play_flag=0; 
       key=getch();
       switch (key) {

            /*                        
           case 'w':          {
                               move_up();
                               check_reward();
                               plot_all(); 
                               loop();                             
                              } 
           break;     
           case ' ':          {          
                               stop=stop^1;
                               loop();
                              }                                     
           break; 
                              
            case 'R': case 'r':  {
                                   init_R();
                                   init_S();
                                   random_agent();
                                   plot_maze();
                                   plot_agent();
                                 }
            break;                     
            
            default:
                loop();
         }
   } while ((key!='x')&&(key!='X'));*/

   closegraph();
   clrscr();
}

//---------------------------------------
/*
BLACK        Â³  0  Â³ Yes Â³ Yes
BLUE         Â³  1  Â³ Yes Â³ Yes
GREEN        Â³  2  Â³ Yes Â³ Yes
CYAN         Â³  3  Â³ Yes Â³ Yes
RED          Â³  4  Â³ Yes Â³ Yes
MAGENTA      Â³  5  Â³ Yes Â³ Yes
BROWN        Â³  6  Â³ Yes Â³ Yes
LIGHTGRAY    Â³  7  Â³ Yes Â³ Yes
DARKGRAY     Â³  8  Â³ No  Â³ Yes
LIGHTBLUE    Â³  9  Â³ No  Â³ Yes
LIGHTGREEN   Â³ 10  Â³ No  Â³ Yes
LIGHTCYAN    Â³ 11  Â³ No  Â³ Yes
LIGHTRED     Â³ 12  Â³ No  Â³ Yes
LIGHTMAGENTA Â³ 13  Â³ No  Â³ Yes
YELLOW       Â³ 14  Â³ No  Â³ Yes
WHITE        Â³ 15  Â³ No  Â³ Yes

----------------------------------------------------------------
     if(x<0)    { x=0; if( heat<100) heat++;}     
     if(y<35)    { y=35; if( heat<100) heat++;}  
     if(x>640) { x=640; if( heat<100) heat++;}  //  x>1200 : full pantalla 
     if(y>470) { y=470; if( heat<100) heat++;}   // y>720 : full pantalla 
         
//--------------------------------------------------

************************ basic_robot.cpp ***************************
desarrollado usando Dev-C++ IDE V4.9.8.4 GNU / MinGW / GNU gcc
                    Sc1 IDE / BCC5.5
                    version orginal por Oscar Chang
*********************************************************************/

