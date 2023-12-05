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
int map[10][10]; //map
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
    int around[8][2];
    int cnt;
    int accuracy;

}sniper;
typedef struct wife
{
    int quad;
    int around[8][2];
    int location[2];
    int cnt;
}wife;
typedef struct home
{
    int quad;
    int location[2];

}home;

void tmpmain(); //tmp main
void move(int speed,drunkMan * man,sniper * sni,wife * w,home * h); //defines the movement of an object
void locationSet(drunkMan * man,sniper * sni,wife * w,home * h); // Set object location
int where(int x,int y);
void printMap(sniper * sni);
void randomGo(int *rx,int * ry);
void second(drunkMan* man,sniper* sni);
void thirdRandom(int secondQuad,drunkMan* man);
int Xquad(int quad);
int Yquad(int quad);
void four(drunkMan *man,wife *w,sniper *sni);
void mapSet();
int cntWall(int secondQuad);
int main()
    {
        tmpmain();
        
        while(1){};
        return 0;
    }
void tmpmain() // 가 메인 함수
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
        w.cnt=0;
        sniper sni;
        home h;
        sni.cnt=0;
        sni.accuracy=0;
        mapSet();
        locationSet(&man,&sni,&w,&h);
        move(speed,&man,&sni,&w,&h);
    }

void move(int speed,drunkMan * man,sniper * sni,wife * w,home * h) // 이동함수
    {
        int rx,ry,ox,oy,secondQuad=rand()%4+1,homeCnt=0;
        while(secondQuad==man->quad||secondQuad==sni->quad||secondQuad==w->quad)
            {
                secondQuad=rand()%4+1;
            }
        
        map[w->location[0]][w->location[1]]=0;
        while(man->status==1)
            {
                printMap(sni);
                logiTime++;
                if(man->quad==w->quad)
                    {
                        if(w->cnt<5)
                            {
                               w->cnt++;                        
                            }
                    }
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
                while((rx<0||rx>9||ry<0||ry>9)|| map[rx][ry]==1 || man->visitedQuad[where(rx,ry)-1]==1
                ||map[rx][ry]==lsni||map[rx][ry]==lwife)
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
                        thirdRandom(secondQuad,man);
                    }
                if(man->quad==sni->quad)
                    {
                        sni->cnt++;
                    }
                if(sni->cnt>=10 && man->quad==sni->quad)
                    {
                        second(man,sni);
                    }
                if(w->cnt==5)
                {
                    four(man,w,sni);
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

       
        while(man->status== -2)
        {
            printMap(sni);
            homeCnt++;
            logiTime++;
            ox=man->location[0];
            oy=man->location[1];
            map[ox][oy]=0;
            randomGo(&rx,&ry);
            rx=ox+rx;
            ry=oy+ry;
            while((rx<0||rx>9||ry<0||ry>9)||map[rx][ry]==1||man->visitedQuad[where(rx,ry)-1]==1)
                {
                    randomGo(&rx,&ry);
                    rx=ox+rx;
                    ry=oy+ry;
                }
            map[rx][ry]=lman;
            man->location[0]=rx;
            man->location[1]=ry;
            if(man->location[0]==h->location[0]&&man->location[1]==h->location[1])
                {
                    man->status=0;
                    printf("\n 붙잡혀 집에 도착했습니다\n %d번만에 \n",homeCnt);
                    sleep(10);
                    return;
                }  
            sleep(5/speed);
            system("clear");
            
        }
        return;
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


void locationSet(drunkMan * man,sniper * sni,wife * w,home * h) // 위치 설정 함수
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
    //home section
    for(int i=0;i<4;++i)
        {
            if(man->quad==i+1)
            {
                wStore=4-i;
                h->quad=wStore;
            }
        }
    rx=Xquad(h->quad);
    ry=Yquad(h->quad);
    while(map[rx][ry]==1 ||where(rx,ry)!=h->quad )
        {
            rx=Xquad(h->quad);
            ry=Yquad(h->quad);
        }
    map[rx][ry]=lhome;
    h->location[0]=rx;
    h->location[1]=ry;
    // wife section
    for(int i=1;i<=4;++i)
        {
            wStore=i;
            if(man->quad!=wStore && h->quad==wStore)
                {
                    w->quad=wStore;
                }
        }
    rx=Xquad(w->quad);
    ry=Yquad(w->quad);
    while(map[rx][ry]==1||where(rx,ry)!=w->quad || (rx==h->location[0]&& ry==h->location[1]))
        {
            rx=Xquad(w->quad);
            ry=Yquad(w->quad);
        }
    map[rx][ry]=lwife;
    w->location[0]=rx;
    w->location[1]=ry;
    //sniper section
    for(int i=1;i<=4;++i)
        {
            wStore=i;
            if(man->quad!=wStore && h->quad!=wStore && w->quad!=wStore)
                {
                    sni->quad=wStore;
                }
        }
    rx=Xquad(sni->quad);
    ry=Yquad(sni->quad);
    while(map[rx][ry]==0 || where(rx,ry)!=sni->quad)
        {
            rx=Xquad(sni->quad);
            ry=Yquad(sni->quad);
        }
    map[rx][ry]=lsni;
    sni->location[0]=rx;
    sni->location[1]=ry;
}

void printMap(sniper * sni) //맵 출력 함수
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
                    if(map[i][j]== lman)
                        {
                            printf("M");
                        }
                    if(map[i][j]== lhome)
                        {
                            printf("H");
                        }
                    if(map[i][j]== lwife)
                        {
                            printf("W");
                        }
                    if(map[i][j]== lsni)
                        {
                            if(sni->accuracy==0)
                                {
                                    printf("S");
                                }
                            else
                            {
                                for(int i=1;i<=10;++i)
                                    {
                                        if(sni->accuracy==i&&sni->accuracy!=10)
                                            {
                                                printf("%d",i*10);
                                            }
                                    }
                                if(sni->accuracy==10)
                                    {
                                        printf("0");
                                    }
                            }
                        }

                }
            printf("\n");
        }
    printf("\n<< logi Time : %d>>\n",logiTime);
}
void randomGo(int * rx,int * ry ) // 랜덤 이동 함수
    {

        int d=rand()%4+1;
        if(d==1)
        {
            *rx= 0;
            *ry= -1;
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
                *rx= -1;
                *ry=0;
                return;
            }
        if(d==4)
            {
                *rx=0;
                *ry= 1;
                return;
            }

        
    }
