/*
Powered by wmydx
Snake verson 1.0
2013.10.19
遗留问题：当蛇尾有多个邻接星号时，如何涂抹。 
*/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define ROW 40
#define COL 20
struct SnakeTail
{
       int x;
       int y;
};
struct SnakeHead
{
       int x;
       int y;
       int dis;
};
struct Food
{
       int x;
       int y;
};
SnakeTail myTail;
SnakeHead myHead;
Food myFood;
char map[COL][ROW];
int gameSpeed = 100;
int winPoint = 0;
int isDead = 0;
int isPoint = 0;
//以下是网上找来的GOTOXY实现 
void GoToXY(int x, int y)
{
 COORD pos = {x,y};
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
 
 SetConsoleCursorPosition(hOut, pos);
}

void WhereXY(int *x, int *y)
{
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
 CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo( hOut, &bInfo ); 
 COORD pos = bInfo.dwCursorPosition;
 *x = pos.X;
 *y = pos.Y;
}
//以上时网上找来的GOTOXY实现 
void plantFood()
{
     int tmpx,tmpy;
     srand((int)time(0));
     tmpx = rand() % COL;
     tmpy = rand() % ROW;
     while(((tmpx <= 2 && tmpx >= COL - 2) || (tmpy <= 2 && tmpy >= ROW - 2)) || map[tmpx][tmpy] == '*')
     {
             tmpx = rand() % COL;
             tmpy = rand() % ROW;
     }
     myFood.x = tmpx;
     myFood.y = tmpy;
     map[myFood.x][myFood.y] = '$';
}
void initialization() //初始化游戏 
{
     int col = 9;
     for(int i = 0;i < COL;i++)
             for(int j = 0;j < ROW;j++)
             {
                     map[i][j] = ' ';        
             }
     for(int i = 2;i <= 6;i++)
             map[col][i] = '*';
     myTail.x = 9;
     myTail.y = 2;
     myHead.x = 9;
     myHead.y = 6;
     myHead.dis = 4;
     plantFood();
}
void print()
{
     printf("                   ");
     for(int i = 0;i < ROW;i++)
             printf("-");
     printf("\n");
     for(int i = 0;i < COL;i++)
     {
             printf("                   ");
             for(int j = 0;j < ROW;j++)
             {
                     if(j == 0)printf("|");
                     printf("%c",map[i][j]);
             }
             printf("|\n");        
     }
     printf("                   ");
     for(int i = 0;i < ROW;i++)
             printf("-");
}
int ifDie(int x,int y)
{
    if(x < 0 || y < 0 || x >= COL || y >= ROW || map[x][y] == '*')return 1;
    else return 0;
}
int ifGetPoint()
{
    if(map[myHead.x][myHead.y] == '$')
    {
           plantFood();    
           return 1;
    }
    else return 0;
}
void snakeMove()
{
     switch(myHead.dis)
     {
                       case 1 : myHead.x --;
                                if(ifGetPoint())
                                {
                                   winPoint ++;
                                   isPoint = 1;
                                }
                                if(!ifDie(myHead.x,myHead.y))
                                   map[myHead.x][myHead.y] = '*';
                                else 
                                {
                                     isDead = 1;
                                }
                                break;
                       case 2 : myHead.x ++;
                                if(ifGetPoint())
                                {
                                   winPoint ++;
                                   isPoint = 1;
                                }                       
                                if(!ifDie(myHead.x,myHead.y))
                                   map[myHead.x][myHead.y] = '*';
                                else 
                                {
                                     isDead = 1;
                                }
                                break;  
                       case 3 : myHead.y --;
                                if(ifGetPoint())
                                {
                                   winPoint ++;
                                   isPoint = 1;
                                }                       
                                if(!ifDie(myHead.x,myHead.y))
                                   map[myHead.x][myHead.y] = '*';
                                else 
                                {
                                     isDead = 1;
                                }
                                break;   
                       case 4 : myHead.y ++;
                                if(ifGetPoint())
                                {
                                   winPoint ++;
                                   isPoint = 1;
                                }                       
                                if(!ifDie(myHead.x,myHead.y))
                                   map[myHead.x][myHead.y] = '*';
                                else 
                                {
                                     isDead = 1;
                                }
                                break;                                                                               
     }
     if(isPoint == 0)
     {
             if(map[myTail.x + 1][myTail.y] == '*')
             {
                             map[myTail.x][myTail.y] = ' ';
                             myTail.x ++;
             } 
             else if(map[myTail.x - 1][myTail.y] == '*')
             {
                             map[myTail.x][myTail.y] = ' ';
                             myTail.x --;
             }
             else if(map[myTail.x][myTail.y + 1] == '*')
             {
                             map[myTail.x][myTail.y] = ' ';
                             myTail.y ++;
             }   
             else if(map[myTail.x][myTail.y - 1] == '*')
             {
                             map[myTail.x][myTail.y] = ' ';
                             myTail.y --;
             }                                
     }
     else isPoint = 0;
}
void changeSnake(char ch)
{
     switch(ch)
     {
               case 'w' : myHead.dis = 1;
                          break;
               case 'a' : myHead.dis = 3;
                          break;
               case 's' : myHead.dis = 2;
                          break;
               case 'd' : myHead.dis = 4;
                          break;
               default : ;//printf("ERROR!"); BUG检测代码                   
     }
}
int main(void)
{
    char control;
    initialization();
    int end = 0;
    while(1)
    {
            while(kbhit() == 0)
            {
                    print();
                    snakeMove();
                    if(isDead == 1)
                    {
                              end = 1;
                              break;
                    }
                    Sleep(gameSpeed);
                    GoToXY(0,0);
            }
            if(end)break;
            control = getche();
            changeSnake(control);
            
    }
    printf("\n                               YOUR SCORE IS %d \n",winPoint);
    system("pause");
    return 0;
}
