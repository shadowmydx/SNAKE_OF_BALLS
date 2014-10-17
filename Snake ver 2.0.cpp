/*
Powered by wmydx
Snake verson 2.0
2013.10.19
verson 1.0的遗留问题已经解决：标记蛇头的访问顺序，谁小跟谁
注意：用户摁键过快会产生BUG，已解决
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
struct Map
{
       char a;
       unsigned long long num;
};
struct Point
{
       int x;
       int y;
       int flag;
};
SnakeTail myTail;
SnakeHead myHead;
Food myFood;
unsigned long long count = 1;
Map map[COL][ROW];
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
     while(((tmpx <= 2 && tmpx >= COL - 2) || (tmpy <= 2 && tmpy >= ROW - 2)) || map[tmpx][tmpy].a == '*')
     {
             tmpx = rand() % COL;
             tmpy = rand() % ROW;
     }
     myFood.x = tmpx;
     myFood.y = tmpy;
     map[myFood.x][myFood.y].a = '$';
}
void initialization() //初始化游戏
{
     int col = 9;
     for(int i = 0;i < COL;i++)
             for(int j = 0;j < ROW;j++)
             {
                     map[i][j].a = ' ';
                     map[i][j].num = 0;
             }
     for(int i = 2;i <= 6;i++)
     {
             map[col][i].a = '*';
             map[col][i].num = count ++;
     }
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
                     printf("%c",map[i][j].a);
             }
             printf("|\n");
     }
     printf("                   ");
     for(int i = 0;i < ROW;i++)
             printf("-");
}
int ifDie(int x,int y)
{
    if(x < 0 || y < 0 || x >= COL || y >= ROW || map[x][y].a == '*')return 1;
    else return 0;
}
int ifGetPoint()
{
    if(map[myHead.x][myHead.y].a == '$')
    {
           plantFood();
           return 1;
    }
    else return 0;
}
void deleteTail()
{
     Point a[4];
     Point temp;
     int test = 0;
     unsigned long long min = 0xFFFFFFFF;
     for(int i = 0;i < 4;i++)
             a[i].flag = 0;
     if(map[myTail.x + 1][myTail.y].a == '*')
     {
                             a[0].flag = 1;
                             a[0].x = myTail.x + 1;
                             a[0].y = myTail.y;
     }
     if(map[myTail.x - 1][myTail.y].a == '*')
     {
                             a[1].flag = 1;
                             a[1].x = myTail.x - 1;
                             a[1].y = myTail.y;
     }
     if(map[myTail.x][myTail.y + 1].a == '*')
     {
                             a[2].flag = 1;
                             a[2].x = myTail.x;
                             a[2].y = myTail.y + 1;
     }
     if(map[myTail.x][myTail.y - 1].a == '*')
     {
                             a[3].flag = 1;
                             a[3].x = myTail.x;
                             a[3].y = myTail.y - 1;
     }
     for(int i = 0;i < 4;i++)
     {
             if(a[i].flag == 1)
             {
                     test ++;
                     if(map[a[i].x][a[i].y].num < min)
                     {
                        min = map[a[i].x][a[i].y].num;
                        temp = a[i];
                     }

             }
     }
     map[myTail.x][myTail.y].a = ' ';
     map[myTail.x][myTail.y].num = 0;
     myTail.x = temp.x;
     myTail.y = temp.y;
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
                                {
                                   map[myHead.x][myHead.y].a = '*';
                                   map[myHead.x][myHead.y].num = count ++;
                                }
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
                                {
                                   map[myHead.x][myHead.y].a = '*';
                                   map[myHead.x][myHead.y].num = count ++;
                                }
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
                                {
                                   map[myHead.x][myHead.y].a = '*';
                                   map[myHead.x][myHead.y].num = count ++;
                                }
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
                                {
                                   map[myHead.x][myHead.y].a = '*';
                                   map[myHead.x][myHead.y].num = count ++;
                                }
                                else
                                {
                                     isDead = 1;
                                }
                                break;
     }
     if(isPoint == 0)
     {
                deleteTail();
     }
     else isPoint = 0;
}
void changeSnake(char ch)
{
     if(ch == '.')return;
     switch(ch)
     {
               case 'w' : if(myHead.dis != 2)myHead.dis = 1;
                          break;
               case 'a' : if(myHead.dis != 4)myHead.dis = 3;
                          break;
               case 's' : if(myHead.dis != 1)myHead.dis = 2;
                          break;
               case 'd' : if(myHead.dis != 3)myHead.dis = 4;
                          break;
               default : ;//printf("ERROR!"); BUG检测代码
     }
}
int main(void)
{
    char control = '.';
    initialization();
    int end = 0;
    while(1)
    {
            while(kbhit() == 0)
            {
                    changeSnake(control); //这个函数要放入循环体！否则摁键过快，前次操作未进入循环体，后次操作又改变dis了
                    control = '.';
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
            control = getch();
    }
    printf("\n                               YOUR SCORE IS %d \n",winPoint);
    system("pause");
    return 0;
}
