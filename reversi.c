#include<X11/Xlib.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h> 
#include <stdbool.h>
#include <errno.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#define SHARED_KEY_1 9123
#define SHARED_KEY_2 9124
#define BLACK 0
#define WHITE 1
#define PLAYABLE 2
#define FALSE 0
#define TRUE  1
#define EMPTY 3
Display *display;
int s;
Window window;
XEvent event;


int *score1;
int *score2;
int *player;
int id_reversi;
int ktory;
int *plansza;
int game_ended = 0;
int wrong_move = 0;
int has_valid_move = 0;
int skipped_turn = 0;
int amount_arcs;
XArc *arcs;
int playable_direction[8][8][8];
char str1[12]="000";
char str2[12]="000";

const char *row_names = "01234567";
const char *col_names = "01234567";

int a,b;

int Pobierz(int x,int y)
{
  return *(plansza + (x*8+y));  
}


void Wstaw(int x,int y,int wartosc)
{
  *(plansza + (x*8+y))=wartosc;
}


int  AlokujPamiec()
{
  id_reversi=shmget(SHARED_KEY_1,sizeof(int)*68,0666 | IPC_CREAT | IPC_EXCL);
  
  if(id_reversi==-1)
  {

    if(errno==EEXIST)
    {
      id_reversi=shmget(SHARED_KEY_1,sizeof(int)*68,0);
      int *adres = shmat(id_reversi,NULL,0);
      plansza=adres;
            
      player=plansza+64;
      score1=plansza+65;
      score2=plansza+66;
      ktory=1;
      
      return 1;

    }
    else
    {
      return -1;
    }
  }

  int *adres = shmat(id_reversi,NULL,0);
  plansza=adres;

  player=plansza+64;
  score1=plansza+65;
  score2=plansza+66;
    
  *player=0;
  *score1=2;
  *score2=2;
    

  ktory=0;


  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
      Wstaw(i,j,3);
    }
  }
  
  Wstaw(3,3,BLACK);
  Wstaw(4,4,BLACK);
  Wstaw(3,4,WHITE);
  Wstaw(4,3,WHITE);
  

  return 1;

}


int CzyszczeniePamieci()
{
  shmdt(plansza); 
  shmctl(id_reversi,IPC_RMID,0);
  exit(0);
}

unsigned long Kolor( char* color_name )
{

  Colormap cmap;
  XColor near_color, true_color;
  cmap = DefaultColormap( display, 0 );
  XAllocNamedColor( display, cmap, color_name, &near_color, &true_color );
  return( near_color.pixel );
}

void Polaczenie()
{
     /* open connection with the server */
   display=XOpenDisplay(NULL);
   if(display==NULL) 
   {
    printf("Cannot open display\n");
    exit(1);
   }
   s=DefaultScreen(display);

}


void UtowrzenieOkna()
{
    /* create window */
   window=XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 1000, 800, 1,
                         BlackPixel(display, s), WhitePixel(display, s));

   // Process Window Close Event through event handler so XNextEvent does Not fail
   Atom delWindow = XInternAtom( display, "WM_DELETE_WINDOW", 0 );
   XSetWMProtocols(display , window, &delWindow, 1);

    /* select kind of events we are interested in */
   XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);

    /* map (show) the window */
   XMapWindow(display, window);

}

void ZamknijPolaczenie()
{
   /* destroy our window */
   XDestroyWindow(display, window);

    /* close connection to server */
   XCloseDisplay(display);

}


bool Koniec()
{
  if(game_ended)
    return true;
  else
    return false;
}

void WyswietlKoniec()
{
  if(*score1<*score2)
    XDrawString(display, window, DefaultGC(display, s), 860, 500, "Wgygral RED", 11);
  if(*score1>*score2)
    XDrawString(display, window, DefaultGC(display, s), 860, 500, "Wgygral BLACK", 13);
  if(*score1==*score2)
     XDrawString(display, window, DefaultGC(display, s), 860, 500, "REMIS",5 );
}

void display_current_player( )
{

    if ( *player == WHITE )
     {
       XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor( "white"));
        usleep(5000);
        
        XDrawString(display, window, DefaultGC(display, s), 860, 200, "BLACK PLAYER", 12);
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor( "red"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 860, 200, "RED PLAYER", 10);
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor( "black"));
        usleep(5000);
      }
    else
    {

        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor(  "white"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 860, 200, "RED PLAYER", 10);
       
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor(  "black"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 860, 200, "BLACK PLAYER", 12);
        
        
    }
        
    printf( "\n" );
}

