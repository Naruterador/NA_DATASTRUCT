#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
循环链表
*/


struct Node
{
    int data;
    struct Node * pNext;
};



struct Node * create_linked_list(int * ,int);
void tarverse(struct Node *);


int main(void)
{
    int a[5] = {4,3,1,2,5};
    int length = 5;
    struct Node * pHead = NULL;
    pHead = create_linked_list(a,length);
    tarverse(pHead);
    return 0;
}


struct Node * create_linked_list(int * val,int len)
{

    int i = 0;
    struct Node * pHead  =(struct Node *)malloc(sizeof(struct Node *));
    pHead->data = val[0];
    
    if(NULL == pHead)
        exit(1);
    
    struct Node * pTail = pHead;
    pTail->pNext = pHead;

    for(i = 1;i < len;i++)
    {
        struct Node * pNew = (struct Node *)malloc(sizeof(struct Node *));
        if(NULL == pNew)
            exit(1);
        
        pNew->data = val[i];
        pTail->pNext = pNew;
        pNew->pNext = NULL;
        pTail = pNew;

    }
    pTail->pNext = pHead;
    return pHead;
    
}


void tarverse(struct Node * listNode)
{
    struct Node * ptNext = listNode;
    while(listNode != ptNext->pNext)
    {    
        printf("%d\n",ptNext->data);
        ptNext = ptNext->pNext;
    }
    printf("%d\n",ptNext->data);
}
