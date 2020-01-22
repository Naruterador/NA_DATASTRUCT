#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
循环链表解决Josephus problem（约瑟夫环问题）

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
    
    pNode pTail = pHead;
    pTail->pNext = pHead;

    for(i;i < members;i++)
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
    pNode pHead = create_linked_list(data,members);
    
    
    //1.找到开始报数的链表
    
    pNode pStart = pHead; 
    int i = 0;
    int j = 0;
    int k = 0;
    for(i;i < start;i++)
        pStart = pStart->pNext;

    pNode pEnd = pStart;
    pNode pTemp1;
    pNode pTemp2 = NULL;
    //2.从start处开始出列
    while(NULL != pHead->pNext->data)
    {

        for (j = 0;j < count;j++)
        {   
            if(j == (count - 2))
                if(pEnd->pNext->pNext == pHead)
                    pTemp2 = pEnd;
            
            if(j == (count - 1) && pEnd != pHead)
                pTemp1 = pEnd;
            
            if(pHead == pEnd->pNext && j < (count - 1))
            {
                for(k = j;k < count;k++)
                    pEnd = pEnd->pNext;
                    pHead->pNext = pEnd->pNext;
                    j++;
                    pTemp1 = pEnd;
            }

            pEnd = pEnd->pNext;
           
        }
        printf("%d\n",pTemp1->data);
        if(NULL != pTemp2)
        {
            pTemp2->pNext = pHead;
            pTemp2 = NULL;
        }
        pTemp1->data = NULL;

    }
    
}