void thirdRandom(int secondQuad,drunkMan* man) //thrid quad function
{
    int rx,ry;
    static int oTime=logiTime;
    rx=Xquad(secondQuad);
    ry=Yquad(secondQuad);
    if(logiTime-oTime ==5)
        {
            while((where(rx,ry)!=secondQuad || map[rx][ry]!=1 || (rx== man->location[0] && ry == man->location[1])
             )&& cntWall(secondQuad)!=0 )
                {
                    rx=Xquad(secondQuad);
                    ry=Yquad(secondQuad);
                }
            oTime=logiTime;
            sleep(1/2);
            map[rx][ry]=0;
        }
}
int Xquad(int quad) // x 만들기 함수
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
int Yquad(int quad) // y 만들기 함수
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
void second(drunkMan * man,sniper* sni) //second sniper function
    {
        int rx[8]={1,-1,0,0,-1,-1,1,1},ry[8]={0,0,1,-1,1,-1,1,-1},s1,s2,rate;
        bool inflag=0;
        rate=rand()%10+1;
        if(sni->accuracy<10)
            {
                sni->accuracy++;
            }
        if(sni->cnt==10)
        {
            for(int i=0;i<8;++i)
                {
                    s1=sni->location[0];
                    s2=sni->location[1];
                    if(i<4)
                        {
                            sni->around[i][0]=s1+rx[i];
                            sni->around[i][1]=s2+ry[i];
                            if(where(sni->around[i][0],sni->around[i][1])!=sni->quad)
                                {
                                    sni->around[i][0]= -1;
                                    sni->around[i][1]= -1;
                                }
                        }
                    else
                    {
                        sni->around[i][0]=s1+rx[i];
                        sni->around[i][1]=s2+ry[i];
                        if(where(sni->around[i][0],sni->around[i][1])!=sni->quad)
                                {
                                    sni->around[i][0]= -1;
                                    sni->around[i][1]= -1;
                                }
                    }
                }
        }
        for(int i=0;i<8;++i) 
            {
                if(man->location[0]==sni->around[i][0] && man->location[1]==sni->around[i][1])
                    {
                        inflag=1;
                    }
            }
        if(inflag==1)
        {
            if(rate<=sni->accuracy||sni->accuracy==10)
                {
                    man->status= -1;
                    system("clear");
                    printMap(sni);
                    printf("\n 사망했습니다 !\n");
                    sleep(10);
                }
            else
            {
                system("clear");
                printMap(sni);
                rate=rand()%10+1;
                printf("\n 못맞췄습니다!\n");
            }


        }
    }
