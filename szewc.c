#include<X11/Xlib.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h> 
#include <stdbool.h>
#include <errno.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#define PLAYER1 0
#define PLAYER2 1
#define PLAYABLE 2
#define SHARED_KEY_1 9123
#define SHARED_KEY_2 9124


Display *display;
int s;
Window window;
XEvent event;
char *str="SZEWC";
int *zajetePola;
int *plansza;
int *dane;
int gracz=0;
int *score1;
int *score2;
int *player;
int id_szewc;
int ktory;
int amount_arcs;
XArc *arcs;
int miejsce;
char str1[12]="000";
char str2[12]="000";





int  AlokujPamiec()
{
    id_szewc=shmget(SHARED_KEY_1,sizeof(int)*63,0666 | IPC_CREAT | IPC_EXCL);
    
    if(id_szewc==-1)
    {

        if(errno==EEXIST)
        {
            id_szewc=shmget(SHARED_KEY_1,sizeof(int)*63,0);
            int *adres = shmat(id_szewc,NULL,0);
            dane=adres;
            zajetePola=adres;
            plansza=adres+9;
            player=adres+60;
            score1=adres+61;
            score2=adres+62;
            
            ktory=1;
            return 1;

        }
        else
        {
            return -1;
        }
    }

    int *adres = shmat(id_szewc,NULL,0);
    dane=adres;
    zajetePola=adres;
    plansza=adres+9;
    player=adres+60;
    score1=adres+61;
    score2=adres+62;


    for(int i=0;i<59;i++)
        *(zajetePola+i)=PLAYABLE;


    *player=0;
    *score1=0;
    *score2=0;
    ktory=0;

    return 1;

}


int CzyszczeniePamieci()
{
    shmdt(dane); 
    shmctl(id_szewc,IPC_RMID,0);
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


void UstawWartosciKropoek()
{
    amount_arcs=0;
    arcs[amount_arcs].x=100;
    arcs[amount_arcs].y=100;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=175;
    arcs[amount_arcs].y=100;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=250;
    arcs[amount_arcs].y=100;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=325;
    arcs[amount_arcs].y=100;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;


    arcs[amount_arcs].x=100;
    arcs[amount_arcs].y=175;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;



    arcs[amount_arcs].x=175;
    arcs[amount_arcs].y=175;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=250;
    arcs[amount_arcs].y=175;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=325;
    arcs[amount_arcs].y=175;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;


    arcs[amount_arcs].x=100;
    arcs[amount_arcs].y=250;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=175;
    arcs[amount_arcs].y=250;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;


    arcs[amount_arcs].x=250;
    arcs[amount_arcs].y=250;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;


    arcs[amount_arcs].x=325;
    arcs[amount_arcs].y=250;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=100;
    arcs[amount_arcs].y=325;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=175;
    arcs[amount_arcs].y=325;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;

    arcs[amount_arcs].x=250;
    arcs[amount_arcs].y=325;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;



    arcs[amount_arcs].x=325;
    arcs[amount_arcs].y=325;
    arcs[amount_arcs].width=20;
    arcs[amount_arcs].height=20;
    arcs[amount_arcs].angle1=360*64;
    arcs[amount_arcs++].angle2=360*64;


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
   window=XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 650, 500, 1,
                         BlackPixel(display, s), WhitePixel(display, s));

   // Process Window Close Event through event handler so XNextEvent does Not fail
   Atom delWindow = XInternAtom( display, "WM_DELETE_WINDOW", 0 );
   XSetWMProtocols(display , window, &delWindow, 1);

    /* select kind of events we are interested in */
   XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);

    /* map (show) the window */
   XMapWindow(display, window);

}

void RysujKropki()
{
    //tytul
    XDrawString(display, window, DefaultGC(display, s), 500, 50, str, strlen(str));

    XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
    usleep(5000);

    UstawWartosciKropoek();
    XFillArcs(display, window, DefaultGC(display, s),arcs,amount_arcs);
    XDrawArcs(display, window, DefaultGC(display, s), arcs, amount_arcs);
    
}




