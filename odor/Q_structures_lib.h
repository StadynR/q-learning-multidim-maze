//===========================================================================
//  DEFINICION DE ESTRUCTURAS Q 
//========================================================================
//----------------------------------------------------------------------------------------------------     
void print_R(void)
{
 int i,j;
    
    printf("This is the R Matrix:\n \n");
    for(i = 0; i < files; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(4) << R[i][j];   
		} 
        cout << "\n";
	} 
    cout << "\n";
}
//----------------------------------------------------------------------------------------------------     
void print_Q(void)
{
 int i,j;
    
    printf("This is the Q Matrix:\n \n");
    for(i = 0; i < files; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(4) << Q[i][j];   
		} 
        cout << "\n";
	} 
    cout << "\n";
}
//---------------------------------------------------------------------------------------------
void print_S(void)
{
 int i,j;
    
    printf("This is the S Matrix:\n \n");
    for(i = 0; i < files; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(4) << S[i][j];   
		}
        cout << "\n";
	} 
    cout << "\n";
}
//------------------------------------------------------------------------------------------------
void init_S(void)
{
 float lambda=10;    //  costante de decaimiento con la distancia
 //float N=1.0;         //   N : scent concentration in a given square
 float step=0.01;     // cuanto se avanza en cada loop  
 int k, distx, disty;
 
   for (int i=0; i < files; i++)
   for (int j=0; j < columns; j++)
    S[i][j]=-1;
    
   for (int i=0; i < files; i++)
   for (int j=0; j < columns; j++)
    {
     disty = i-file_cheese;
     distx = j-column_cheese;
     k = sqrt(distx*distx+disty*disty);   // distancia pitagoras a coordenadas (0,0)
     if(R[i][j]!=-1) S[i][j]=100* exp(-lambda*step*k);  // concentracion % a esa distancia
    }   
    //   se consulta a la matriz R por lo tanto el gradiente sigue la ley de las paredes
}
//-------------------------------------------------------------
void print_visited(){
    cout << "Visited: ";
    for(int i = 0; i <= cont; i++){
        cout << "[" << visited[i][0] << ", " << visited[i][1] << "] ";
    }
    cout << endl;
}
//------------------------------------------------------------
void print_path(){
    cout << "Path: ";
    for(int i = 0; i <= stcont; i++){
        cout << "[" << path[i][0] << ", " << path[i][1] << "] ";
    }
    cout << endl;
}
//------------------------------------------------------------
void clear_visited(){
    for(int i = 0; i <= cont; i++){
        visited[i][0] = -1;
        visited[i][1] = -1;
    }
}
//------------------------------------------------------------
void clear_path(){
    for(int i = 0; i <= stcont; i++){
        path[i][0] = -1;
        path[i][1] = -1;
    }
}
//------------------------------------------------------------
void move_left(void)
{
 int temp;
    temp=getpixel(x_agent-square_size,y_agent);   // revisa cercania a la izquierda
    if(temp!=BLACK) // movimiento válido
    {  
     x_agent=x_agent-square_size;
     column_agent--;
    }    
}
//--------------------------------------------------------------
void move_right(void)
{
 int temp;   
  temp=getpixel(x_agent+square_size,y_agent);   // revisa cercania a la derecha
  if(temp!=BLACK)
     {
      x_agent=x_agent+square_size;
      column_agent++; 
     }  
}
//-------------------------------------------------------------
void move_up(void)
{
 int temp;
    temp=getpixel(x_agent,y_agent-square_size);   // revisa cercania arriba
    if(temp!=BLACK)
    {
     y_agent=y_agent-square_size;
     file_agent--;
    }  
}
//-------------------------------------------------------------
void move_down(void)
{
 int temp;
   temp=getpixel(x_agent,y_agent+square_size);    // revisa cercania abajo
   if(temp!=BLACK)
   {
    y_agent=y_agent+square_size; 
    file_agent++;
   }   
}
//-------------------------------------------------------------
bool no_unvisited() 
{ 
    bool f = true;
    
    for(int i = 0; i < 4; i++){
        if(sensor[i] != -1){
            f = false; 
            break;
        }
    }
    
    return f;
}
//------------------------------------------------------------
bool already_visited(int row, int col) 
{ 
    bool f = false;
    
    for(int i = 0; i < cont; i++){
        if(visited[i][0] == row && visited[i][1] == col){
            f = true; 
            break;
        }
    }
    
    return f;
}
//--------------------------------------------------------
void search_for_MAX_unvisited(void) 
{
 int i,j, sum = 0, r, lim_l, lim_r;
    
    sensor[0]= S[file_agent][column_agent-1];    // lee  a izquierda
    if(column_agent==0 || already_visited(file_agent, column_agent-1)) sensor[0]=-1;            // desborde a la izquierd  
        
    sensor[1]= S[file_agent][column_agent+1];    // lee a  derecha
    if(column_agent==columns-1 || already_visited(file_agent, column_agent+1)) sensor[1]=-1;
    
    sensor[2]= S[file_agent-1][column_agent];    // lee arriba
    if(file_agent==0 || already_visited(file_agent-1, column_agent)) sensor[2]=-1;
    
    sensor[3]= S[file_agent+1][column_agent];    // lee abjo
    if(file_agent==files-1 || already_visited(file_agent+1, column_agent)) sensor[3]=-1;

    //MAX=sensor[0];
    //for(i=0;i<4;i++) if(sensor[i]>=MAX) {MAX=sensor[i];grad_pointer=i;}  // grad_pointer apunta al maximo valor
    
    if(no_unvisited()) MAX = -1;
    else{
        for(i=0;i<4;i++){
        if(sensor[i] != -1)
            sum+=sensor[i];
        }
        if(sum > 1) r = random(sum); else r = 0;
        //cout << "suma: " << sum << " r: " << r << endl;
        //getch();
        lim_l = 0;
        for(i=0;i<4;i++){ 
            if(sensor[i]!=-1){
                lim_r = sensor[i] + lim_l;
                if(r >= lim_l && r <= lim_r){
                    MAX=sensor[i];
                    grad_pointer = i;
                    break;
                }
                lim_l = lim_r;
            }
        }
    }
}
//------------------------------------------------------------
void search_for_MAX(void) 
{
 int i,j, sum=0, r, lim_l, lim_r;
    
    sensor[0]= S[file_agent][column_agent-1];    // lee  a izquierda
    if(column_agent==0) sensor[0]=-1;            // desborde a la izquierd  
        
    sensor[1]= S[file_agent][column_agent+1];    // lee a  derecha
    if(column_agent==columns-1) sensor[1]=-1;
    
    sensor[2]= S[file_agent-1][column_agent];    // lee arriba
    if(file_agent==0) sensor[2]=-1;
    
    sensor[3]= S[file_agent+1][column_agent];    // lee abjo
    if(file_agent==files-1) sensor[3]=-1;
        
    
    for(i=0;i<4;i++){
        if(sensor[i] != -1)
            sum+=sensor[i];
    }
    //cout << "suma: " << sum << endl;
    //getch();
    
    if(sum > 1) r = random(sum); else r = 0;
    //cout << "suma: " << sum << " r: " << r << endl;
    //getch();
    lim_l = 0;
    for(i=0;i<4;i++){ 
        if(sensor[i]!=-1){
            lim_r = sensor[i] + lim_l;
            if(r >= lim_l && r <= lim_r){
                //MAX=sensor[i];
                grad_pointer = i;
                break;
            }
            lim_l = lim_r;
        }
    }
}
//------------------------------------------------------------
void search_for_MAX_Q(void) 
{
 int i,j, sum=0, r, lim_l, lim_r;
    
    sensor[0]= Q[file_agent][column_agent-1];    // lee  a izquierda
    if(column_agent==0) sensor[0]=-1;            // desborde a la izquierd  
        
    sensor[1]= Q[file_agent][column_agent+1];    // lee a  derecha
    if(column_agent==columns-1) sensor[1]=-1;
    
    sensor[2]= Q[file_agent-1][column_agent];    // lee arriba
    if(file_agent==0) sensor[2]=-1;
    
    sensor[3]= Q[file_agent+1][column_agent];    // lee abjo
    if(file_agent==files-1) sensor[3]=-1;
    
    MAX=sensor[0];
    for(i=0;i<4;i++) if(sensor[i]>=MAX) {MAX=sensor[i];}  // grad_pointer apunta al maximo valor
    //cout <<" MAX: "<< MAX <<endl; 
}
//------------------------------------------------------------
void backtrack() 
{ 
    int temp;
    
    //cout << "bfile: " << file_agent << " bcol: " << column_agent << endl;
    
    temp = R[file_agent][column_agent-1];
    if(column_agent == 0) temp = -1;
    if(temp != -1 && file_agent == path[stcont][0] && column_agent-1 == path[stcont][1]){
        //cout << "Backtrack left: " << temp << endl;
        mov = 0;
        return;
    }
    
    temp = R[file_agent][column_agent+1];
    if(column_agent == columns-1) temp = -1;
    if(temp != -1 && file_agent == path[stcont][0] && column_agent+1 == path[stcont][1]){ 
        //cout << "Backtrack right: " << temp << endl;
        mov = 1;
        return;
    }
    
    temp = R[file_agent-1][column_agent];
    if(file_agent == 0) temp = -1;
    if(temp != -1 && file_agent-1 == path[stcont][0] && column_agent == path[stcont][1]){ 
        //cout << "Backtrack up: " << temp << endl;
        mov = 2;
        return;
    }
    
    temp = R[file_agent+1][column_agent];
    if(file_agent == files-1) temp = -1;
    if(temp != -1 && file_agent+1 == path[stcont][0] && column_agent == path[stcont][1]){ 
        //cout << "Backtrack down: " << temp << endl;
        mov = 3;
        return;
    }
}
//------------------------------------------------------------
void DFS(){
      
     path[stcont][0] = file_agent;
     path[stcont][1] = column_agent;
     visited[cont][0] = file_agent;
     visited[cont][1] = column_agent;    
     //cout << "Stack pos: " << stcont << " , row: " << file_agent << " , col: " << column_agent << endl;
     //print_visited();
    
     search_for_MAX();
     //cout << "max: " << MAX << " mov: " << grad_pointer << endl;
     //getch();
     if (MAX == -1){
         stcont--;
         cont++;
         backtrack();
     }
     else{
         cont++;
         stcont++;       
         mov = grad_pointer;          // el agente se mueve a un nuevo estado
         }
} 
//-----------------------------------
void save_q(void){
    int i, j;
    for(i=0;i<files;i++){
        for(j=0;j<columns;j++){
            Q_p[i][j]=Q[i][j];
        }
    }    
}
//-------------------------------------------------------
bool check_q(bool go){
    int i, j;
    go = false;
    for(i=0;i<files;i++){
        for(j=0;j<columns;j++){
            if(Q[i][j]!=Q_p[i][j]){
                go=true;
                break;
            }
        }
    }
    return go;
}
//-------------------------------------------------------
void random_agent(void){
    int i, j;
    do{
        i = random(files);
        j = random(columns);
        if(R[i][j]==0 || R[i][j]==100){ //if it is not in the wall or in the 
            file_agent=i;           
            column_agent=j;  
        }
    }while(R[i][j]<0); 
} 
//---------------------------------------------------------

