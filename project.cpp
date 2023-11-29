#include <iostream>
#include<stdio.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include<termios.h>


int logiTime; // check logical time
bool visited[10][10]; 
int map[10][10];
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
int move(int speed); //defines the movement of an object
void locationSet(drunkMan * man,sniper * sni,wife * w,home * h); // Set object location
void randomWall();
void setQuad();
void verifyWall(int x,int y);
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
        randomWall();
        locationSet(NULL,NULL,NULL,NULL);
        move(speed);

    }

int move(int speed)
    {

        int r=rand()%4;

        logiTime++;
        return 0;
    }
void randomWall()
{
    

}
void locationSet(drunkMan * man,sniper * sni,wife * w,home * h)
{

}