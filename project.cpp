#include <iostream>
#include<stdio.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include<termios.h>
#define lman -1
#define lhome -2
#define lwife -3
#define lsni -4
int logiTime; // check logical time
bool visited[10][10]; 
int map[10][10]; //map
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int roadCnt; // count contiued walls
int Xquad(int quad);
int Yquad(int quad);
typedef struct drunkMan
{
    int quad;    // location of obj in quadrant
    bool visitedQuad[4];
    int status;
    int location[2];
    
}drunkMan;
typedef struct sniper
{
    int quad;
    int location[2];

}sniper;
typedef struct wife
{
    int quad;
    int around[10][10];
    int location[2];

}wife;
typedef struct home
{
    int quad;
    int location[2];

}home;

void tmpmain(); //tmp main
void move(int speed,drunkMan * man,sniper * sni,wife * w,home * h); //defines the movement of an object
void locationSet(drunkMan * man,sniper * sni,wife * w,home * h); // Set object location
void randomWall();
int where(int x,int y);
int cntWall(int quad);
void verifyWall(int x,int y); //Whether the walls are made up of five in a row
void printMap();
int rangeX(int quad);
int rangeY(int quad);
void randomGo(int *rx,int * ry);
void thirdRandom(int secondQuad);
int main()
    {
        tmpmain();
        
        while(1){};
        return 0;
    }
void tmpmain()
    {
        srand(time(NULL));
        int speed,l;
        printf("speed:");
        scanf("%d",&speed);
        drunkMan man;
        man.status=1;
        for(int i=0;i<4;++i)
            {
                man.visitedQuad[i]=0;
            }
        wife w;
        sniper sni;
        home h;
        randomWall();
        locationSet(&man,&sni,&w,&h);
        move(speed,&man,&sni,&w,&h);


    }

void move(int speed,drunkMan * man,sniper * sni,wife * w,home * h)
    {
        int rx,ry,ox,oy,secondQuad=rand()%4+1;
        while(secondQuad==man->quad||secondQuad==sni->quad||secondQuad==w->quad)
            {
                secondQuad=rand()%4+1;
            }
        
        while(man->status==1)
            {
                printMap();
                logiTime++;
                ox=man->location[0];
                oy=man->location[1];
                map[ox][oy]=0;
                rx=0;
                ry=0;
                if(man->visitedQuad[where(rx,ry)-1]!=1)
                {
                    randomGo(&rx,&ry);
                    rx=rx+ox;
                    ry=ry+oy;
                    man->quad=where(ox,oy);
                }
                while((rx<0||rx>9||ry<0||ry>9)|| map[rx][ry]==1 || man->visitedQuad[where(rx,ry)-1]==1)
                    {
                
                        randomGo(&rx,&ry);
                        rx=rx+ox;
                        ry=ry+oy;

                    }
                
                map[rx][ry]=lman;
                man->location[0]=rx;
                man->location[1]=ry;
                man->quad=where(rx,ry);
                if(where(rx,ry)!=where(ox,oy))
                    {
                        man->visitedQuad[where(ox,oy)-1]=1;
                    }
                if(man->quad==h->quad)
                    {
                        for(int i=0;i<4;++i)
                            {
                                if(h->quad!=i+1)
                                    {
                                        man->visitedQuad[i]=1;
                                    }
                            }
                    }
                if(man->quad==secondQuad)
                    {
                        thirdRandom(secondQuad);
                    }

                if(man->location[0]==h->location[0]&&man->location[1]==h->location[1])
                    {
                        man->status=0;
                        printf("\n무사히 집에 잘 도착했습니다\n");
                        return;
                    }  

                sleep(5/speed);
                system("clear");
            }
        
        
        
        return;
    }
void randomWall()
{
    int x,y,cntSum=0,wStore,rWall=0;

    while(cntSum<26) 
    {
        x=rand()%10;
        y=rand()%10;
        cntSum=0;
        
        wStore=where(x,y);
        if(cntWall(wStore)<9&& map[x][y]==0)
        {
            map[x][y]=1;
        }
        for(int i=1;i<5;++i)
            {
                cntSum+=cntWall(i);
            }
        roadCnt=0;
        for(int i=0;i<10;++i)
            {
                memset(visited[i],0,sizeof(int)*10);
            }
        verifyWall(x,y);
    }

}
int where(int x,int y) // To find out where it is in the fourth quadrant
    {
        int quad;
        if(x<5 && y<5)
            {
                quad=1;
            }
        if(x<5 && y>=5)
            {
                quad=2;
            }
        if(x>=5&& y<5)
            {
                quad=3;
            }
        if(x>=5&&y>=5)
            {
                quad=4;
            }
        return quad;
    }
int cntWall(int quad) //count the number of walls in the quadrant
{
    int cnt=0;
    if(quad==1)
    {
        for(int i=0;i<5;++i)
            {
                for(int j=0;j<5;++j)
                    {
                        if(map[i][j]==1)
                            {
                                cnt++;
                            }
                    }
            }
    }
    if(quad==2)
        {
            for(int i=0;i<5;++i)
                {
                    for(int j=5;j<10;++j)
                        {
                            if(map[i][j]==1)
                                {
                                    cnt++;
                                }
                        }
                }
        }
    if(quad==3)
        {
            for(int i=5;i<10;++i)
                {
                    for(int j=0;j<5;++j)
                        {
                            if(map[i][j]==1)
                                {
                                    cnt++;
                                }
                        }
                }
        }
    if(quad==4)
        {
            for(int i=5;i<10;++i)
                {
                    for(int j=5;j<10;++j)
                        {
                            if(map[i][j]==1)
                                {
                                    cnt++;
                                }
                        }
                }
        }
    return cnt;
}

