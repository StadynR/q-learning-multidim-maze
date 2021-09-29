//---------------------------------
//         RUTINA PLOT NET ITEMS    --    GRAFICA los parametros de la matriz Q 
void Game_Over(void);
//-----------------------------------------
void plot_maze(void)               ////       PLOT MAZE GRAPHICS
{
int i,j,sx,sy,x,y,color,scale; 
int temp; 
    
x= x_plot_maze;
y= y_plot_maze;   
scale=square_size;
   
   for(i=0;i<files;i++)  // 
     { 
      y=y_plot_maze;   
      sy = y+i*scale;             
      for(j=0;j<columns;j++)
         {    
          sx = x+j*scale;
          temp=R[i][j];  
          
          //timp= Entrada[counter];  
          color=LIGHTGRAY; 
          if(temp<0) color=BLACK;          // WALL
          if(temp==0) color=LIGHTGRAY;          // FLOOR    
          //if(temp==100) color=YELLOW;     // TOP REWARD
          setcolor(color); 
          setfillstyle(SOLID_FILL,color); 
          bar(sx,sy,sx+scale,sy+scale) ;  
          //putpixel(sx,sy, color);      
          //y++;  
         }
       //x++;  
     } 
 
}
//----------------------------------------------------------------------------------------
void plot_trail(void)           
{
    int color;  
    int x,y;    
    
     x= x_plot_maze;   //   para sincronizarse con el enviroment grafico
     y= y_plot_maze;   //   
       
    x_agent=x+column_agent*square_size;
    y_agent=y+file_agent*square_size;
    
    //captured_color=getpixel(x_agent,y_agent);   //  el sensor captura en una esquina
     
     setcolor(LIGHTRED); //  
     setfillstyle(SOLID_FILL,LIGHTRED);   
     bar(x_agent,y_agent,x_agent+square_size,y_agent+square_size);
}
//----------------------------------------------------------------------------------------
void plot_agent(void)
{
int color,agent_size=square_size-3;  
int x,y;    
    
int offset_x=5;   //   para centrar al agente en x
int offset_y=5;   //   para centrar al agente en y

 x= x_plot_maze;   //   para sincronizarse con el enviroment grafico
 y= y_plot_maze;   //   
   
    x_agent=x+column_agent*square_size;
    y_agent=y+file_agent*square_size;
    
    captured_color=getpixel(x_agent,y_agent);   //  el sensor captura en una esquina
 
 setcolor(RED); //  
 setfillstyle(SOLID_FILL,RED);   
 bar(x_agent+offset_x,y_agent+offset_y,x_agent+agent_size,y_agent+agent_size) ;   
    
}

//----------------------------------------------------------------------------------------------------     
void plot_cheese(void)
{
int color,cheese_size=square_size;  
int x,y;    

 x= x_plot_maze;   //   para sincronizarse con el enviroment grafico
 y= y_plot_maze;   //   
   
    x_cheese=x+column_cheese*square_size;
    y_cheese=y+file_cheese*square_size;
    
    captured_color=getpixel(x_cheese,y_cheese);   //  el sensor captura en una esquina
 
 setcolor(YELLOW); //  
 setfillstyle(SOLID_FILL,RED);   
 bar(x_cheese,y_cheese,x_cheese+cheese_size,y_cheese+cheese_size) ;   
    
}

//----------------------------------------------------------------------------------------------------     
void plot_path(void)           
{
    int row, col, color;  
    int x,y;    
    
     x= x_plot_maze;   //   para sincronizarse con el enviroment grafico
     y= y_plot_maze;   //   
     
    for(int i = 0; i < stcont; i++){
     color = (i == 0)? GREEN: BLUE; 
     row = path[i][0];
     col = path[i][1];
     x_agent=x+col*square_size;
     y_agent=y+row*square_size;
     setcolor(color); //  
     setfillstyle(SOLID_FILL,color);   
     bar(x_agent,y_agent,x_agent+square_size,y_agent+square_size);
    }
}
//----------------------------------------------------------------------------------------
void plot_olor_gradient(void)               ////       PLOT MAZE GRAPHICS
{
   int i,j,sx,sy,x,y,color,scale,a,b,c,d; 
   int temp; 
    
   x= x_plot_maze;
   y= y_plot_maze;   
   scale=square_size;


   for(int k=0;k<columns;k++){
      //restric files
      a = file_cheese-k; b = file_cheese+k;
      if(a<0) a=0; //do not exit the maze
      if(b>files) b = files-1; //do not exit the maze

      //restirc columns
      c = column_cheese-k; d = column_cheese+k;
      if(c<0) c=0;
      if(d>columns) d = columns-1;

      for(i=a;i<b;i++){
         y=y_plot_maze;   
         sy = y+i*scale; 
         for(j=c;j<d;j++){
          sx = x+j*scale;
          temp=S[i][j];   
          if(temp>0 && temp<=25) color=LIGHTGREEN;          
          if(temp>25&& temp<=50) color=LIGHTCYAN;            
          if(temp>50&& temp<=75) color=LIGHTMAGENTA;     
          if(temp>75&& temp<=99) color=LIGHTBLUE;     
          if(temp==100) color=YELLOW;     // TOP REWARD
          if(temp>0){
             setcolor(color); 
             setfillstyle(SOLID_FILL,color); 
             bar(sx,sy,sx+scale,sy+scale) ;  
           }

          //if(i==file_agent && j==column_agent) plot_agent();
         }
      }
      Sleep(10);
   }
}
//----------------------------------------------------------------------------------------

//
// cout <<" x_agent: "<< x_agent <<endl; 
// cout <<" y_agent: "<< y_agent <<endl;    
// cout <<" color: "<< captured_color <<endl<<endl;    
    
 //file_agent= (y_agent/square_size)- y_plot_maze;
    
 //cout <<" file_agent: "<< file_agent <<endl;    


