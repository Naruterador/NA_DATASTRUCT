/*
非循环队列实现迷宫求解

利用非循环队列求解的迷宫是走的斜线，不管方向设置是4个还是8个，都是走斜面。

×××遗留问题：如果解决选4方向走斜线的问题。

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



//迷宫方向结构体
struct Direction
{
    int incX;
    int incY;
};

//迷宫坐标和位置节点
struct mazeNode
{
    //迷宫横坐标
    int x;
    //迷宫纵坐标:
    int y;
    //迷宫上一个节点的坐标
    int pre;
};

//队列结构体
struct queuelist
{   
    //迷宫节点
    struct mazeNode * qNode;
    //读列头指针位置
    int front;
    //队列尾指针位置，指向后一个节点
    int rear;
    //队列的大小
    int size;

};

//栈节点
struct stackNode
{
    struct mazeNode mazeel;
    struct stackNode * pNext;
};

//栈空间结构体
struct stack
{
    struct stackNode * pTop;
    struct stackNode * pBottom;
};



//队列操作
void init_queue(struct queuelist *);
void insert_queue(struct queuelist *,int ,int ,int);
struct mazeNode delete_queue(struct queuelist *);
bool is_qempty(struct queuelist *);

//栈操作
void init_stack(struct stack *);
void push_stack(struct stack *,struct mazeNode );
struct mazeNode pop_stack(struct stack *);
bool is_sempty(struct stack *);

//生成迷宫地图
void init_mazeboard(int mazeboard[5][5]);

//迷宫算法实现函数
void mazefindout(int mazeboard[5][5],struct Direction *,struct stack * ,struct queuelist * );



int main(void)
{
    
    struct queuelist queue;
    struct stack sta;
    int a[5][5];
    init_mazeboard(a);
    for(int i = 0; i < 5;i++)
    {
        for(int j = 0;j < 5;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }

    //4个方向
    struct Direction dif[4] = {{0,1},{1,0},{0,-1},{-1,0}};
    //8个方向
    struct Direction die[8] ={{0,1},{1,0},{0,-1},{-1,0},{-1,1},{1,1},{1,-1},{-1,-1}};

    mazefindout(a,dif,&sta,&queue);
  

    return 0;
}


//生成迷宫图
void init_mazeboard(int mazeboard[5][5])
{
    int i = 0;
    int j = 0;
    srand((int)time(NULL));
    
    for(i = 0;i < 5;i++)
        for(j = 0;j < 5;j++)
        {
            if((i == 0 && j == 0 )||(i == 4 && j == 4))
                mazeboard[i][j] = 0;
            else
                mazeboard[i][j] = rand() % 2;                        
        }
}


//生成队列
void init_queue(struct queuelist * qu)
{
    qu->size = 1;
    qu->qNode =(struct mazeNode *)malloc(sizeof(struct mazeNode) * qu->size);
    if(NULL == qu->qNode)
    {
        printf("Can not assign for queue");
        exit(1);
    }
    qu->rear = 0;
    qu->front = 0;
}

//插入队列元素
void insert_queue(struct queuelist * qu,int x,int y,int pre)
{
    //没插入一个数据队列就增加1
    qu->size++;
    qu->qNode = (struct mazeNode * )realloc(qu->qNode,sizeof(struct mazeNode)* qu->size);
    if(NULL == qu->qNode)
    {
        printf("ERROR qu->qNode");
        exit(1);
    }
    qu->qNode[qu->rear].x = x;
    qu->qNode[qu->rear].y = y;
    qu->qNode[qu->rear].pre = pre;
    
    qu->rear++;
}

//删除队列元素
struct mazeNode delete_queue(struct queuelist * qu)
{
    struct mazeNode rqNode;
    rqNode = qu->qNode[qu->front];
    qu->front++;
    return rqNode; 
}

//判断队列是否为空
bool is_qempty(struct queuelist * qu)
{
    if(qu->front == qu->rear)
        return true;
    return false;
}

//初始化栈
void init_stack(struct stack * sta)
{
    sta->pTop = (struct stackNode *)malloc(sizeof(struct stackNode));
    if(NULL == sta->pTop)
    {
        printf("ERROR sta->pTop");
        exit(1);
    }
    sta->pBottom = sta->pTop;
    sta->pTop->pNext = NULL;
}

//压入栈
void push_stack(struct stack * sta,struct mazeNode mnode)
{
    struct stackNode * pNew = (struct stackNode *)malloc(sizeof(struct stackNode));
    if(NULL == pNew)
    {
        printf("Can not assign for New stack Node");
        exit(1);
    }
    pNew->mazeel = mnode;
    pNew->pNext = sta->pTop;
    sta->pTop = pNew;
}


//弹出栈
struct mazeNode pop_stack(struct stack * sta)
{
    if(is_sempty(sta))
    {
        printf("Stack is empty!");
        exit(1);

    }
    struct mazeNode pmNode;
    struct stackNode * q = sta->pTop;
    sta->pTop = q->pNext;
    pmNode = q->mazeel;
    free(q);
    q = NULL;
    return pmNode;
}

//判断栈是否为空
bool is_sempty(struct stack * sta)
{
    if(sta->pBottom == sta->pTop)
        return true;
    return false;
}



void mazefindout(int mazeboard[5][5],struct Direction * di,struct stack * sta,struct queuelist * qu)
{
    //迷宫的初始起点，pre初始赋-1    
    struct mazeNode startN = {0,0,-1};

    int i = 0;
    int x = startN.x;
    int y = startN.y;
    int pre = startN.pre;
    //确定当前迷宫是否走完的标记值
    int flag = 0;
    
    //迷宫起点赋值-1
    mazeboard[x][y] = -1;


    init_queue(qu);
    insert_queue(qu,x,y,pre);

    //计算函数迷宫出口函数
    while(!(is_qempty(qu)) && flag == 0)
    {   
        int i = 0;
        struct mazeNode preNode = delete_queue(qu);
        
        while(i < 4)
        {   
            //求出迷宫的下一个节点坐标            
            preNode.x = preNode.x + di[i].incX;
            preNode.y = preNode.y + di[i].incY;
            //检查迷宫的下一个节点坐标是否可以通过，可以通过为0,不能通过为其他值
            if(mazeboard[preNode.x][preNode.y] == 0)
            {
                //走过的路径需要修改路径值
                mazeboard[preNode.x][preNode.y] = -1;
                //前一个迷宫坐标节点在队列中的指针地址
                pre = qu->front - 1;
                //将可以通过的路径压如队列内
                insert_queue(qu,preNode.x,preNode.y,pre);
                //迷宫出口判断
                if(preNode.x == 4 && preNode.y == 4)
                {   
                    flag = 1;
                    break;
                }
                
            }
            i++;

        }

    }
    //如果Flag为真，表示迷宫有解
    if(flag)
        {
            int k = qu->rear - 1;
            init_stack(sta);
            //将队列中的坐标压入栈
            while(k >=0)
            {
                push_stack(sta,qu->qNode[k]);
                k = qu->qNode[k].pre;
            }
            struct mazeNode coor;
            //将队列中的坐标出栈
            while(!is_sempty(sta))
            {
                coor = pop_stack(sta);
                
                printf("[%d,%d]",coor.x,coor.y);

            }
            
        }else
        {
            printf("迷宫没有出路！");
            exit(1);            
        }

        
        
}