void RysujLinie()
{
    //poziome
    if(*(plansza+1)==0 || *(plansza+1)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 108 , 108, 75,5 );
    if(*(plansza+3)==0 || *(plansza+3)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 183 , 108, 75,5 );
    if(*(plansza+5)==0 || *(plansza+5)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 258 , 108, 75,5 );

    if(*(plansza+15)==0 || *(plansza+15)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 108 , 183, 75,5 );
    if(*(plansza+17)==0 || *(plansza+17)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 183 , 183, 75,5 );
    if(*(plansza+19)==0 || *(plansza+19)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 258 , 183, 75,5 );
    
    if(*(plansza+29)==0 || *(plansza+29)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 108 , 258, 75,5 );
    if(*(plansza+31)==0 || *(plansza+31)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 183 , 258, 75,5 );
    if(*(plansza+33)==0 || *(plansza+33)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 258 , 258, 75,5 );
    
    if(*(plansza+43)==0 || *(plansza+43)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 108 , 333, 75,5 );
    if(*(plansza+45)==0 || *(plansza+45)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 183 , 333, 75,5 );
    if(*(plansza+47)==0 || *(plansza+47)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 258 , 333, 75,5 );
    
 
    //pionowe
    if(*(plansza+7)==0 || *(plansza+7)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 108 , 108, 5,75 );
    if(*(plansza+9)==0 || *(plansza+9)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 183 , 108, 5,75 );
    if(*(plansza+11)==0 || *(plansza+11)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 258 , 108, 5,75 );
    if(*(plansza+13)==0 || *(plansza+13)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 333 , 108, 5,75 );
    

    if(*(plansza+21)==0 || *(plansza+21)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 108 , 183, 5,75 );
    if(*(plansza+23)==0 || *(plansza+23)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 183 , 183, 5,75 );
    if(*(plansza+25)==0 || *(plansza+25)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 258 , 183, 5,75 );
    if(*(plansza+27)==0 || *(plansza+27)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 333 , 183, 5,75 );
    
    if(*(plansza+35)==0 || *(plansza+35)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 108 , 258, 5,75 );
    if(*(plansza+37)==0 || *(plansza+37)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 183 , 258, 5,75 );
    if(*(plansza+39)==0 || *(plansza+39)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 258 , 258, 5,75 );
    if(*(plansza+41)==0 || *(plansza+41)==1 )
    XDrawRectangle(display, window, DefaultGC(display, s), 333 , 258, 5,75 );


}


void WyswietlAktualnegoGracza()
{
    if ( *player == PLAYER1 )
    {
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("white"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 490, 150, "PLAYER 2", 8);
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 490, 150, "PLAYER 1", 8);
    }    
    else
    {

        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("white"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 490, 150, "PLAYER 1", 8);
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 490, 150, "PLAYER 2", 8);
          
    }
}





void WyswietlKoniec()
{
    XDrawString(display, window, DefaultGC(display, s), 500, 350, "KONIEC", 6);

    if(*score1>*score2)
        XDrawString(display, window, DefaultGC(display, s), 475, 365, "WYGRAL PLAYER1", 14);
    else
        if(*score1<*score2)
            XDrawString(display, window, DefaultGC(display, s), 475, 365, "WYGRAL PLAYER2", 14);
        else
            XDrawString(display, window, DefaultGC(display, s), 500, 365, "REMIS", 5);
        
    
}


void ZmienGracza()
{
    if(*player==PLAYER1)
        *player=PLAYER2;
    else
        *player=PLAYER1;

}