void mapSet() // 기본 맵 세팅
{
    int wall[10][10]={ {0,1,4}, {6,7,8}, {1,3,4}, {6,9}, {1,2,4}, {0}, {1,2,4,6,8}, {8},{1,2,3,4,6,8}};
    for(int i=0;i<10;++i)
        {
            for(int j=0;j<10;++j)
                {
                    if(wall[i][j]!=0)
                        {
                            map[i][wall[i][j]]=1;
                        }
                }
        }
    map[0][0]=1;
}
void four(drunkMan *man,wife* w,sniper* sni) //4 사분면 함수
{
    int ox,oy,rx,ry,kx[8]={1,-1,0,0,-1,-1,1,1},ky[8]={0,0,1,-1,1,-1,1,-1},inflag=0;
    ox=w->location[0];
    oy=w->location[1];
    map[ox][oy]=0;
    for(int i=0;i<8;++i)
        {
            if(i<4)
                {
                    w->around[i][0]=ox+kx[i];
                    w->around[i][1]=oy+ky[i];
                }
            else
                {
                    w->around[i][0]=ox+kx[i];
                    w->around[i][1]=oy+ky[i];
                }
            
        }
    for(int i=0;i<8;++i) 
        {
            if(man->location[0]==w->around[i][0] && man->location[1]==w->around[i][1])
                {
                    inflag=1;
                }
        }
    if(inflag==1)
        {
            man->status= -2;
            printf("\n붙잡혔습니다 !\n");
            printf("\n집으로 돌아갑니다...\n");
            sleep(3);
        }
    else
    {
        randomGo(&rx,&ry);
        rx=ox+rx;
        ry=oy+ry;
        while((rx<0||rx>9||ry<0||ry>9)||map[rx][ry]==1||map[rx][ry]==lhome||map[rx][ry]==lman||man->visitedQuad[where(rx,ry)-1]==1)
            {
                randomGo(&rx,&ry);
                rx=ox+rx;
                ry=oy+ry;
            }
        map[rx][ry]=lwife;
        w->location[0]=rx;
        w->location[1]=ry;
    }
    for(int i=0;i<8;++i)
    {
        if(i<4)
            {
                w->around[i][0]=ox+kx[i];
                w->around[i][1]=oy+ky[i];
            }
        else
            {
                w->around[i][0]=ox+kx[i];
                w->around[i][1]=oy+ky[i];
            }
        
    }
}
int cntWall(int secondQuad) //벽 세기 함수
{
    int rx,ry,cnt=0;
    rx=Xquad(secondQuad);
    ry=Yquad(secondQuad);
    while(where(rx,ry)!=secondQuad)
        {
            rx=Xquad(secondQuad);
            ry=Yquad(secondQuad);
        }
    if(where(rx,ry)==1)
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
    if(where(rx,ry)==2)
        {
            for(int i=0;i<5;++i)
                {
                    for(int j=0;j<5;++j)
                        {
                            if(map[i][9-j]==1)
                                {
                                    cnt++;
                                }
                        }
                }
        }
    if(where(rx,ry)==3)
        {
           for(int i=0;i<5;++i)
                {
                    for(int j=0;j<5;++j)
                        {
                            if(map[9-i][j]==1)
                                {
                                    cnt++;
                                }
                        }
                } 
        }
    if(where(rx,ry)==3)
            {
            for(int i=0;i<5;++i)
                    {
                        for(int j=0;j<5;++j)
                            {
                                if(map[9-i][9-j]==1)
                                    {
                                        cnt++;
                                    }
                            }
                    } 
            }
    return cnt;
}