void locationSet(drunkMan * man,sniper * sni,wife * w,home * h)
{
    int rx,ry,wStore;
    rx=rand()%10;
    ry=rand()%10;
    wStore=where(rx,ry);
    while(map[rx][ry]==1) //set man location
    {
        rx=rand()%10;
        ry=rand()%10;
        wStore=where(rx,ry);
    }
    map[rx][ry]=lman;
    man->location[0]=rx;
    man->location[1]=ry;
    man->quad=wStore;
    for(int i=0;i<4;++i)
        {
            if(man->quad==i+1)
            {
                wStore=4-i;
                h->quad=wStore;
            }
        }
    rx=rangeX(h->quad); //set h location
    ry=rangeY(h->quad);
    while(map[rx][ry]==1 )
        {
            rx=rangeX(h->quad);
            ry=rangeY(h->quad);
        }
    map[rx][ry]=lhome;
    h->location[0]=rx;
    h->location[1]=ry;
    for(int i=1;i<=4;++i)
        {
            wStore=i;
            if(man->quad!=wStore && h->quad==wStore)
                {
                    w->quad=wStore;
                }
        }
    rx=rangeX(w->quad); //set wife location
    ry=rangeY(w->quad);
    while(map[rx][ry]==1)
        {
            rx=rangeX(w->quad);
            ry=rangeY(w->quad);
        }
    map[rx][ry]=lwife;
    w->location[0]=rx;
    w->location[1]=ry;
    for(int i=1;i<=4;++i)
        {
            wStore=i;
            if(man->quad!=wStore && h->quad!=wStore && w->quad!=wStore)
                {
                    sni->quad=wStore;
                }
        }
    rx=rangeX(sni->quad);
    ry=rangeY(sni->quad);
    while(map[rx][ry]==0 )
        {
            rx=rangeX(sni->quad);
            ry=rangeY(sni->quad);
        }
    map[rx][ry]=lsni;
    sni->location[0]=rx;
    sni->location[1]=ry;
}
void verifyWall(int x,int y)
{
    visited[x][y]=1;
    int ax,by,i=0;
    while(i<4)
        {
            ax=x+dx[i];
            by=y+dy[i];
            if(ax>=10 || ax<0|| by>=10 || by<0) 
            {
                i++;
            }
            else if(visited[ax][by]==0 && map[ax][by]==1)
                {
                    roadCnt++;
                    verifyWall(ax,by);
                }
            else
            {
                i++;
            }
        }
    

}
void printMap()
{
    for(int i=0;i<10;++i)
        {
            for(int j=0;j<10;++j)
                {
                    if(map[i][j]==1)
                    {
                        printf("◼");
                    }
                    if(map[i][j]==0)
                    {
                        printf("□");
                    }
                    if(map[i][j]== -1)
                        {
                            printf("M");
                        }
                    if(map[i][j]== -2)
                        {
                            printf("H");
                        }
                    if(map[i][j]== -3)
                        {
                            printf("W");
                        }
                    if(map[i][j]== -4)
                        {
                            printf("0");
                        }

                }
            printf("\n");
        }
}
int rangeX(int quad)
    {
        int rx=rand()%10;
        if(quad==1 || quad==2)
            {
                while(rx>=5)
                    {
                        rx=rand()%10;
                    }
                return rx;
            }
        if(quad==3 || quad==4)
            {
                while(rx<5)
                    {
                        rx=rand()%10;
                    }
                return rx;
            }
        return 0;
    }
int rangeY(int quad)
    {
        int ry=rand()%10;
        if(quad==1||quad==3)
            {
                while(ry>=5)
                    {
                        ry=rand()%10;
                    }
                return  ry;
            }
        if(quad==2||quad==4)
            {
                while(ry<5)
                    {
                        ry=rand()%10;
                    }
                return ry;
            }
        return 0;
    }
void randomGo(int * rx,int * ry )
    {

        int d=rand()%4+1;
        if(d==1)
        {
            *rx= -1;
            *ry=0;
            return;
        }
        if(d==2)
            {
                *rx=1;
                *ry=0;
                return;
            }
        if(d==3)
            {
                *rx=0;
                *ry=1;
                return;
            }
        if(d==4)
            {
                *rx=0;
                *ry= -1;
                return;
            }

        
    }
void thirdRandom(int secondQuad)
{
    int rx,ry;
    static int oTime=logiTime;
    rx=Xquad(secondQuad);
    ry=Yquad(secondQuad);
    if(logiTime-oTime ==5)
        {
            while(where(rx,ry)!=secondQuad)
                {
                    rx=Xquad(secondQuad);
                    ry=Yquad(secondQuad);
                }
            oTime=logiTime;
            map[rx][ry]=0;
        }
}
int Xquad(int quad)
{
    int rx;
    rx=rand()%10;
    if(quad==1||quad ==2)
    {
        while(rx>=5)
            {
                rx=rand()%10;
            }
        return rx;
    }
    if(quad==3||quad==4)
        {
            while(rx<5)
                {
                    rx=rand()%10;
                }
            return rx;
        }
    return 1;
}
int Yquad(int quad)
{
    int ry=rand()%10;
    if(quad==1||quad==3)
        {
            while(ry>=5)
                {
                    ry=rand()%10;
                }
            return ry;
        }
    if(quad==2||quad==4)
        {
            while(ry<5)
                {
                    ry=rand()%10;
                }
            return ry;
        }
    return 1;
}