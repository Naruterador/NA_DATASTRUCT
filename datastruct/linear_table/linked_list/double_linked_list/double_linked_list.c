#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//实例双向不循环链表


struct Node
{
    struct Node * prior;  
    int data;
    struct Node * back;
};


struct Node * create_linked_list(int * a,int);
void traverse(struct Node *);
struct Node *  insertNode(struct Node *,int,int);
struct Node * deleteNode(struct Node *,int);


int main(void)
{
    int a[5] = {1,2,3,4,5};
    int len = 5;
    struct Node * pHead = NULL;
    pHead = create_linked_list(a,len);
    //pHead = insertNode(pHead,100,2);
    pHead = deleteNode(pHead,1);
    traverse(pHead);

}


struct Node * create_linked_list(int * a,int len)
{
    int i = 0;
    struct Node * pHead = (struct Node *)malloc(sizeof(struct Node*));
    if(NULL == pHead)
        exit(1);
    pHead->data = a[0];
    struct Node * pTail = pHead;
    pTail->prior = NULL;
    pTail->back = NULL;

    for(i = 1;i < len;i++)
    {
        struct Node * pNew =(struct Node *)malloc(sizeof(struct Node *));
        if(NULL == pNew)
            exit(1);


        pNew->data = a[i];
        pTail->back = pNew;
        pNew->prior = pTail;
        pNew->back = NULL;
        pTail = pNew;

    }
    return pHead;

}

void traverse(struct Node * linkedlist)
{   
    struct Node * ptNode = linkedlist;
    while(NULL != ptNode->back)
    {
        printf("%d\n",ptNode->data);
        ptNode = ptNode->back;
    }
    printf("%d\n",ptNode->data);

}

struct Node * insertNode(struct Node * linkedlist,int data,int position)
{
    int i;
    struct Node * pNew =(struct Node *)malloc(sizeof(struct Node *));
    if(NULL == pNew)
        exit(1);
        //return false;
    struct Node * pCurrent = linkedlist;
    struct Node * q;
    
    if(position == 1)
    {
        pNew->data = data;
        pNew->prior = NULL;
        pNew->back = pCurrent;
        pCurrent->prior = pNew;
        return pNew;
    }

    for(i = 0;i < position - 1;i++)
    {
        q = pCurrent;
        pCurrent = pCurrent->back;
    }


    pNew->data = data;
    pNew->prior = q;
    pNew->back = pCurrent;
    q->back = pNew;
    pCurrent->prior = pNew;
    return linkedlist;
}

struct Node * deleteNode(struct Node * linkedlist,int position)
{
    int i = 0;
    struct Node * pCurrent = linkedlist;
    struct Node * q;

    if(position == 1)
    {
       q = pCurrent->back;
       q->prior = NULL;
       return q;
    }


    for(i = 0;i < position - 1;i++)
    {
        q = pCurrent;
        pCurrent = pCurrent->back;
    }
    
    struct Node * p;
    q->back = pCurrent->back;
    p = pCurrent->back;
    p->prior = q;
    
    return linkedlist;
}

