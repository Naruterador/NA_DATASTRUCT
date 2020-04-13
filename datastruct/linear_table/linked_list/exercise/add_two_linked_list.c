/*
给定两个非空链表，每一个节点代表一个数字0-9，单个链表从左往右是由高位到低位组成的一个数，现在需要将两个链表表示的数相加并且以链表形式返回。


举例：Input: (7-> 2 -> 4 -> 3) + (5 -> 6 -> 4) Output: 7 -> 8 -> 0 -> 7

以双向链表逆序的方式来实现


（1）malloc函数:
其原型void *malloc(unsigned int num_bytes)；
num_byte为要申请的空间大小，需要我们手动的去计算，如int *p = (int *)malloc(20*sizeof(int)),
如果编译器默认int为4字节存储的话，那么计算结果是80Byte，一次申请一个80Byte的连续空间，
并将空间基地址强制转换为int类型，赋值给指针p,此时申请的内存值是不确定的。

（2）calloc函数:
其原型void *calloc(size_t n, size_t size)；
其比malloc函数多一个参数，并不需要人为的计算空间的大小，比如如果他要申请20个int类型空间
会int *p = (int *)calloc(20, sizeof(int)）,这样就省去了人为空间计算的麻烦。
但这并不是他们之间最重要的区别，malloc申请后空间的值是随机的，并没有进行初始化，
而calloc却在申请后，对空间逐一进行初始化，并设置值为0;

（3）realloc函数和上面两个有本质的区别，
其原型void realloc(void *ptr, size_t new_Size)
用于对动态内存进行扩容(及已申请的动态空间不够使用，需要进行空间扩容操作)，
ptr为指向原来空间基址的指针， new_size为接下来需要扩充容量的大小。
实例：
    const int size = 2000;
    int *p = (int *)malloc(20*sizeof(int));
    int *pp = (int *)realloc(p, size*sizeof(int));

程序注意点:
malloc、realloc、calloc在一段程序里不能使用相同的变量名重复声明




*/



#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node * prior;
    int data;
    struct Node * next;
} * pNode;


pNode create_linked_list(int *,int);
void display(pNode);
pNode add(pNode,pNode);



int main(void)
{
    int k = 0;
    pNode pHead1 = NULL;
    pNode pHead2 = NULL;
    pNode pHead3 = NULL;
    int a[3] = {9,9,9};
    int b[3] = {9,9,9};
    pHead1 = create_linked_list(a,3);
    pHead2 = create_linked_list(b,3);
    pHead3 = add(pHead1,pHead2);
    display(pHead3);
    return 0;
}

pNode create_linked_list(int * data,int len)
{
    int i = 0;
    pNode pHead =(pNode)malloc(sizeof(pNode));
    if(NULL == pHead)
    {    
        printf("can not assign the space for pHead");
        exit(1);
    }
    
    pHead->data = data[0];
    pNode pTail = pHead;
    pTail->prior = NULL;
    pTail->next = NULL;

    for(i = 1;i < len;i++)
    {
        pNode pNew = (pNode)malloc(sizeof(pNode));
        if(NULL == pNew)
        {
            printf("can not assign the space for pNew");
            exit(1);
        }
        
        pNew->data = data[i];
        pTail->next = pNew;
        pNew->prior = pTail;
        pNew->next =NULL;
        pTail = pNew;

    }
    
    return pHead;
}

void display(pNode linkedlist)
{
    pNode ptNext = linkedlist;
    while(NULL != ptNext->next)
    {
        ptNext = ptNext->next;
        printf("%d\n",ptNext->data);
    }
    
}


pNode add(pNode list1,pNode list2)
{
    int lengthl1 = 0;
    int lengthl2 = 0;
    //找到链表list1的尾节点
    pNode ldl1 = list1;
    while(NULL != ldl1->next)
    {
        lengthl1++;
        ldl1 = ldl1->next;
    }
    
    //找到链表list2的尾节点
    pNode ldl2 = list2;
    while(NULL != ldl2->next)
    {
        lengthl2++;
        ldl2 = ldl2->next;
    }
    int i = 0;
    int num = 0;
    int temp = 0;
    pNode q;
    pNode p;
    pNode ta;
    
    pNode pHead =(pNode)malloc(sizeof(pNode));
    if(NULL == pHead)
        exit(1);
    pNode pTail = pHead;
    pTail->prior = NULL;
    pTail->next = NULL;
    
    if(lengthl1 > lengthl2)
    {
        q = ldl1;
        p = ldl2;
    }
    else if(lengthl1 < lengthl2)
    {    
        q = ldl2;
        p = ldl1;
    }
    else{
        q = ldl1;
        p = ldl2;
    }
    int data1 = 0;
    int data2 = 0;
    while(NULL != q->prior)
    {   
        if(NULL != q->prior)
        {
            ta = q;
            data1 = q->data;
            q = q->prior;
        }

        if(NULL != p->prior)
        {
            data2 = p->data;
            p = p->prior;
        }else{
            if(NULL != ta->prior && NULL == p->prior)
            {
                data2 = p->data;
            }else{
                data2 = 0;
            }
        }

        num = data1 + data2;
        if(num > 9)
        {
            temp = num % 10;
            p->data++;
        }else{
            temp = num;
        }
        
        pNode pNew =(pNode)malloc(sizeof(pNode));
        if(NULL == pNew)
            exit(1);
        pNew->data = temp;
        pTail->next = pNew;
        pNew->prior = pTail;
        pNew->next = NULL;
        pTail = pNew;
         
    }

    if(lengthl2 == lengthl1)
    {
        
        
        temp = p->data + q->data;
        pNode pNew =(pNode)malloc(sizeof(pNode));
        if(NULL == pNew)
            exit(1);
        pNew->data = temp;
        pTail->next = pNew;
        pNew->prior = pTail;
        pNew->next = NULL;
        pTail = pNew;       
    }
    else
    {
        
        if(num > 10)
            q->data++;
        
        pNode pNew =(pNode)malloc(sizeof(pNode));
        if(NULL == pNew)
            exit(1);
        pNew->data = q->data;
        pTail->next = pNew;
        pNew->prior = pTail;
        pNew->next = NULL;
        pTail = pNew;    
    }
    

    //翻转链表
    pNode pReverse = pHead;
    while(NULL != pReverse->next)
        pReverse = pReverse->next;
        
    
    pNode pHead2 = (pNode)malloc(sizeof(pNode));
        if(NULL == pHead)
            exit(1);
    pNode pTailnew = pHead2;
    pTailnew->prior = NULL;
    pTailnew->next = NULL;
    
    while(NULL != pReverse->prior)
    {
        pNode pNew2 =(pNode)malloc(sizeof(pNode));
        if(NULL == pNew2)
            exit(1);
        pNew2->data = pReverse->data;
        pTailnew->next = pNew2;
        pNew2->prior = pTailnew;
        pNew2->next = NULL;
        pTailnew = pNew2;

        pReverse = pReverse->prior;

    }
    return pHead2;
}