void RysujPlansze()
{
  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
  usleep(5000);
  XDrawLine(display, window, DefaultGC(display, s), 100, 0, 100, 800);
  XDrawLine(display, window, DefaultGC(display, s), 200, 0, 200, 800);
  XDrawLine(display, window, DefaultGC(display, s), 300, 0, 300, 800);
  XDrawLine(display, window, DefaultGC(display, s), 400, 0, 400, 800);
  XDrawLine(display, window, DefaultGC(display, s), 500, 0, 500, 800);
  XDrawLine(display, window, DefaultGC(display, s), 600, 0, 600, 800);
  XDrawLine(display, window, DefaultGC(display, s), 700, 0, 700, 800);
  XDrawLine(display, window, DefaultGC(display, s), 800, 0, 800, 800);
  XDrawLine(display, window, DefaultGC(display, s), 0, 100, 800, 100);
  XDrawLine(display, window, DefaultGC(display, s), 0, 200, 800, 200);
  XDrawLine(display, window, DefaultGC(display, s), 0, 300, 800, 300);
  XDrawLine(display, window, DefaultGC(display, s), 0, 400, 800, 400);
  XDrawLine(display, window, DefaultGC(display, s), 0, 500, 800, 500);
  XDrawLine(display, window, DefaultGC(display, s), 0, 600, 800, 600);
  XDrawLine(display, window, DefaultGC(display, s), 0, 700, 800, 700);
  XDrawString(display, window, DefaultGC(display, s), 875, 150, "REVERSI", 7);
  usleep(5000);

}


void SetArcsToFill(int cos)
{
  amount_arcs=0;

  for(int i=0;i<8;i++)
      {
        for(int j=0;j<8;j++)
        {
          
          if(Pobierz(i,j)==BLACK && cos==BLACK)
          {
            
            arcs[amount_arcs].x=i*100+10;
            arcs[amount_arcs].y=j*100+10;
            arcs[amount_arcs].width=80;
            arcs[amount_arcs].height=80;
            arcs[amount_arcs].angle1=360*64;
            arcs[amount_arcs].angle2=360*64;
            amount_arcs++;
          }

          if(Pobierz(i,j)==WHITE && cos==WHITE)
          {
            arcs[amount_arcs].x=i*100+10;
            arcs[amount_arcs].y=j*100+10;
            arcs[amount_arcs].width=80;
            arcs[amount_arcs].height=80;
            arcs[amount_arcs].angle1=360*64;
            arcs[amount_arcs].angle2=360*64;
            amount_arcs++;
          }

        }
      }


}


void UstawPunkty()
{
  a=0;
  b=0;

  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
      if(Pobierz(i,j)==BLACK)
        a++;
      if(Pobierz(i,j)==WHITE)
        b++;
    }
  }


printf("punkty %d %d\n",a,b);

}




void WyswietlPunkty()
{
  
 
  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
  usleep(5000);
  XDrawString(display, window, DefaultGC(display, s), 810, 300, "BLACK PLAYER", 12);
  
  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("red"));
  usleep(5000);
  XDrawString(display, window, DefaultGC(display, s), 900, 300, "RED PLAYER", 10);
  usleep(500);



  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("white"));
  usleep(5000);
  XDrawString(display, window, DefaultGC(display, s), 835, 320, str1, strlen(str1));
  XDrawString(display, window, DefaultGC(display, s), 925, 320, str2, strlen(str2));


  usleep(5000);
  //printf("jestem tu 1 %d\n",*player);
  UstawPunkty();
  printf("punkty %d %d\n",a,b);
 // printf("jestem tu 2 %d\n",*player);
  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
  usleep(500);
  sprintf(str1, "%d", a);
  XDrawString(display, window, DefaultGC(display, s), 835, 320, str1, strlen(str1));

  sprintf(str2, "%d", b);
  XDrawString(display, window, DefaultGC(display, s), 925, 320, str2, strlen(str2));
}

void WyswietlKola()
{
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
     
      if(Pobierz(i,j)==WHITE)
      {
        
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("red"));
        usleep(5000);
        SetArcsToFill(WHITE);
        XFillArcs(display, window, DefaultGC(display, s),arcs,amount_arcs);
        XDrawArc(display, window, DefaultGC(display, s), i*100+10, j*100+10, 80, 80, 0, 360*64);
      }else
       if(Pobierz(i,j)==BLACK)
      {
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
        usleep(5000);
        
        SetArcsToFill(BLACK);
        
        XFillArcs(display, window, DefaultGC(display, s),arcs,amount_arcs);
        XDrawArc(display, window, DefaultGC(display, s), i*100+10, j*100+10, 80, 80, 0, 360*64);
         
      }

    }
  }
}
int distance( int i1, int j1, int i2, int j2 )
{
    int di = abs( i1 - i2 ), dj = abs( j1 - j2 );
    if ( di > 0 ) return di;
    return dj;
}

