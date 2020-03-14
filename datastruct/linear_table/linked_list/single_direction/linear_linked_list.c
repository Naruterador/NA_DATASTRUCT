#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
线性链表的实现
单向不循环链表
*/


typedef struct Node
{
    int data;
    struct Node * pNext;
} * pNode;


pNode create_linked_list(int *,int);
void traverse_linked_list(struct Node *);
int length_list(struct Node *);
bool is_empty(struct Node *);
bool insert_ce(struct Node *,int ,int);
bool delete_ce(struct Node *,int);
bool sorted(struct Node *);

int main(void)
{
    int a[5] = {4,3,1,2,5};
    int len = 5;


    pNode pHead = NULL;
    pHead = create_linked_list(a,len);
    //insert_ce(pHead,100,1);
    //delete_ce(pHead,2);
    sorted(pHead);
    traverse_linked_list(pHead);
    
    //printf("The lentgh of linked_list: %d",length_list(pHead));
}

pNode create_linked_list(int * val,int len)
{
    int i = 0;
    //创建头节点
    pNode pHead =(pNode)malloc(sizeof(pNode));
    if (NULL == pHead)
        {
            printf("Can not assign the space for pHead!");
            exit(1);
        }
    //创建尾节点
    pNode pTail = pHead;
    pTail->pNext = NULL;

    for(i;i < len;i++)
    {   
        //创建一个新节点
        pNode pNew =(pNode)malloc(sizeof(pNode));
        if (NULL==pNew)
        {
            printf("Can not assign the space for pHead!");
            exit(1);
        }
        //为新节点插入值
        pNew->data = val[i];
        //将尾节点的下一个节点设置成新节点
        pTail->pNext = pNew;
        //将新节点下一个节点地址设置为NULL
        pNew->pNext = NULL;
        //将新节点设置为尾节点
        pTail = pNew;    
    }

    return pHead;

}

void traverse_linked_list(struct Node * listNode)
{
    pNode ptNext;
    ptNext = listNode;
    while(NULL != ptNext->pNext)
    {
        ptNext = ptNext->pNext;
        printf("%d\n",ptNext->data);
       

    }
    //printf("%d\n",ptNext->data);
}

int length_list(struct Node * listNode)
{
    int length = 0;
    pNode ptNext;
    ptNext = listNode;
    while(ptNext->pNext != NULL)
    {
        
        ptNext = ptNext->pNext;
        length++;

    }
    return length;
}


bool is_empty(struct Node * listNode)
{
    pNode Node = listNode;
    
    if(NULL == Node->pNext)
        return true;

    return false;
}



bool insert_ce(struct Node * listNode,int val,int position)
{

    int i = 0;
    pNode pNew =(pNode)malloc(sizeof(pNode));
    if(NULL == pNew && position < 1)
    {
        return false;
    }
    pNode pPervious = listNode;
    for(i;i < position - 1;i++)
    {
        pPervious = pPervious->pNext;
    }

    pNew->data = val;
    pNew->pNext = pPervious->pNext;
    pPervious ->pNext = pNew;
    return true;
}



bool delete_ce(struct Node * listNode,int position)
{   


    if(is_empty(listNode))
    {
        return false;
    }
    
    int i = 0;
    pNode pPervious = listNode;

    for(i;i < position - 1;i++)
    {
        pPervious = pPervious->pNext;
    }
    
    pNode temp = pPervious->pNext;

    pPervious->pNext = temp->pNext;

    return true;

}


bool sorted(struct Node * listNode)
{
    if(is_empty(listNode))
        return false;

    int len = length_list(listNode);
    int i = 0;
    int j = 0;
    int temp = 0;
    pNode pCurrent = listNode->pNext;
    pNode pNext = pCurrent->pNext;

    for(i;i < len - 1;i++)
    {
        for(j = i;j < len -1;j++)
        {
            if(pCurrent->data > pNext->data)
            {
                temp = pCurrent->data;
                pCurrent->data = pNext->data;
                pNext->data = temp;
            }
            pNext = pNext->pNext;
        }
        pCurrent = pCurrent->pNext;
        pNext = pCurrent->pNext;
    }
}