bool Dodaj(int x,int y)
{
    //poziomo
    if(x>105 && x<170 && y>100 && y<120 )
    {
        if(*(plansza+1)==PLAYABLE)
        {
            *(plansza+1)=*player;
            miejsce=1;
            return true;
        }
    }
    else
    if(x>175 && x<245 && y>100 && y<120 )
    {
        if(*(plansza+3)==PLAYABLE)
        {
            *(plansza+3)=*player;
            miejsce=3;
            return true;
        }
    }
    else
    if(x>245 && x<320 && y>100 && y<120 )
    {
        if(*(plansza+5)==PLAYABLE)
        {
            *(plansza+5)=*player;
            miejsce=5;
            return true;
        }
    }///////////////////////////////////////
    else
    if(x>105 && x<170 && y>175 && y<195 )
    {
        if(*(plansza+15)==PLAYABLE)
        {
            *(plansza+15)=*player;
            miejsce=15;
            return true;
        }
    }
    else
    if(x>175 && x<245 && y>175 && y<195 )
    {
        if(*(plansza+17)==PLAYABLE)
        {
            *(plansza+17)=*player;
            miejsce=17;
            return true;
        }
    }
    else
    if(x>245 && x<320 && y>175 && y<195 )
    {
        if(*(plansza+19)==PLAYABLE)
        {
            *(plansza+19)=*player;
            miejsce=19;
            return true;
        }
    }
    else///////////////////////////////////////
    if(x>105 && x<170 && y>250 && y<270 )
    {
        if(*(plansza+29)==PLAYABLE)
        {
            *(plansza+29)=*player;
            miejsce=29;
            return true;
        }
    }
    else
    if(x>175 && x<245 && y>250 && y<270 )
    {
        if(*(plansza+31)==PLAYABLE)
        {
            *(plansza+31)=*player;
            miejsce=31;
            return true;
        }
    }
    else
    if(x>245 && x<320 && y>250 && y<270 )
    {
        if(*(plansza+33)==PLAYABLE)
        {
            *(plansza+33)=*player;
            miejsce=33;
            return true;
        }
    }
    else/////////////////////////////////////
    if(x>105 && x<170 && y>325 && y<345 )
    {
        if(*(plansza+43)==PLAYABLE)
        {
            *(plansza+43)=*player;
            miejsce=43;
            return true;
        }
    }
    else
    if(x>175 && x<245 && y>325 && y<345 )
    {
        if(*(plansza+45)==PLAYABLE)
        {
            *(plansza+45)=*player;
            miejsce=45;
            return true;
        }
    }
    else
    if(x>245 && x<320 && y>325 && y<345 )
    {
        if(*(plansza+47)==PLAYABLE)
        {
            *(plansza+47)=*player;
            miejsce=47;
            return true;
        }
    }
    //pionowio
    else
    if(x>105 && x<125 && y>100 && y<175 )
    {
        if(*(plansza+7)==PLAYABLE)
        {
            *(plansza+7)=*player;
            miejsce=7;
            return true;
        }
    }
    else
    if(x>175 && x<195 && y>100 && y<175 )
    {
        if(*(plansza+9)==PLAYABLE)
        {
            *(plansza+9)=*player;
            miejsce=9;
            return true;
        }
    }
    else
    if(x>250 && x<270 && y>100 && y<175 )
    {
        if(*(plansza+11)==PLAYABLE)
        {
            *(plansza+11)=*player;
            miejsce=11;
            return true;
        }
    }
    else
    if(x>325 && x<345 && y>100 && y<175 )
    {
        if(*(plansza+13)==PLAYABLE)
        {
            *(plansza+13)=*player;
            miejsce=13;
            return true;
        }
    }
    else///////////////////////////
    if(x>105 && x<125 && y>175 && y<250 )
    {
        if(*(plansza+21)==PLAYABLE)
        {
            *(plansza+21)=*player;
            miejsce=21;
            return true;
        }
    }
    else
    if(x>175 && x<195 && y>175 && y<250 )
    {
        if(*(plansza+23)==PLAYABLE)
        {
            *(plansza+23)=*player;
            miejsce=21;
            return true;
        }
    }
    else
    if(x>250 && x<270 && y>175 && y<250 )
    {
        if(*(plansza+25)==PLAYABLE)
        {
            *(plansza+25)=*player;
            miejsce=25;
            return true;
        }
    }
    else
    if(x>325 && x<345 && y>175 && y<250 )
    {
        if(*(plansza+27)==PLAYABLE)
        {
            *(plansza+27)=*player;
            miejsce=27;
            return true;
        }
    }
    else///////////////////////////
    if(x>105 && x<125 && y>250 && y<325 )
    {
        if(*(plansza+35)==PLAYABLE)
        {
            *(plansza+35)=*player;
            miejsce=35;
            return true;
        }
    }
    else
    if(x>175 && x<195 && y>250 && y<325 )
    {
        if(*(plansza+37)==PLAYABLE)
        {
            *(plansza+37)=*player;
            miejsce=37;
            return true;
        }
    }
    else
    if(x>250 && x<270 && y>250 && y<325 )
    {
        if(*(plansza+39)==PLAYABLE)
        {
            *(plansza+39)=*player;
            miejsce=39;
            return true;
        }
    }
    else
    if(x>325 && x<345 && y>250 && y<325 )
    {
        if(*(plansza+41)==PLAYABLE)
        {
            *(plansza+41)=*player;
            miejsce=41;
            return true;
        }
    }

    return false;
}