void change_current_player( )
{
  if(*player==BLACK)
    *player=WHITE;
  else
    *player=BLACK;
}


void mark_playable_positions( )
{
  int licznik=0;
    has_valid_move = FALSE;
    for ( int i=0; i<8; ++i )
    {
        for ( int j=0; j<8; ++j )
        {

            if ( Pobierz(i,j) == PLAYABLE )
                { 
                 Wstaw(i,j,EMPTY);
                }
            if ( is_playable( i, j ) )
            {

                Wstaw(i,j,PLAYABLE);
                has_valid_move = TRUE;
            }
        }
    }
}



int is_playable( int i, int j )
{
  
    memset( playable_direction[i][j], 0, 8 );
    
    if ( Pobierz(i,j) != EMPTY ) return FALSE;
    int playable = FALSE;
    int pom = *player;
    int opposing_player = ( pom + 1 ) % 2;
    
    // Test UL diagonal
        
    int i_it = i-1, j_it = j-1;
    
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {
    while ( Pobierz(i_it,j_it) == opposing_player )
    {
        i_it -= 1;
        j_it -= 1;
        if(i_it<0 && j_it<0)
        break;
    }}
    
    if ( distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][0] = 1;
        playable = TRUE;
    }
    
    
    // Test UP path
    i_it = i-1, j_it = j;
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {while (  Pobierz(i_it,j_it) == opposing_player )
        i_it -= 1;}

  


    if (  distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][1] = 1;
        playable = TRUE;
    }
    
    //printf("%d %d\n",i_it,j_it );
    // Test UR diagonal
    i_it = i-1, j_it = j+1;
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {while (  Pobierz(i_it,j_it) == opposing_player )
    {
        i_it -= 1;
        j_it += 1;
    }}
    if (  distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][2] = 1;
        playable = TRUE;
    }

    // Test LEFT path
    i_it = i, j_it = j-1;
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {while (  Pobierz(i_it,j_it) == opposing_player )
        j_it -= 1;}

    if (  distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][3] = 1;
        playable = TRUE;
    }

    // Test RIGHT path
    i_it = i, j_it = j+1;
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {while (  Pobierz(i_it,j_it) == opposing_player )
        j_it += 1;}

    if (  distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][4] = 1;
        playable = TRUE;
    }

    // Test DL diagonal
    i_it = i+1, j_it = j-1;
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {while (  Pobierz(i_it,j_it) == opposing_player )
    {
        i_it += 1;
        j_it -= 1;
    }}
    if (  distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][5] = 1;
        playable = TRUE;
    }
  
    // Test DOWN path
    i_it = i+1, j_it = j;
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {while (  Pobierz(i_it,j_it) == opposing_player )
    {
      i_it += 1;
     //if(i_it>15)
    // break;
     //printf("%d\n",i_it);//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }}
    
    if (  distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][6] = 1;
        playable = TRUE;
    }
    

    // Test DR diagonal
    i_it = i+1, j_it = j+1;
    if(i_it>=0 && i_it<8 && j_it>=0 && j_it<8 )
    {while (  Pobierz(i_it,j_it) == opposing_player )
    {
        i_it += 1;
        j_it += 1;
    }}
    
    if (  distance( i, j, i_it, j_it ) > 1 && Pobierz(i_it,j_it) == *player )
    {
        playable_direction[i][j][7] = 1;
        playable = TRUE;
    }
    
    return playable;
}

void capture_pieces( int i, int j )
{
    int pom=*player;
    int opposing_player = ( pom + 1 ) % 2;
    int i_it, j_it;
    
    // Capture UL diagonal
    if ( playable_direction[i][j][0] )
    {
        i_it = i-1, j_it = j-1;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
         
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            

            i_it -= 1;
            j_it -= 1;
        }
    }

    // Capture UP path
    if ( playable_direction[i][j][1] )
    {
        i_it = i-1, j_it = j;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            i_it -= 1;
        }
    }
    
    // Capture UR diagonal
    if ( playable_direction[i][j][2] )
    {
        i_it = i-1, j_it = j+1;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            i_it -= 1;
            j_it += 1;
        }
    }

    // Capture LEFT path
    if ( playable_direction[i][j][3] )
    {
        i_it = i, j_it = j-1;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            j_it -= 1;
        }
    }

    // Capture RIGHT path
    if ( playable_direction[i][j][4] )
    {
        i_it = i, j_it = j+1;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            j_it += 1;
        }
    }

    // Capture DL diagonal
    if ( playable_direction[i][j][5] )
    {
        i_it = i+1, j_it = j-1;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            i_it += 1;
            j_it -= 1;
        }
    }

    // Capture DOWN path
    if ( playable_direction[i][j][6] )
    {
        i_it = i+1, j_it = j;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            i_it += 1;
        }
    }

    // Capture DR diagonal
    if ( playable_direction[i][j][7] )
    {
        i_it = i+1, j_it = j+1;
        while ( Pobierz(i_it,j_it) == opposing_player )
        {
            Wstaw(i_it,j_it,*player);printf("wstawiono\n");
            if(*player==BLACK)  
            {
              *score1++;
              *score2--;
            }
            else
            {
              *score2++;
              *score1--;
            }
            i_it += 1;
            j_it += 1;
        }
    }
}


