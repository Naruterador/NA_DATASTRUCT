#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
单向循环链表解决Josephus problem（约瑟夫环问题）

*/

typedef struct Node
{
    int data;
    struct Node * pNext;

} * pNode;


pNode create_linked_list(int *,int);
void lineout(int * , int,int,int);


int main(void)
{
    int a[5] = {1,2,3,4,5};
    lineout(a,5,3,3);
    return 0;
}


pNode create_linked_list(int * data,int members)
{
    int i = 0;
    pNode pHead = (pNode)malloc(sizeof(pNode));
    if (NULL == pHead)
        exit(-1);
    pHead->data = data[0];
    
    pNode pTail = pHead;
    pTail->pNext = NULL;

    for(i = 1;i < members;i++)
    {
        pNode pNew =(pNode)malloc(sizeof(pNode));
        if(NULL == pNew)
            exit(1);
        
        pNew->data = data[i];
        pTail->pNext = pNew;
        pNew->pNext = NULL;
        pTail = pNew;

    }
    pTail->pNext = pHead;
    return pHead;
}


void lineout(int * data,int members,int start,int count)
{
    //创建链表
    pNode pHead = create_linked_list(data,members);
    pNode pTail;
    
    //找到第K个链表
    pNode p = pHead;
    while(p->data != start)
    {    
        p = p->pNext;
    }
    //从编号为p的人开始，只要有符合p->Next==p时，说明链表中除了p节点，所有编号都出列了
    while(p->pNext != p)
    {
        int i;
        //让节点p数m个位置
        for(i = 1;i < count;i++)
        {
            pTail = p;
            p = p->pNext;
        }
        pTail->pNext = p->pNext;
        printf("%d\n",p->data);
        p = pTail->pNext;
    }
    printf("%d\n",p->data);
}
