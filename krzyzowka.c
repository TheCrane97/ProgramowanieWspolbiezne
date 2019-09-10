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
#define SHARED_KEY_1 9123
#define SHARED_KEY_2 9124


Display *display;
int s;
Window window;
XEvent event;
char *str="KRZYZOWKA";
char *pytanie1="1.Funkcja zawierajaca wartosc bezwzgledna liczby calkowitej.";
char *pytanie2="2.Zmienna calkowita.";
char *pytanie3="3.Funkcja Liczaca arcsinus.";
char *pytanie4="4.Nazwa glownej funkcji programu w jezyku C.";
char *pytanie5="5.Funkcja sluzaca do wpisywania pojedynczych znakow.";
char *A="A";
char *B="B";
char *C="C";
char *H="H";
char *I="I";
char *M="M";
char *N="N";
char *P="P";
char *R="R";
char *S="S";
char *T="T";
char *U="U";
char odp[5][10]={{"ABS"},{"INT"},{"ASIN"},{"MAIN"},{"PUTCHAR"}};
int *krzyzowka;
int gracz=0;
int *score1;
int *score2;
int *player;
int id_krzyzowki;
int ktory;

typedef struct {
	short x, y;
	unsigned short width, height;
} Rectangle;

Rectangle rectangles[21];



int  AlokujPamiec()
{
    id_krzyzowki=shmget(SHARED_KEY_1,sizeof(int)*9,0666 | IPC_CREAT | IPC_EXCL);
    printf("ID KRZYZOWKI: %d\n", id_krzyzowki);
    if(id_krzyzowki==-1)
    {

        if(errno==EEXIST)
        {
            id_krzyzowki=shmget(SHARED_KEY_1,sizeof(int)*9,0);
            int *adres = shmat(id_krzyzowki,NULL,0);
            printf("ADRES P2: %d\n", adres);
            krzyzowka=adres;
            printf("KRZYZOWKA P2: %d\n", krzyzowka);
            player=krzyzowka+6;
            score1=krzyzowka+7;
            score2=krzyzowka+8;
            printf("PLAYER adres nieadres: %d  %d\n", player, *player);
            ktory=1;
            return 1;

        }
        else
        {
            return -1;
        }
    }

    int *adres = shmat(id_krzyzowki,NULL,0);
    printf("ADRES P1: %d\n", adres);
    krzyzowka=adres;
    printf("KRZYZOWKA P1: %d\n", krzyzowka);
    player=krzyzowka+6;
    score1=krzyzowka+7;
    score2=krzyzowka+8;
    
    
    printf("PLAYER co sie rowna krzyzowka: %d  %d\n", player, *player);
    *player=0;
    *score1=0;
    *score2=0;
    printf("PLAYER adres nieadres: %d  %d\n", player, *player);

    ktory=0;

    for(int i=0;i<5;i++)
    {
       // printf("krzyzowka: %d\n",(*krzyzowka+i));
        *(krzyzowka+i)=0;
            
    }



    return 1;

}


