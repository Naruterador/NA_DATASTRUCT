/*
没有长度限制的循环队列实现
*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CSTreeNode.h"


struct queuelist
{
    CSTree * cst; 
    //若队列不空，头指针指向当前头元素
    int front;
    //若队列不空，尾指针指向当前尾元素的后一个位置
    int rear;
    //队列的默认长度
    int queuesize;

};


void init_queue(struct queuelist * ,int size);
void insert_queue(struct queuelist *,CSTree);
CSTree delete_queue(struct queuelist *);
bool is_empty(struct queuelist *);
bool is_full(struct queuelist *);


void init_queue(struct queuelist * qu,int size)
{
    qu->queuesize = size + 1;
    qu->cst =(CSTree *)malloc(sizeof(CSTree) * qu->queuesize);
    if(NULL == qu->cst)
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

void insert_queue(struct queuelist * qu,CSTree csn)
{

  int i = 0;
  //插入队列时，先判断队列是否满，如果满了，需要动态的增加一个元素空间
  if(is_full(qu))
  {
    qu->cst =(CSTree *)realloc(qu->cst,sizeof(CSTree) * (qu->queuesize + 1));
    if(NULL == qu->cst)
    {
        printf("Can not assign the space for the new qu->base");
        exit(1);
    }
    //如果头元素大于尾元素，则将SIZE+1位和front位向后移动一位
    if(qu->front > qu->rear)
    {
        for(i = qu->queuesize - 1;i >= qu->front;i--)
            qu->cst[i + 1] = qu->cst[i];
        qu->front++;
    }
    //最大空间+1
    qu->queuesize++;
  }
    qu->cst[qu->rear] = csn;
    qu->rear = (qu->rear + 1) % qu->queuesize;

}



CSTree  delete_queue(struct queuelist * qu)
{
    CSTree temp;
    temp = qu->cst[qu->front];
    qu->front = (qu->front + 1) % qu->queuesize;
    
    return temp;
}
