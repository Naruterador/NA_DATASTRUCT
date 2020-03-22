/*
循环队列的实现

循环队列是为了解决“假溢出”问题而出现的。


在循环队列中，队尾指针可能小于队头指针。入队元素时，队尾指针加 1。当队列满
时，队尾指针等于队头指针，和队列空的条件一样。为了区别队满和队空，在循环队列
中，少用一个存储单元。也就是在存储空间为 MAX_QSIZE 的循环队列中，最多只能存放
MAX_QSIZE-1 个元素。这样，队列空的条件仍为队尾指针等于队头指针，队列满的条件
改为(队尾指针+1)对 MAX_QSIZE 求余等于队头指针。


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
int length(pLsq);
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
    //traverse(&queue);
    val = length(&queue);
    printf("%d\n",val);
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



int length(pLsq qu)
{
    int length;
    
    length = (qu->rear - qu->front + qu->size) % qu->size;

    return length;
}






void clearall(pLsq qu)
{
    free(qu->base);
    qu->base = NULL;
    qu->rear = 0;
    qu->front = 0;
}