int CzyszczeniePamieci()
{
    shmdt(krzyzowka); 
    shmctl(id_krzyzowki,IPC_RMID,0);
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


void UstawWartosciKwadratow()
{
    //zolte
    rectangles[0].x=250;
    rectangles[0].y=100;
    rectangles[0].width=40;
    rectangles[0].height=40;

    rectangles[1].x=290;
    rectangles[1].y=100;
    rectangles[1].width=40;
    rectangles[1].height=40;

    rectangles[2].x=330;
    rectangles[2].y=100;
    rectangles[2].width=40;
    rectangles[2].height=40;

    rectangles[3].x=210;
    rectangles[3].y=140;
    rectangles[3].width=40;
    rectangles[3].height=40;

    //zolte
    rectangles[4].x=250;
    rectangles[4].y=140;
    rectangles[4].width=40;
    rectangles[4].height=40;

    rectangles[5].x=290;
    rectangles[5].y=140;
    rectangles[5].width=40;
    rectangles[5].height=40;

    rectangles[6].x=210;
    rectangles[6].y=180;
    rectangles[6].width=40;
    rectangles[6].height=40;

    //zolte
    rectangles[7].x=250;
    rectangles[7].y=180;
    rectangles[7].width=40;
    rectangles[7].height=40;

    rectangles[8].x=290;
    rectangles[8].y=180;
    rectangles[8].width=40;
    rectangles[8].height=40;

    rectangles[9].x=330;
    rectangles[9].y=180;
    rectangles[9].width=40;
    rectangles[9].height=40;

    rectangles[10].x=170;
    rectangles[10].y=220;
    rectangles[10].width=40;
    rectangles[10].height=40;

    rectangles[11].x=210;
    rectangles[11].y=220;
    rectangles[11].width=40;
    rectangles[11].height=40;

    //zolte
    rectangles[12].x=250;
    rectangles[12].y=220;
    rectangles[12].width=40;
    rectangles[12].height=40;

    rectangles[13].x=290;
    rectangles[13].y=220;
    rectangles[13].width=40;
    rectangles[13].height=40;

    rectangles[14].x=130;
    rectangles[14].y=260;
    rectangles[14].width=40;
    rectangles[14].height=40;

    rectangles[15].x=170;
    rectangles[15].y=260;
    rectangles[15].width=40;
    rectangles[15].height=40;

    rectangles[16].x=210;
    rectangles[16].y=260;
    rectangles[16].width=40;
    rectangles[16].height=40;

    //zolte
    rectangles[17].x=250;
    rectangles[17].y=260;
    rectangles[17].width=40;
    rectangles[17].height=40;

    rectangles[18].x=290;
    rectangles[18].y=260;
    rectangles[18].width=40;
    rectangles[18].height=40;

    rectangles[19].x=330;
    rectangles[19].y=260;
    rectangles[19].width=40;
    rectangles[19].height=40;

    rectangles[20].x=370;
    rectangles[20].y=260;
    rectangles[20].width=40;
    rectangles[20].height=40;

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
   window=XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 1000, 500, 1,
                         BlackPixel(display, s), WhitePixel(display, s));

   // Process Window Close Event through event handler so XNextEvent does Not fail
   Atom delWindow = XInternAtom( display, "WM_DELETE_WINDOW", 0 );
   XSetWMProtocols(display , window, &delWindow, 1);

    /* select kind of events we are interested in */
   XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);

    /* map (show) the window */
   XMapWindow(display, window);

}

void Krzyzowka()
{
    //tytul
    XDrawString(display, window, DefaultGC(display, s), 460, 50, str, strlen(str));
    //pytania
    XDrawString(display, window, DefaultGC(display, s), 550, 100, pytanie1, strlen(pytanie1));
    XDrawString(display, window, DefaultGC(display, s), 550, 150, pytanie2, strlen(pytanie2));
    XDrawString(display, window, DefaultGC(display, s), 550, 200, pytanie3, strlen(pytanie3));
    XDrawString(display, window, DefaultGC(display, s), 550, 250, pytanie4, strlen(pytanie4));
    XDrawString(display, window, DefaultGC(display, s), 550, 300, pytanie5, strlen(pytanie5));
    //krzyzowka
    UstawWartosciKwadratow();
    XDrawRectangles(display, window, DefaultGC(display, s), rectangles, 21);
    //zolte wypelnienia
    XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("yellow"));
    usleep(5000);
    XFillRectangle(display, window, DefaultGC(display, s), 251, 101, 38, 38);
    XFillRectangle(display, window, DefaultGC(display, s), 251, 141, 38, 38);
    XFillRectangle(display, window, DefaultGC(display, s), 251, 181, 38, 38);
    XFillRectangle(display, window, DefaultGC(display, s), 251, 221, 38, 38);
    XFillRectangle(display, window, DefaultGC(display, s), 251, 261, 38, 38);
    XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
    usleep(5000);
    //cyfry w przed slowami w krzyzowce
    XDrawString(display, window, DefaultGC(display, s), 225, 120, "1", 1);
    XDrawString(display, window, DefaultGC(display, s), 185, 165, "2", 1);
    XDrawString(display, window, DefaultGC(display, s), 185, 205, "3", 1);
    XDrawString(display, window, DefaultGC(display, s), 145, 245, "4", 1);
    XDrawString(display, window, DefaultGC(display, s), 105, 285, "5", 1);
    //pryzciski i litery
    //przycisk NIE WIEM
    XDrawRectangle(display, window, DefaultGC(display, s), 800 , 330, 70,20 );
    XDrawString(display, window, DefaultGC(display, s), 812, 345, "NIE WIEM", 8);
    //przycisk ENTER
    XDrawRectangle(display, window, DefaultGC(display, s), 800 , 360, 70,20 );
    XDrawString(display, window, DefaultGC(display, s), 820, 375, "ENTER", 5);
    //troche alfabetu
    XDrawRectangle(display, window, DefaultGC(display, s), 760 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 740 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 720 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 700 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 680 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 660 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 640 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 620 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 600 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 580 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 560 , 360, 20,20 );
    XDrawRectangle(display, window, DefaultGC(display, s), 540 , 360, 20,20 );
    XDrawString(display, window, DefaultGC(display, s), 767, 375, U, 1);
    XDrawString(display, window, DefaultGC(display, s), 747, 375, T, 1);
    XDrawString(display, window, DefaultGC(display, s), 727, 375, S, 1);
    XDrawString(display, window, DefaultGC(display, s), 707, 375, R, 1);
    XDrawString(display, window, DefaultGC(display, s), 687, 375, P, 1);
    XDrawString(display, window, DefaultGC(display, s), 667, 375, N, 1);
    XDrawString(display, window, DefaultGC(display, s), 647, 375, M, 1);
    XDrawString(display, window, DefaultGC(display, s), 627, 375, I, 1);
    XDrawString(display, window, DefaultGC(display, s), 607, 375, H, 1);
    XDrawString(display, window, DefaultGC(display, s), 587, 375, C, 1);
    XDrawString(display, window, DefaultGC(display, s), 567, 375, B, 1);
    XDrawString(display, window, DefaultGC(display, s), 547, 375, A, 1);
}

