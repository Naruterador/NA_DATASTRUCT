/*
链队列的实现
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



//队列元素
typedef struct Node
{
    int data;
    struct Node * pNext;

} * pNode;


//队列
typedef struct queuelist
{
    //队列头元素
    pNode front;
    //队列尾元素
    pNode rear;
} * queue;

void init_queue(queue);
void insert_queue(queue,int);
int delete_queue(queue);
int find_frontel(queue);
bool is_empty(queue);
void length_queue(queue);
void clearall(queue);


int main(void)
{
    int queueout = 0;
    int val = 0;
    struct queuelist queue;
    init_queue(&queue);
    insert_queue(&queue,1);
    insert_queue(&queue,2);
    insert_queue(&queue,3);

    //queueout = delete_queue(&queue);
    //queueout = delete_queue(&queue);
    //length_queue(&queue);
    clearall(&queue);
    return 0;
}


void init_queue(queue qu)
{
    qu->rear =(pNode)malloc(sizeof(struct Node));
    if(NULL == qu->rear)
    {
        printf("Can not assign the space for qu->rear");
        exit(1);
    }
    qu->front = qu->rear;
    qu->front->pNext = NULL;
}


bool is_empty(queue qu)
{
    if(NULL == qu->front->pNext)
        return true;
    return false;
}


void insert_queue(queue qu,int val)
{
    pNode pNew =(pNode)malloc(sizeof(struct Node));
    if(NULL == pNew)
    {
        printf("Can not assign the space for pNew");
        exit(1);
    }
    pNew->data = val;
    
    if(is_empty(qu))
    {
        pNew->pNext = qu->front;
        qu->front = pNew;
        qu->rear = qu->front;
    }else
    {
        pNew->pNext = qu->rear;
        qu->rear = pNew; 
    }

}


int delete_queue(queue qu)
{
    if(is_empty(qu))
    {
        printf("Queue is empty!");
        exit(1);
    }
    
    int temp = 0;
    pNode q = qu->rear;
    pNode df;
    while(q->pNext != qu->front)
    {
        q = q->pNext;
    }
    
    df = qu->front;
    qu->front = q;
    temp = df->data;
    
    free(df);
    df = NULL;
    return temp;

}


int find_frontel(queue qu)
{
    if(is_empty(qu))
    {
        printf("Queue is empty!");
        exit(1);
    }
    pNode q = qu->rear;
    while(q != qu->front)
    {
        q = q->pNext;

    }
    return q->data;
}


void length_queue(queue qu)
{
    int length = 0;
    if(is_empty(qu))
    {
        printf("Queue is empty!");
        exit(1);
    }
    pNode q = qu->rear;
    while(qu->front != q)
    {
        q = q->pNext;
        length++;
    }
    printf("Length is %d\n",length + 1);
}

void clearall(queue qu)
{
    
    if(is_empty(qu))
    {
        printf("Queue is empty");
        exit(1);
    }

    pNode q = qu->rear;
    pNode temp;
    while(qu->front != q)
    {
        temp = q->pNext;
        free(q);
        q = NULL;
        q = temp;
    }
    q->pNext = NULL;
    qu->rear = qu->front;
    qu->front = q;
    free(q);
}


