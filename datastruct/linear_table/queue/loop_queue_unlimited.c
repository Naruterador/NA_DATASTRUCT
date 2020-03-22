/*
没有长度限制的循环队列实现
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



struct queuelist
{
    int * base;
    //若队列不空，头指针指向当前头元素
    int front;
    //若队列不空，尾指针指向当前尾元素的后一个位置
    int rear;
    //队列的默认长度
    int queuesize;

};


void init_queue(struct queuelist * ,int size);
void insert_queue(struct queuelist *,int val);
int delete_queue(struct queuelist *);
void traverse_queue(struct queuelist *);



bool is_empty(struct queuelist *);
bool is_full(struct queuelist *);



int main(void)
{

    struct queuelist queue;
    init_queue(&queue,5);
    insert_queue(&queue,1);
    insert_queue(&queue,2);
    insert_queue(&queue,3);
    insert_queue(&queue,4);
    insert_queue(&queue,5);
    insert_queue(&queue,6);
    insert_queue(&queue,7);
    insert_queue(&queue,8);

    delete_queue(&queue);

    traverse_queue(&queue);

    return 0;
}




void init_queue(struct queuelist * qu,int size)
{
    qu->queuesize = size + 1;
    qu->base =(int *)malloc(sizeof(int) * qu->queuesize);
    if(NULL == qu->base)
    {
        printf("Can not assign for the qu->base");   
        exit(1);
    }
    
    qu->front = 0;
    qu->rear = 0;

}

bool is_empty(struct queuelist * qu)
{
    if(qu->front == qu->rear)
        return true;
    return false;
}

bool is_full(struct queuelist * qu)
{
    if((qu->rear + 1) % qu->queuesize == qu->front)
        return true;
    return false;
}


void traverse_queue(struct queuelist * qu)
{
    int i = 0;
    i = qu->front;
    while(i != qu->rear)
    {
        printf("%d\n",qu->base[i]);
        i = (i + 1) % qu->queuesize;

    }

}


void insert_queue(struct queuelist * qu,int val)
{

  int i = 0;
  //插入队列时，先判断队列是否满，如果满了，需要动态的增加一个元素空间
  if(is_full(qu))
  {
    qu->base =(int *)realloc(qu->base,sizeof(int) * (qu->queuesize + 1));
    if(NULL == qu->base)
    {
        printf("Can not assign the space for the new qu->base");
        exit(1);
    }
    //如果头元素大于尾元素，则将SIZE+1位和front位向后移动一位
    if(qu->front > qu->rear)
    {
        for(i = qu->queuesize - 1;i >= qu->front;i--)
            qu->base[i + 1] = qu->base[i];
        qu->front++;
    }
    //最大空间+1
    qu->queuesize++;
  }
    qu->base[qu->rear] = val;
    qu->rear = (qu->rear + 1) % qu->queuesize;

}



int delete_queue(struct queuelist * qu)
{
    int val = 0;
    val = qu->base[qu->front];
    qu->front = (qu->front + 1) % qu->queuesize;
    
    return val;
}