bool PrawidloweKlikniecie(int x,int y)
{

    if(x>540 && x <780 && y>360 && y<380)
        return true;
    if(x>820 && x <890 && y>360 && y<380)
        return true;
    if(x>800 && x <870 && y>330 && y<350)
        return true;

    return false;    
}

char KtoraLitera(int x,int y)
{
    if(x>760 && x <780)
        return 'U';
    if(x>740)
        return 'T';
    if(x>720)
        return 'S';
    if(x>700)
        return 'R';
    if(x>680)
        return 'P';
    if(x>660)
        return 'N';
    if(x>640)
        return 'M';
    if(x>620)
        return 'I';
    if(x>600)
        return 'H';
    if(x>580)
        return 'C';
    if(x>560)
        return 'B';
    if(x>540)
        return 'A';


}



void WyswietlKoniec()
{
    XDrawString(display, window, DefaultGC(display, s), 200, 350, "KONIEC", 6);
    XDrawString(display, window, DefaultGC(display, s), 200, 365, "WYGRAL", 6);

    if(*score1>*score2)
        XDrawString(display, window, DefaultGC(display, s), 200, 380, "PLAYER1", 7);
    else
        XDrawString(display, window, DefaultGC(display, s), 200, 380, "PLAYER2", 7);
    
}


void ZmienGracza()
{
    if(*player==PLAYER1)
        *player=PLAYER2;
    else
        *player=PLAYER1;

}



void Rysuj1()
{
    XDrawString(display, window, DefaultGC(display, s), 267, 128, "A", 1);
    XDrawString(display, window, DefaultGC(display, s), 307, 128, "B", 1);
    XDrawString(display, window, DefaultGC(display, s), 347, 128, "S", 1);
}
void Rysuj2()
{
    XDrawString(display, window, DefaultGC(display, s), 227, 168, "I", 1);
    XDrawString(display, window, DefaultGC(display, s), 267, 168, "N", 1);
    XDrawString(display, window, DefaultGC(display, s), 307, 168, "T", 1);
}
void Rysuj3()
{
    XDrawString(display, window, DefaultGC(display, s), 227, 208, "A", 1);
    XDrawString(display, window, DefaultGC(display, s), 267, 208, "S", 1);
    XDrawString(display, window, DefaultGC(display, s), 307, 208, "I", 1);
    XDrawString(display, window, DefaultGC(display, s), 347, 208, "N", 1);
}
void Rysuj4()
{
    XDrawString(display, window, DefaultGC(display, s), 187, 248, "M", 1);
    XDrawString(display, window, DefaultGC(display, s), 227, 248, "A", 1);
    XDrawString(display, window, DefaultGC(display, s), 267, 248, "I", 1);
    XDrawString(display, window, DefaultGC(display, s), 307, 248, "N", 1);
   
}
void Rysuj5()
{
    XDrawString(display, window, DefaultGC(display, s), 147, 288, "P", 1);
    XDrawString(display, window, DefaultGC(display, s), 187, 288, "U", 1);
    XDrawString(display, window, DefaultGC(display, s), 227, 288, "T", 1);
    XDrawString(display, window, DefaultGC(display, s), 267, 288, "C", 1);
    XDrawString(display, window, DefaultGC(display, s), 307, 288, "H", 1);
    XDrawString(display, window, DefaultGC(display, s), 347, 288, "A", 1);
    XDrawString(display, window, DefaultGC(display, s), 387, 288, "R", 1);
}



