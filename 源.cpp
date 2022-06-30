#include<stdio.h>
#include<stdlib.h>
#include <algorithm>
#include<graphics.h>
#include <conio.h>
#include <time.h>
using namespace std;
#define MAX_GRID 4 //每行格子数
#define GRID_WIDTH 100//格子宽度
#define INTERVAL 15 //间隔
#define WIDTH 5*INTERVAL+GRID_WIDTH*MAX_GRID //窗口宽度
enum Color //格子颜色
{
    two_0 = RGB(205, 193, 180),//2的0的颜色
    two_1 = RGB(238, 228, 218),//2的1次方的颜色
    two_2 = RGB(237, 224, 200),//2的2次方的颜色
    two_3 = RGB(242, 177, 121),//......
    two_4 = RGB(245, 149, 99),
    two_5 = RGB(246, 124, 95),
    two_6 = RGB(246, 94, 59),
    two_7 = RGB(242, 177, 121),
    two_8 = RGB(237, 204, 97),
    two_9 = RGB(255, 0, 128),
    two_10 = RGB(145, 0, 72),
    two_11 = RGB(242, 17, 158),
    back = RGB(187,173,160),//背景颜色
};
Color numcolor[13] = { two_0, two_1, two_2, two_3, two_4, two_5, two_6, two_7, two_8, two_9, two_10, two_11 };
int num[13] = { 0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
int map[MAX_GRID][MAX_GRID];
bool flag;

//随机生成2或4 概率为1：4
int create() 
{
    if (rand() % 10 < 2)
        return 4;
    else
        return 2;
}

//在随机位置设置初始值
void set() 
{
    while (1) {
        int x, y;
        x = rand() % MAX_GRID;
        y = rand() % MAX_GRID;
        if (map[x][y] == 0)
        {
            map[x][y] = create();
            break;
        }
    }
}

//初始化游戏
void StartGame() 
{
    srand(time(0));//更具时间设置随机数种子
    //游戏开始设置两个位置不为零的初始值
    set();
    set();
}

//找到对应数字的颜色位置
int Findindex(int x)
{
    int index = lower_bound( num, num + 12, x) - num;//STL 中的二分查找,找到比x数大的位置-1
    return index;
}

//游戏显示界面
void GameDraw() 
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        for (int j = 0; j < MAX_GRID; j++)
        {
            setfillcolor(numcolor[ Findindex( map[i][j] ) ]);//设置格子颜色
            solidrectangle((j + 1) * INTERVAL + j * GRID_WIDTH, (i + 1) * INTERVAL + i * GRID_WIDTH,
                (j + 1) * (INTERVAL + GRID_WIDTH), (i + 1) * (INTERVAL + GRID_WIDTH));//显示并设置格子位置大小
            
            if (map[i][j] != 0)
            {
                char number[5] = "";
                settextstyle(50, 0, "楷体");
                setbkmode(TRANSPARENT);
                sprintf(number, "%d", map[i][j]);
                int dx = GRID_WIDTH / 2 - textwidth(number)/2;
                int dy = GRID_WIDTH / 2 - textheight(number) / 2;
                outtextxy((j + 1) * INTERVAL + j * GRID_WIDTH + dx, (i + 1) * INTERVAL + i * GRID_WIDTH + dy, number);//显示格子内数字
            }
        }
    }
}

//上移
void upmove()
{
    for (int i = 0; i < 4; i++)
    {
        int index = 0;
        for (int j = 0; j < 4; j++)
            if (map[j][i])
            {
                map[index++][i] = map[j][i];
                if (index - 1 != j)
                {
                    map[j][i] = 0;
                    flag = true;
                }
                    
            }
    }
}

//向上合成
void up()
{
    upmove();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j <= 2; j++)
            if (map[j][i] && map[j][i] == map[j + 1][i])
                map[j][i] *= 2, map[j + 1][i] = 0;
    }
    upmove();
}

//下移
void downmove()
{
    for (int i = 0; i < 4; i++)
    {
        int index = 3;
        for (int j = 3; j >= 0; j--)
            if (map[j][i])
            {
                map[index--][i] = map[j][i];
                if (index + 1 != j)
                {
                    map[j][i] = 0;
                    flag = true;
                }
                    
            }
    }
}

//向下合成
void down()
{
    downmove();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
            if (map[j][i] && map[j][i] == map[j - 1][i])
                map[j][i] *= 2, map[j - 1][i] = 0;
    }
    downmove();
}

//左移
void leftmove()
{
    for (int i = 0; i < 4; i++)
    {
        int index = 0;
        for (int j = 0; j < 4; j++)
            if (map[i][j])
            {
                map[i][index++] = map[i][j];
                if (index - 1 != j)
                {
                    map[i][j] = 0;
                    flag = true;
                }
                    
            }
    }
}

//向左合成
void left()
{
    leftmove();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (map[i][j] && map[i][j] == map[i][j + 1])
                map[i][j] *= 2, map[i][j + 1] = 0;
    leftmove();
}

//右移
void rightmove()
{
    for (int i = 0; i < 4; i++)
    {
        int index = 3;
        for (int j = 3; j >= 0; j--)
            if (map[i][j])
            {
                map[i][index--] = map[i][j];
                if (index + 1 != j)
                {
                    map[i][j] = 0;
                    flag = true;
                }
                    
            }
    }
}

//向右合成
void right()
{
    rightmove();
    for (int i = 0; i < 4; i++)
        for (int j = 3; j > 0; j--)
            if (map[i][j] && map[i][j] == map[i][j - 1])
                map[i][j] *= 2, map[i][j - 1] = 0;
    rightmove();
}

//游戏控制
void GameContolr()
{
    flag = false;
    char key = _getch();
    switch(key)
    {
    case 'w':
    case 'W':
    case 72: up(); break;
    case 's':
    case 'S':
    case 80: down(); break;
    case 'a':
    case 'A':
    case 75: left(); break;
    case 'd':
    case 'D':
    case 77: right(); break;
    }
    if (flag)
        set(); 
}

int main()
{
    //创建窗口
    initgraph(WIDTH, WIDTH);;
    setbkcolor(back);//设置背景颜色
    cleardevice();//清除屏幕包括用当前背景色填充屏幕
    StartGame();
    while (1)
    {
        GameDraw();
        GameContolr();
    }
    system("pause");
    return 0;
}