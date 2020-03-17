/*
    栈的应用举例
    
    使用栈来实现数制转换
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//栈节点
struct Node
{
    struct Node * pNext;
    int data;
    char * chardata;
};

//空栈
struct stack
{
    struct Node * pTop;
    struct Node * pBottom;
};


void init_stack(struct stack *);
void push_stack(struct stack *,int,char *);
void pop_stack(struct stack *,int);
void traverse_stack(struct stack *);
bool is_empty(struct stack *);
void clearall_stack(struct stack *);
void convert10to2(struct stack *,int);
void convert10to16(struct stack *,int);
int main(void)
{

    struct stack sta;
    init_stack(&sta);
    convert10to2(&sta,173);
    //convert10to16(&sta,7692);
    traverse_stack(&sta);
    return 0;
}



void init_stack(struct stack * sta)
{
    sta->pTop = (struct Node *)malloc(sizeof(struct Node));
    if(NULL == sta->pTop)
    {
        printf("Can not assigin the space for RAM!");
        exit(1);
    }
    
    sta->pBottom = sta->pTop;
    sta->pTop->pNext = NULL;
}


void push_stack(struct stack * sta,int val,char *  valchar)
{
    struct Node * pNew =(struct Node *)malloc(sizeof(struct Node));
    if(NULL == pNew)
    {
        printf("Can not assigin the space for RAM!");
        exit(1);
    }
    pNew->data = val;
    pNew->chardata = valchar;
    pNew->pNext = sta->pTop;
    sta->pTop = pNew;
}


void traverse_stack(struct stack * sta)
{
    struct Node * p = sta->pTop;
    while(sta->pBottom != p)
    {
        if(NULL != p->chardata)
            printf("%c\n",p->chardata);
        else
            printf("%d\n",p->data);
        p = p->pNext;
    }

}

void convert10to2(struct stack * sta,int val)
{
     if(!is_empty(sta))
        clearall_stack(sta);

     int binval = 0;
     while(0 != val)
     {
        binval = val % 2;
        val = val / 2;
        push_stack(sta,binval,NULL);
     }
    
}

void convert10to16(struct stack * sta,int val)
{
    int hexval = 0;
    if(!is_empty(sta))
        clearall_stack(sta);

    while(0 != val)
    {
        hexval = val % 16;
        val = val / 16;
        if(10 == hexval)
            push_stack(sta,hexval,'A');
        else if(11 == hexval)
            push_stack(sta,hexval,'B');
        else if(12 == hexval)
            push_stack(sta,hexval,'C');
        else if(13 == hexval)
            push_stack(sta,hexval,'D');
        else if(14 == hexval)
            push_stack(sta,hexval,'E');
        else if(15 == hexval)
            push_stack(sta,hexval,'F');
        else
            push_stack(sta,hexval,NULL);

    }

}





bool is_empty(struct stack * sta)
{
    if(sta->pTop == sta->pBottom)
        return true;
    return false;
}

void clearall_stack(struct stack *sta)
{
    struct Node * p = sta->pTop;
    struct Node * q;
    while(sta->pBottom != p)
    {
        q = p->pNext;
        free(p);
        p = q;
    }
    sta->pTop = sta->pBottom;
}


