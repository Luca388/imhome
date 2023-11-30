#include <iostream>
#include<stdio.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include<termios.h>


int logiTime; // check logical time
bool visited[10][10]; 
int map[10][10]; //map
int road[10][10];
int roadCnt; // count contiued walls
typedef struct drunkMan
{
    int location[2];  //location of drunkMan
    int quad;    // location of obj in quadrant

    
}drunkMan;
typedef struct sniper
{
    int quad;
    int location[2];

}sniper;
typedef struct wife
{
    int quad;
    int location[2];

}wife;
typedef struct home
{
    int quad;
    int location[2];
}home;

void tmpmain(); //tmp main
int move(int speed,drunkMan * man,sniper * sni,wife * w,home * h); //defines the movement of an object
void locationSet(drunkMan * man,sniper * sni,wife * w,home * h); // Set object location
void randomWall();
int where(int x,int y);
int cntWall(int quad);
bool verifyWall(int x,int y); //Whether the walls are made up of five in a row
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
        wife w;
        sniper sni;
        home h;
        randomWall();
        locationSet(&man,&sni,&w,&h);
        move(speed,&man,&sni,&w,&h);

    }

int move(int speed,drunkMan * man,sniper * sni,wife * w,home * h)
    {

        int r=rand()%4;

        logiTime++;
        return 0;
    }
void randomWall()
{
    int cnt[4]={0},x,y,cntSum,wStore;

    while(cntSum<26)
    {
        x=rand()%10;
        y=rand()%10;
        wStore=where(x,y);
        if(cntWall(wStore)<9)
        {
            map[x][y]=1;
        }
        
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

}
bool verifyWall(int x,int y)
{

}