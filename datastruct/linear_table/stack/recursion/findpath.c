/*
使用递归函数找到迷宫出路
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//定义迷宫运动方向的结构体
struct Direction
{
    int incX;
    int inCY;
};


//初始化迷宫图
void init_mazeboard(int mazeboard[4][4]);
//寻路函数,带入三个参数分别是迷宫图，起点和终点的坐标
int findpath(int mazeboard[4][4],int x,int y);



int main(void)
{
    int i = 0;
    int j = 0;
    int a[4][4];
    init_mazeboard(a);

    for(i = 0;i < 4;i++)
    {    for(j = 0;j < 4;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
    findpath(a,0,0);
    printf("0,0\n");

    return 0;
}



void init_mazeboard(int mazeboard[4][4])
{
    srand((int)time(0));
    int i = 0;
    int j = 0;

    for(i = 0;i < 4;i++)
        for(j = 0;j < 4;j++)
        {
            if((i == 0 &&  j == 0)|| (i == 3 && j == 3 ))
                mazeboard[i][j] = 0;
            else
                mazeboard[i][j] = rand() % 2;
        }
}



int findpath(int mazeboard[4][4],int x, int y)
{
    
    int tag = 0;
    int nextx,nexty;
    //mazeboard[x][y] = -1;
    
    //方向控制，优先级为右下左上
    struct Direction direction[4] = {{0,1},{1,0},{0,-1},{-1,0}};
    
    //越界将跳出递归
    if(x < 0 || x > 3 || y < 0 || y > 3)
        return 0;

    //到达出口
    if(x == 3 && y == 3)
    {
        return 1;
    }

    for(int i = 0;i < 4;i++)
    {
        //下一个节点的坐标       
        nextx= x + direction[i].incX;
        nexty = y + direction[i].inCY;
        
        //判断这个下一个节点是否可以通过
        if(mazeboard[nextx][nexty] == 0)
        {
            //将通过的节点赋上-1,防止重复走
            mazeboard[nextx][nexty] = -1;
            
            //进入递归分析下一个节点，并将返回值给标记位
            tag = findpath(mazeboard,nextx,nexty);
            
            //如果节点可以通过，则输出这个节点
            if(1 == tag)
            {
                printf("%d,%d\n",nextx,nexty);
                return 1;
            }

        }

    }
    return 0;
}


