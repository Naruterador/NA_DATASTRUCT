/*
实现队列顺序结构2（出队列时不移动元素，只改变队列头元素的位置）

顺序结构2克服了在删除元素的时候，需要大量移动元素的操作，可用于简化操作，节约时间。

缺点:
1.队列的每个空间自始至终只能存一个队列元素。即使这个元素出列后也不能使用该空间
2.由于没有其他数据，当队头元素出队后，其值还保留在队列中。

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct queue2
{

    //初始化空间
    int * base;
    //尾指针，若队列不空，则指向队列尾元素的下一个位置
    int rear;
    //头指针，若队列不空，指向队列头元素
    int front;
    //队列大小
    int size;

};


void init_queue(struct queue2 *,int size);
void insert_queue(struct queue2 *,int val);
int delete_queue(struct queue2 *);
bool is_full(struct queue2 *);
bool is_empty(struct queue2 *);
void clearall(struct queue2 *);
void traverse(struct queue2 *);


int main(void)
{
    int val = 0;
    struct queue2 queue;
    init_queue(&queue,5);
    insert_queue(&queue,1);    
    insert_queue(&queue,2);    
    insert_queue(&queue,3);
    
    val = delete_queue(&queue);
    traverse(&queue);
    return 0;
}



void init_queue(struct queue2 * qu,int size)
{
    qu->base =(int *)malloc(sizeof(int) * size);
    if(NULL == qu->base)
    {
        printf("Can not assign the speace for qu->base!");
        exit(1);
    }
    
    qu->front = 0;
    qu->rear = 0;
    qu->size = size;
}

bool is_full(struct queue2 * qu)
{
    if(qu->rear == qu->size)
        return true;
    return false;
}

bool is_empty(struct queue2 * qu)
{
    if(qu->front == qu->rear)
        return true;
    return false;
}


void insert_queue(struct queue2 * qu,int val)
{
    if(is_full(qu))
    {
        printf("Queue is full!");
        exit(1);
    }
    qu->base[qu->rear] = val;
    qu->rear++;
}

int delete_queue(struct queue2 * qu)
{
    int temp;
    if(is_empty(qu))
    {
        printf("Queue is empty!");
        exit(1);
    }
    
    temp = qu->base[qu->front];
    qu->front++;
    return temp;
}



void traverse(struct queue2 * qu)
{
    int i = qu->front;
    while(qu->rear != i)
    {
        printf("%d\n",qu->base[i]);
        i++;
    }
}




void clearall(struct queue2 * qu)
{
    free(qu->base);
    qu->base = NULL;
    qu->front = 0;
    qu->rear = 0;
}




