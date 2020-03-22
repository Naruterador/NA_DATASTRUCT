/*
队列的顺序结构实现1：
非循环结构（队列的元素在[0]单元）

缺点：
1.在出队列时候必须移动大量元素
2.在队列较长时，效率比较低

*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct sq
{
    int * base;   //初始化存储空以数组来表示
    int rear;     //尾指针，指向队列元素的下一个位置
    int size;     //为当前队列分配的存储容量
}* pSq;


void init_seq_queue(pSq,int);
void insert_seq_queue(pSq,int);int delete_seq_queue(pSq);
int front_el(pSq);
bool is_empty(pSq);
bool is_full(pSq);
void clearall(pSq);



int main(void)
{

    int val;
    struct sq queue;
    init_seq_queue(&queue,5);
    insert_seq_queue(&queue,1);
    insert_seq_queue(&queue,2); 
    insert_seq_queue(&queue,3);
    clearall(&queue);
    return 0;
}


void init_seq_queue(pSq seq,int size)
{
    seq->base = (int *)malloc(sizeof(int) * size);
    if(NULL == seq->base)
    {
        printf("Can not assign the space for seq->base");
        exit(1);
    }
    seq->rear = 0;
    seq->size = size;
}

bool is_full(pSq seq)
{
    if(seq->rear >= seq->size)
        return true;
    return false;       
}

bool is_empty(pSq seq)
{
    if(0 == seq->rear)
        return true;
    return false;
}


void insert_seq_queue(pSq seq,int val)
{
    if(is_full(seq))
    {
        printf("Queue is full");
        exit(1);
    }
    
    seq->base[seq->rear] = val;
    seq->rear++;
}

int delete_seq_queue(pSq seq)
{
    
    int i = 0;
    if(is_empty(seq))
    {
        printf("Queue is empty!");
        exit(1);
    }
    for(i = seq->rear - 1;i > 0;i--)
    {
        seq->base[i - 1] = seq->base[i];
    }

    seq->rear--;
    return seq->base[0];
}


int front_el(pSq seq)
{
    return seq->base[0];

}


void clearall(pSq seq)
{
    seq->base = NULL;
    seq->rear = 0;
    seq->size = 0;

}





