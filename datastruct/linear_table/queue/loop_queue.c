/*
循环队列的实现

循环队列是为了解决“假溢出”问题而出现的。





*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct loopqueue
{
    //初始化动态分配的队列空间
    int * base;
    //头指针，若队列不空，指向队列头元素
    int front;
    //尾指针，若队列不空，指向尾元素的后一个位置
    int rear;
    int size;

}* pLsq;


void init_queue(pLsq,int size);
void insert_queue(pLsq,int val);
int delete_queue(pLsq);
void traverse(pLsq);
void clearall(pLsq);

bool is_empty(pLsq);
bool is_full(pLsq);


int main(void)
{
    int val;
    struct loopqueue queue;
    init_queue(&queue,5);
    insert_queue(&queue,1);
    insert_queue(&queue,2);
    insert_queue(&queue,3);
    
    //val = delete_queue(&queue);
    //val = delete_queue(&queue);
    //printf("%d\n",val);
    traverse(&queue);

    return 0;
}




void init_queue(pLsq qu,int size)
{
    qu->base =(int *)malloc(sizeof(int) * size);
    if(NULL == qu->base)
    {
        printf("Can not assign the space for qu->base");
        exit(1);
    }
    qu->front = 0;
    qu->rear = 0;
    qu->size = size + 1;

}


bool is_empty(pLsq qu)
{
    if(qu->front == qu->rear)
        return true;
    return false;
}

bool is_full(pLsq qu)
{
    if((qu->rear + 1) % qu->size == qu->front)
        return true;
    return false;
}


void insert_queue(pLsq qu,int val)
{
    if(is_full(qu))
    {
        printf("Queue is full!");
        exit(1);
    }
    qu->base[qu->rear] = val;
    qu->rear = (qu->rear + 1) % qu->size; 
}


int delete_queue(pLsq qu)
{
    int val;
    if(is_empty(qu))
    {
        printf("Queue is empty!");
        exit(1);
    }
    
    val = qu->base[qu->front];
    qu->front = (qu->front + 1) % qu->size;
    return val;
}

void traverse(pLsq qu)
{
   int i = qu->front;

    while(i != qu->rear)
    {
        printf("%d\n",qu->base[i]);
        i = (i + 1) % qu->size;

    }

}

void clearall(pLsq qu)
{
    free(qu->base);
    qu->base = NULL;
    qu->rear = 0;
    qu->front = 0;
}





