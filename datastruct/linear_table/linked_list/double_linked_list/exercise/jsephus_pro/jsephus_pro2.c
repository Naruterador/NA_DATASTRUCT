//双向循环连环解决约瑟夫环问题
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node
{
    struct Node * prior;
    int data;
    struct Node * next;
} * pNode;


pNode create_linked_list(int *,int);
void display(pNode);
void lineoutall(pNode,int start,int count);

int main(void)
{
    int a[5] = {1,2,3,4,5};
    pNode pHead = NULL;
    pHead = create_linked_list(a,5);
    lineoutall(pHead,3,3);
    //display(pHead);
    return 0;

}


pNode create_linked_list(int * a,int len)
{
    int i = 0;
    pNode pHead = (pNode)malloc(sizeof(pNode));
    if(NULL == pHead)
        exit(1);
    
    pHead->data = a[0];
    pNode pTail = pHead;
    pTail->prior = NULL;
    pTail->next = NULL;

    for(i=1;i < len;i++)
    {
        pNode pNew =(pNode)malloc(sizeof(pNode));
        if(NULL == pNew)
            exit(1);

        pNew->data = a[i];
        pTail->next = pNew;
        pNew->prior = pTail;
        pNew->next = NULL;
        pTail = pNew;

    }
    pTail->next = pHead;
    pHead->prior = pTail;
    return pHead;
}

void display(pNode linkedlist)
{
    pNode ptNext = linkedlist;
    while(linkedlist != ptNext->next)
    {
        printf("%d\n",ptNext->data);
        ptNext = ptNext->next;
    }
    printf("%d\n",ptNext->data);
}

void lineoutall(pNode linkedlist,int start,int count)
{
    int i = 0;
    pNode p = linkedlist;
    pNode pTail;
    //找到从哪里开始数（对应start的链表节点）
    while(start != p->data)
        p = p->next;

    while(p != p->next)
    {
        
        for(i = 1;i < count;i++)
        {
            pTail = p;
            p = p->next;

        }
        pTail->next = p->next;
        printf("%d\n",p->data);
        p = pTail->next;

    }
    printf("%d\n",p->data);
    free(p);
}




