void random_cheese(void){
    int i, j;
    do{
        i = random(files);
        j = random(columns);
        if(R[i][j]==0 || R[i][j]==100){ //if it is not in the wall or in the 
            file_cheese=i;           
            column_cheese=j;  
        }
    }while(R[i][j]<0); 
} 
//---------------------------------------------------------
void Q_explore(void)  
{
    int episode, step;
    bool go=true;
    
    string datas;
    
     randomize(); 

     //plot_maze();
     plot_agent();
     
     clear_visited();
     clear_path();
     cont = 0;
     stcont = 0;
         
     episode=1;             // 
    do{
         save_q();//save previous Q
         plot_maze();
         plot_olor_gradient();
         plot_agent();
         print_Q();
         //print_R();
         //print_S();   //  gradiente de olor
         step=0;
         t0=clock();
         do
          {
              
           search_for_MAX();
           mov = grad_pointer;
            
           plot_trail();              
           if(mov==0) move_left();
           if(mov==1) move_right(); 
           if(mov==2) move_up();
           if(mov==3) move_down();
               
           search_for_MAX_Q();
           Q[file_agent][column_agent]= S[file_agent][column_agent]+ gamma*MAX;
           
           //plot_maze();
           plot_agent();                     //  sensor captures color
           if(kbhit())
            {
                key=getch();
                if(key=='P' || key=='p')
                        getch();
            }
           delay(31);
           step++;
         }while(captured_color!=YELLOW);     //hasta que capture recompensa maxima o haya tardado mucho
         
        t1 = clock();
         
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
            datas.append("Steps: "+strcc+"\n\n");
            
            episode++;
            cout<<datas<<endl;
        }
        random_agent();
    
    }while(go);  // Unitil Q matix is stablish     
     
    print_visited();
    print_path();
    plot_path();
    print_S();   

    salvar_Q();    
    salvar_data(datas);
    Beep(700, 50);
    Beep(2700,50);
    
    //cout <<" one problem solved-- " <<endl;    
}  
//--------------------------------------------------------