void RysujSlowo(int k)
{
    if(k==0)
        Rysuj1();
    if(k==1)
        Rysuj2();
    if(k==2)
        Rysuj3();
    if(k==3)
        Rysuj4();
    if(k==4)
        Rysuj5();
}



void WyswietlAktualnegoGracza()
{
    if ( *player == PLAYER1 )
    {
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("white"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 650, 400, "PLAYER 2", 8);
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 650, 400, "PLAYER 1", 8);
    }    
    else
    {

        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("white"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 650, 400, "PLAYER 1", 8);
        XSetForeground(display, DefaultGC(display, s), BlackPixel(display, 0)^Kolor("black"));
        usleep(5000);
        XDrawString(display, window, DefaultGC(display, s), 650, 400, "PLAYER 2", 8);
          
    }
}

void SlowaWKrzyzowce()
{

    for(int i=0;i<5;i++)
    {
        
        if(*(krzyzowka+i)==1)
            RysujSlowo(i);
    }

}


bool Koniec()
{
    if(*(krzyzowka)==1 && *(krzyzowka+1)==1 && *(krzyzowka+2)==1 && *(krzyzowka+3)==1 && *(krzyzowka+4)==1)
        return true;
    else
        return false;
}



void Gra()
{
    int x=-1,y=-1;
    int licznik=0;
    char slowo[500];
    int status=0;
    for(int i=0;i<5;i++)
    {
        *(krzyzowka+i)=0;
    }
    

    while(1) 
    {
     XNextEvent(display, &event);
     /* draw or redraw the window */
        if(event.type==Expose) 
        {
            Krzyzowka();
            WyswietlAktualnegoGracza();
            SlowaWKrzyzowce();
            if(Koniec())
                WyswietlKoniec();
        }

        if(event.type==ButtonPress)
        {
            x = event.xbutton.x;
            y = event.xbutton.y;
            printf("click at: %d %d\n",x,y);

            if(*player==ktory)
            {
                if(PrawidloweKlikniecie(x,y))
                {
                    if(x>540 && x <780 && y>360 && y<380)
                    {
                    slowo[licznik]=KtoraLitera(x,y);
                    licznik++;
                    printf("%s\n",slowo);
                    }

                    if(x>820 && x <890 && y>360 && y<380)
                    {
                        licznik=0;
                        for(int k=0;k<5;k++)
                        {
                            status=0;
                            for(int p=0;p<strlen(odp[k]);p++)
                            {
                                if(odp[k][p]!=slowo[p])
                                    status=1;

                                
                            }
                            if(status==0)
                            { 
                                if(*(krzyzowka+k)==0)
                                {
                                        //RysujSlowo(k);
                                        usleep(5000);
                                        *(krzyzowka+k)=1;
                                        break;
                                }
                            }
                        }
                        //printf("%s\n",slowo);
                        printf("%d\n",status);
                        if(status==0)
                        {
                            printf("weszlo\n");
                            if(*player==0)
                                *score1+=1;
                            else
                                *score2+=1;

                            
                            ZmienGracza();
                        }
                        else
                        {
                            status=1;
                            ZmienGracza();
                        }


                        printf("P1: %d  P2: %d\n",*score1,*score2);
                            
                    }


                    if(x>800 && x <870 && y>330 && y<350)
                    {
                        ZmienGracza();
                    }

                    usleep(5000);
                    WyswietlAktualnegoGracza();
                    

                }
            }

        }



        usleep(5000);
        WyswietlAktualnegoGracza();
        usleep(5000);
        SlowaWKrzyzowce();
        usleep(5000);
        if(Koniec())
            WyswietlKoniec();
                


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
void dupa()
{
    // 1 2 3 4 5 6 7 8
    // 1 2 3 4 5 6 7 8
    // 1 2 3 4 5 6 7 8
    // 1 2 3 4 5 6 7 8
    // 1 2 3 4 5 6 7 8
    // 1 2 3 4 5 6 7 8

    int r = 8, c = 8; 
    int *arr = (int *)malloc(r * c * sizeof(int)); 

    int i, j; 

    for (i = 0; i <  r; i++) 
      for (j = 0; j < c; j++) 
         *(arr + i*c + j) = 0; 
}