void draw_board( )
{
    printf( "     %c     %c     %c     %c     %c     %c     %c     %c\n", col_names[0], col_names[1], col_names[2], col_names[3], col_names[4], col_names[5], col_names[6], col_names[7] );
    printf( "   _____ _____ _____ _____ _____ _____ _____ _____\n" );
    for ( int i=0; i<8; ++i )
    {
        printf( "  |     |     |     |     |     |     |     |     |\n" );
        printf( "%c |", row_names[i] );
        for ( int j=0; j<8; ++j )
        {
            if ( Pobierz(i,j) == WHITE )
            {
                printf( "%s", "  0  " );
            } else if ( Pobierz(i,j)  == BLACK )
            {
                printf( "%s", "  1  " );
            } else if ( Pobierz(i,j)  == PLAYABLE )
            {
                printf( "%s", " .   " );
            } else
            {
                printf( "%s", "     " );
            }
            printf("|");
        }
        printf( "\n" );
        printf( "  |_____|_____|_____|_____|_____|_____|_____|_____|\n" );
    }
    printf( "\n" );
}



void Gra()
{
  int x=-1,y=-1;
  arcs = malloc(sizeof *arcs * (99 + 1));
  



  while(1) 
  {
    XNextEvent(display, &event);
     //draw_board( );

      WyswietlPunkty();
      display_current_player();
       if(Koniec())
        WyswietlKoniec();
      WyswietlKola();
      
      XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
      usleep(5000);

    if(event.type==Expose) 
    {
      WyswietlPunkty();
      usleep(5000);
      display_current_player();
      RysujPlansze();
      
      if(Koniec())
        WyswietlKoniec();
      
      WyswietlKola();
      
      XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
      usleep(5000);

        
    }
    display_current_player();

  
    
    if(ktory==*player)
    {
      
      if(event.type==ButtonPress)
      {
        x = event.xbutton.x;
        y = event.xbutton.y;

        if(x<100)
            x=0;
          if(x>100 && x<200)
            x=1;
          if(x>200 && x<300)
            x=2;
          if(x>300 && x<400)
            x=3;
          if(x>400 && x<500)
            x=4;
          if(x>500 && x<600)
            x=5;
          if(x>600 && x<700)
            x=6;
          if(x>700 && x<800)
            x=7;

          if(y<100)
            y=0;
          if(y>100 && y<200)
            y=1;
          if(y>200 && y<300)
            y=2;
          if(y>300 && y<400)
            y=3;
          if(y>400 && y<500)
            y=4;
          if(y>500 && y<600)
            y=5;
          if(y>600 && y<700)
            y=6;
          if(y>700 && y<800)
            y=7; 


          
          if(x>7 || y>7)
          {
            x=-1;
            y=-1;
          }




          if(x!=-1 && y!=-1) 
          {
            
          if(!wrong_move)mark_playable_positions();
          
          
          if(!has_valid_move)
          {
            if(skipped_turn)
            {
              game_ended=1;
              continue;
            }
              skipped_turn=1;
              continue;
          }
          skipped_turn=0;
          

            if ( Pobierz(x,y) == PLAYABLE )
            {
              
              Wstaw(x,y,*player);
              //printf("po przejscciach %d %d, tablica %d\n",y,x, Pobierz(x,y));
              if(*player==BLACK)
                *score1++;
              else
                *score2++;



              display_current_player();
              capture_pieces( x, y );
              usleep(5000);
              change_current_player();
              
              wrong_move=0;
              
            }
            else wrong_move = 1;
            
          }

                      
      }
    }
    

    WyswietlPunkty();
    printf("GRA %d\n",*player);
    
    if(Koniec())
      WyswietlKoniec();
      
    WyswietlKola();
      
    XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
    usleep(5000);

    display_current_player();
    

    if(event.type==KeyPress)
    {
      break;
    }


    if(event.type==ClientMessage)
    {
      break;
    }
  }

}



int main() 
{
  AlokujPamiec();
  
  Polaczenie();
  UtowrzenieOkna();
  Gra();                       
  ZamknijPolaczenie();
  CzyszczeniePamieci();

  return 0;
}