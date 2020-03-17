#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


//控制方向的结构体
struct Direction
{
    int incX;
    int incY;
};


//存放走过迷宫节点的结构体
struct Box
{
    //横坐标
    int x;
    //纵坐标
    int y;
    //当前的方向
    int direct;
    
};

//栈节点
struct Node 
{
    struct Box d;
    struct Node * pNext;

};

//栈结构体
struct stack
{
    struct Node * pTop;
    struct Node * pBottom;
};


//生成迷宫的函数
void create_mazeboard(int mazeboard[4][4],int row,int col);
//栈操作函数
void create_stack(struct stack *);
void push_stack(struct stack *,struct Box);
struct Box pop_stack(struct stack *);
bool is_empty(struct stack *);
void traverse_stack(struct stack *);

//迷宫寻路函数
bool findPath(int mazeboard[4][4],struct Direction * dir,struct stack *);



int main(void)
{

    int i = 0;
    int j = 0;
    int a[4][4];
    struct stack sta;
    struct Box direction = {3,5,-1};
    struct Box direction1 = {1,1,0};
    struct Box direction2 = {4,2,7};
    
    struct Box test;

    create_mazeboard(a,4,4);
    for(i = 0;i < 4;i++)
    {    for(j = 0;j < 4;j++)           
            printf("%d ",a[i][j]);         
         printf("\n");
    } 
    create_stack(&sta);
    /*
        方向结构图数组
        有关方向说明
        1.迷宫方向选择优先级为右下左上
        2.这里(x,y)表示当前的坐标
        3.向右移动表示x,y + 1;
        4.向下移动表示x + 1,y;
        5.向左移动表示x, y - 1;
        6.向上移动表示x - 1,y;
    */
    struct Direction di[4] = {{0,1},{1,0},{0,-1},{-1,0}};

    if(findPath(a,di,&sta))
        traverse_stack(&sta);
    else
        printf("No exit in this maze!"); 
    return 0;
}

void create_stack(struct stack * sta)
{
    sta->pTop =(struct Node *)malloc(sizeof(struct Node));
    if(NULL == sta->pTop)
    {
        printf("Can not assigin the space for sta->sTop");
        exit(1);
    }
    sta->pBottom = sta->pTop;
    sta->pTop->pNext = NULL;
}

void push_stack(struct stack * sta,struct Box cup)
{
    struct Node * pNew = (struct Node *)malloc(sizeof(struct Node));
    if(NULL == pNew)
    {
        printf("Can not assign the space for the pNew");
        exit(1);
    }
    pNew->d = cup;
    pNew->pNext = sta->pTop;
    sta->pTop = pNew;
}

struct Box pop_stack(struct stack * sta)
{
    struct Node * p = sta->pTop;
    struct Box bNew = p->d;
    
    sta->pTop = p->pNext;
    free(p);
    p = NULL;
    return bNew;
}

bool is_empty(struct stack * sta)
{
    if(sta->pBottom == sta->pTop)
        return true;
    return false;
}

void traverse_stack(struct stack * sta)
{
    struct Node * p = sta->pTop;
    while(sta->pBottom != p)
    {
        struct Box * d1 = &(p->d);
        printf("%d ",d1->x);
        printf("%d",d1->y);
        printf("\n");
        p = p->pNext;
    }
}




    
void create_mazeboard(int mazeboard[4][4],int row,int col)
{
    int i = 0;
    int j = 0;
    srand(time(0)); 
    
    for(i = 0;i < row;i++)
        for(j = 0;j < col;j++)
        {  
            if ((0 == j && 0 == j) || (row - 1 == i && col - 1 == j))
                mazeboard[i][j] = 0;
            else
                mazeboard[i][j] = rand() % 2;
        }
}


bool findPath(int mazeboard[4][4],struct Direction * dir,struct stack * sta)
{
    
    //当前坐标节点的横坐标，纵坐标和方向
    int x,y,di;
    
    //移动之后的横坐标，纵坐标
    int nextx,nexty;
    
    //迷宫走过的路径只用（-1）来表示，防止重复走过
    mazeboard[0][0] = -1;
    

    //迷宫入口设置为(0,0)
    struct Box position = {0,0,-1};
    
    //将迷宫入口压入栈
    push_stack(sta,position);
    
    while(!is_empty(sta))
    {
        //如果走到某个节点发现4个方向都没有通路需要返回到上一个节点
        position = pop_stack(sta);
        x = position.x;
        y = position.y;
        di = position.direct + 1;
        while(di<4)
        {
            //下一个节点的(x,y)坐标
            nextx = x + dir[di].incX;
            nexty = y + dir[di].incY;
            //判断当前的坐标点是否可以通过            
            if(mazeboard[nextx][nexty] == 0)
            {
                //将当前节点入栈
                struct Box Current = {x,y,di};
                push_stack(sta,Current);
                x = nextx;
                y = nexty;
                //走过的节点设置成-1
                mazeboard[nextx][nexty] = -1;
                //检查迷宫是否到达终点
                if(x == 3 && y == 3)
                    return true;
                else
                    //移动到新节点之后要重新从向右开始移动
                    di = 0;
            }
            else 
                //如果当前道路方向走不通，则换一个方向走
               di++;
        }
    }
return false;

}