bool DodajPunkt()
{
    int dodano=0;
    
    if(miejsce==1)
    {
        if(*(plansza+7)!=PLAYABLE && *(plansza+15)!=PLAYABLE && *(plansza+9)!=PLAYABLE)
        {
            if(*zajetePola==PLAYABLE)
            {
                *zajetePola=*player;
                dodano=1;
            }        
        }
    }
    if(miejsce==7)
    {
        if(*(plansza+1)!=PLAYABLE && *(plansza+9)!=PLAYABLE && *(plansza+15)!=PLAYABLE)
        {
            if(*(zajetePola)==PLAYABLE)
            {
                *(zajetePola)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==9)
    {
        if(*(plansza+1)!=PLAYABLE && *(plansza+7)!=PLAYABLE && *(plansza+15)!=PLAYABLE)
        {
            if(*(zajetePola)==PLAYABLE)
            {
                *(zajetePola)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+3)!=PLAYABLE && *(plansza+11)!=PLAYABLE && *(plansza+17)!=PLAYABLE)
        {
            if(*(zajetePola+1)==PLAYABLE)
            {
                *(zajetePola+1)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==15)
    {
        if(*(plansza+1)!=PLAYABLE && *(plansza+7)!=PLAYABLE && *(plansza+9)!=PLAYABLE)
        {
            if(*(zajetePola)==PLAYABLE)
            {
                *(zajetePola)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+21)!=PLAYABLE && *(plansza+23)!=PLAYABLE && *(plansza+29)!=PLAYABLE)
        {
            if(*(zajetePola+3)==PLAYABLE)
            {
                *(zajetePola+3)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==3)
    {
        if(*(plansza+9)!=PLAYABLE && *(plansza+11)!=PLAYABLE && *(plansza+17)!=PLAYABLE)
        {
            if(*(zajetePola+1)==PLAYABLE)
            {
                *(zajetePola+1)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==11)
    {
        if(*(plansza+9)!=PLAYABLE && *(plansza+3)!=PLAYABLE && *(plansza+17)!=PLAYABLE)
        {
            if(*(zajetePola+1)==PLAYABLE)
            {
                *(zajetePola+1)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+5)!=PLAYABLE && *(plansza+13)!=PLAYABLE && *(plansza+19)!=PLAYABLE)
        {
            if(*(zajetePola+2)==PLAYABLE)
            {
                *(zajetePola+2)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==17)
    {
        if(*(plansza+9)!=PLAYABLE && *(plansza+11)!=PLAYABLE && *(plansza+3)!=PLAYABLE)
        {
            if(*(zajetePola+1)==PLAYABLE)
            {
                *(zajetePola+1)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+23)!=PLAYABLE && *(plansza+25)!=PLAYABLE && *(plansza+31)!=PLAYABLE)
        {
            if(*(zajetePola+4)==PLAYABLE)
            {
                *(zajetePola+4)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==5)
    {
        if(*(plansza+11)!=PLAYABLE && *(plansza+13)!=PLAYABLE && *(plansza+19)!=PLAYABLE)
        {
            if(*(zajetePola+2)==PLAYABLE)
            {
                *(zajetePola+2)=*player;
                dodano=1;
            }        
        }
        
    }
    else
    if(miejsce==13)
    {
        if(*(plansza+5)!=PLAYABLE && *(plansza+11)!=PLAYABLE && *(plansza+19)!=PLAYABLE)
        {
            if(*(zajetePola+2)==PLAYABLE)
            {
                *(zajetePola+2)=*player;
                dodano=1;
            }        
        }
        
    }
    else
    if(miejsce==19)
    {
        if(*(plansza+5)!=PLAYABLE && *(plansza+11)!=PLAYABLE && *(plansza+13)!=PLAYABLE)
        {
            if(*(zajetePola+2)==PLAYABLE)
            {
                *(zajetePola+2)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+25)!=PLAYABLE && *(plansza+27)!=PLAYABLE && *(plansza+33)!=PLAYABLE)
        {
            if(*(zajetePola+5)==PLAYABLE)
            {
                *(zajetePola+5)=*player;
                dodano=1;
            }        
        }        
    }
    else
    if(miejsce==21)
    {
        if(*(plansza+15)!=PLAYABLE && *(plansza+23)!=PLAYABLE && *(plansza+29)!=PLAYABLE)
        {
            if(*(zajetePola+3)==PLAYABLE)
            {
                *(zajetePola+3)=*player;
                dodano=1;
            }        
        }
                
    }
    else
    if(miejsce==23)
    {
        if(*(plansza+15)!=PLAYABLE && *(plansza+21)!=PLAYABLE && *(plansza+29)!=PLAYABLE)
        {
            if(*(zajetePola+3)==PLAYABLE)
            {
                *(zajetePola+3)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+17)!=PLAYABLE && *(plansza+25)!=PLAYABLE && *(plansza+31)!=PLAYABLE)
        {
            if(*(zajetePola+4)==PLAYABLE)
            {
                *(zajetePola+4)=*player;
                dodano=1;
            }        
        }        
    }
    else
    if(miejsce==25)
    {
        if(*(plansza+19)!=PLAYABLE && *(plansza+27)!=PLAYABLE && *(plansza+33)!=PLAYABLE)
        {
            if(*(zajetePola+5)==PLAYABLE)
            {
                *(zajetePola+5)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+17)!=PLAYABLE && *(plansza+23)!=PLAYABLE && *(plansza+31)!=PLAYABLE)
        {
            if(*(zajetePola+4)==PLAYABLE)
            {
                *(zajetePola+4)=*player;
                dodano=1;
            }        
        }        
    }
    else
    if(miejsce==27)
    {
        if(*(plansza+19)!=PLAYABLE && *(plansza+25)!=PLAYABLE && *(plansza+33)!=PLAYABLE)
        {
            if(*(zajetePola+5)==PLAYABLE)
            {
                *(zajetePola+5)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==29)
    {
        if(*(plansza+21)!=PLAYABLE && *(plansza+15)!=PLAYABLE && *(plansza+23)!=PLAYABLE)
        {
            if(*(zajetePola+3)==PLAYABLE)
            {
                *(zajetePola+3)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+35)!=PLAYABLE && *(plansza+43)!=PLAYABLE && *(plansza+37)!=PLAYABLE)
        {
            if(*(zajetePola+6)==PLAYABLE)
            {
                *(zajetePola+6)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==31)
    {
        if(*(plansza+37)!=PLAYABLE && *(plansza+39)!=PLAYABLE && *(plansza+45)!=PLAYABLE)
        {
            if(*(zajetePola+7)==PLAYABLE)
            {
                *(zajetePola+7)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+23)!=PLAYABLE && *(plansza+17)!=PLAYABLE && *(plansza+25)!=PLAYABLE)
        {
            if(*(zajetePola+4)==PLAYABLE)
            {
                *(zajetePola+4)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==33)
    {
        if(*(plansza+25)!=PLAYABLE && *(plansza+19)!=PLAYABLE && *(plansza+27)!=PLAYABLE)
        {
            if(*(zajetePola+5)==PLAYABLE)
            {
                *(zajetePola+5)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+39)!=PLAYABLE && *(plansza+41)!=PLAYABLE && *(plansza+47)!=PLAYABLE)
        {
            if(*(zajetePola+8)==PLAYABLE)
            {
                *(zajetePola+8)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==35)
    {
        if(*(plansza+29)!=PLAYABLE && *(plansza+37)!=PLAYABLE && *(plansza+43)!=PLAYABLE)
        {
            if(*(zajetePola+6)==PLAYABLE)
            {
                *(zajetePola+6)=*player;
                dodano=1;
            }        
        }
        
    }
    else
    if(miejsce==37)
    {
        if(*(plansza+29)!=PLAYABLE && *(plansza+35)!=PLAYABLE && *(plansza+43)!=PLAYABLE)
        {
            if(*(zajetePola+6)==PLAYABLE)
            {
                *(zajetePola+6)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+31)!=PLAYABLE && *(plansza+39)!=PLAYABLE && *(plansza+45)!=PLAYABLE)
        {
            if(*(zajetePola+7)==PLAYABLE)
            {
                *(zajetePola+7)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==39)
    {
        if(*(plansza+33)!=PLAYABLE && *(plansza+41)!=PLAYABLE && *(plansza+47)!=PLAYABLE)
        {
            if(*(zajetePola+8)==PLAYABLE)
            {
                *(zajetePola+8)=*player;
                dodano=1;
            }        
        }
        if(*(plansza+31)!=PLAYABLE && *(plansza+37)!=PLAYABLE && *(plansza+45)!=PLAYABLE)
        {
            if(*(zajetePola+7)==PLAYABLE)
            {
                *(zajetePola+7)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==41)
    {
        if(*(plansza+33)!=PLAYABLE && *(plansza+39)!=PLAYABLE && *(plansza+47)!=PLAYABLE)
        {
            if(*(zajetePola+8)==PLAYABLE)
            {
                *(zajetePola+8)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==43)
    {
        if(*(plansza+35)!=PLAYABLE && *(plansza+29)!=PLAYABLE && *(plansza+37)!=PLAYABLE)
        {
            if(*(zajetePola+6)==PLAYABLE)
            {
                *(zajetePola+6)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==45)
    {
        if(*(plansza+37)!=PLAYABLE && *(plansza+31)!=PLAYABLE && *(plansza+39)!=PLAYABLE)
        {
            if(*(zajetePola+7)==PLAYABLE)
            {
                *(zajetePola+7)=*player;
                dodano=1;
            }        
        }
    }
    else
    if(miejsce==47)
    {
        if(*(plansza+33)!=PLAYABLE && *(plansza+39)!=PLAYABLE && *(plansza+41)!=PLAYABLE)
        {
            if(*(zajetePola+8)==PLAYABLE)
            {
                *(zajetePola+8)=*player;
                dodano=1;
            }        
        }
    }




    if(dodano == 0)
    return false;
    else
    return true;

    

}


bool Koniec()
{
    int status=0;
    for(int i=0;i<9;i++)
    {
        if(*(zajetePola+i)!=0 && *(zajetePola+i)!=1 )
        {
            status=1;
            break;
        }
    }


    if(status==0)
    return true;
    else
    return false;
}

void ZliczPunkty()
{
    
    int a=0;
    int b=0;
    for(int i=0;i<9;i++)
    {
        if(*(zajetePola+i)==PLAYER1)
            a++;
        if(*(zajetePola+i)==PLAYER2)
            b++;

    }
    
    *score1=a;
    *score2=b;

}



void WyswietlPunkty()
{
  ZliczPunkty();
 
  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
  usleep(5000);
  XDrawString(display, window, DefaultGC(display, s), 470, 100, "PLAYER1", 7);
  XDrawString(display, window, DefaultGC(display, s), 520, 100, "PLAYER2", 7);




  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("white"));
  usleep(5000);
  XDrawString(display, window, DefaultGC(display, s), 485, 120, str1, strlen(str1));
  XDrawString(display, window, DefaultGC(display, s), 535, 120, str2, strlen(str2));

    
  XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
  usleep(500);
 // printf("weszlo %d\n",*score1);
  sprintf(str1, "%d", *score1);
  
  XDrawString(display, window, DefaultGC(display, s), 485, 120, str1, strlen(str1));

  sprintf(str2, "%d", *score2);
  XDrawString(display, window, DefaultGC(display, s), 535, 120, str2,strlen(str2));
}

void WyswietlZnaczkiNaPlanszy()
{
    if(*(zajetePola)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 125 , 125, 165,165 );
        XDrawLine(display, window, DefaultGC(display, s), 165 , 125, 125,165 );
    }
    if(*(zajetePola)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 125, 125, 45, 45, 0, 360*64);
        
    }

    if(*(zajetePola+1)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 200 , 125, 240,165 );
        XDrawLine(display, window, DefaultGC(display, s), 240 , 125, 200,165 );
    }
    if(*(zajetePola+1)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 200, 125, 45, 45, 0, 360*64);
        
    }
    if(*(zajetePola+2)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 275 , 125, 315,165 );
        XDrawLine(display, window, DefaultGC(display, s), 315 , 125, 275,165 );
    }
    if(*(zajetePola+2)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 275, 125, 45, 45, 0, 360*64);
        
    }



    if(*(zajetePola+3)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 125 , 200, 165,240 );
        XDrawLine(display, window, DefaultGC(display, s), 165 , 200, 125,240 );
    }
    if(*(zajetePola+3)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 125, 200, 45, 45, 0, 360*64);
        
    }

    if(*(zajetePola+4)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 200 , 200, 240,240 );
        XDrawLine(display, window, DefaultGC(display, s), 240 , 200, 200,240 );
    }
    if(*(zajetePola+4)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 200, 200, 45, 45, 0, 360*64);
        
    }
    if(*(zajetePola+5)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 275 , 200, 315,240 );
        XDrawLine(display, window, DefaultGC(display, s), 315 , 200, 275,240 );
    }
    if(*(zajetePola+5)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 275, 200, 45, 45, 0, 360*64);
        
    }

    
    
    if(*(zajetePola+6)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 125 , 275, 165,315 );
        XDrawLine(display, window, DefaultGC(display, s), 165 , 275, 125,315 );
    }
    if(*(zajetePola+6)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 125, 275, 45, 45, 0, 360*64);
        
    }

    if(*(zajetePola+7)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 200 , 275, 240,315 );
        XDrawLine(display, window, DefaultGC(display, s), 240 , 275, 200,315 );
    }
    if(*(zajetePola+7)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 200, 275, 45, 45, 0, 360*64);
        
    }
    if(*(zajetePola+8)==PLAYER1)
    {
        XDrawLine(display, window, DefaultGC(display, s), 275 , 275, 315,315 );
        XDrawLine(display, window, DefaultGC(display, s), 315 , 275, 275,315 );
    }
    if(*(zajetePola+8)==PLAYER2)
    {

        XDrawArc(display, window, DefaultGC(display, s), 275, 275, 45, 45, 0, 360*64);
        
    }


}



void Gra()
{
    int x=-1,y=-1;
    arcs = malloc(sizeof *arcs * (99 + 1));


    while(1) 
    {
     XNextEvent(display, &event);
     /* draw or redraw the window */
        if(event.type==Expose) 
        {
            RysujKropki();
            RysujLinie();
            WyswietlAktualnegoGracza();
            WyswietlPunkty();
            
            if(Koniec())
                WyswietlKoniec();
        }

        if(ktory==*player)
        {
            if(event.type==ButtonPress)
            {
                x = event.xbutton.x;
                y = event.xbutton.y;
                printf("click at %d %d\n",x,y);
                if(Dodaj(x,y))
                {
                    if(!DodajPunkt())
                    {
                        WyswietlPunkty();
                        WyswietlZnaczkiNaPlanszy();
                        ZmienGracza();
                    }
                    WyswietlPunkty();
                    WyswietlZnaczkiNaPlanszy();
                    
                }

                RysujLinie();
                WyswietlAktualnegoGracza();
                WyswietlZnaczkiNaPlanszy();
                WyswietlPunkty();
                if(Koniec())
                    WyswietlKoniec();

            }
        }

                
        RysujLinie();
        WyswietlAktualnegoGracza();
            if(Koniec())
                WyswietlKoniec();
        WyswietlPunkty();
        WyswietlZnaczkiNaPlanszy();

        /* exit on key press */
        if(event.type==KeyPress)
            {
                CzyszczeniePamieci();
                break;
            }

        // Handle Windows Close Event
        if(event.type==ClientMessage)
            {
                CzyszczeniePamieci();
                break;
            }
   }

}



void ZamknijPolaczenie()
{
   /* destroy our window */
   XDestroyWindow(display, window);

    /* close connection to server */
   XCloseDisplay(display);

}


int main() 
{
    AlokujPamiec();
    Polaczenie();
    UtowrzenieOkna();
    Gra();                       
    ZamknijPolaczenie();


   return 0;
}