#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//插入的节点
struct Node
{
    int data;
    struct Node * pNext;
};


//栈节点
struct stack
{

    struct Node * pTop;
    struct Node * pBottom;
};


void init_stack(struct stack *);
void push_el(struct stack *,int data);
bool pop_el(struct stack *,int *);
void traverse_stack(struct stack *);
bool is_empty(struct stack *);
void clearall_stack(struct stack *);


int main(void)
{
    int a;
    struct stack sta;
    init_stack(&sta);
    push_el(&sta,1);
    push_el(&sta,2);
    push_el(&sta,3);
    //pop_el(&sta,&a);
    clearall_stack(&sta);
    traverse_stack(&sta);
    return 0;
}

//初始化一个栈
void init_stack(struct stack * sta)
{
    //为栈顶节点分配空间
    sta->pTop = (struct Node *)malloc(sizeof(struct Node));
    if(NULL == sta->pTop)
    {
        printf("Can not assign space for the sta->pTop");
        exit(1);
    }
    //空栈时，栈顶和栈底地址相同
    sta->pBottom = sta->pTop;
    //空栈时，栈顶的下一个节点地址NULL
    sta->pTop->pNext = NULL;
}

//压栈操作
void push_el(struct stack * sta,int data)
{
    //新建一个新的节点，并未新节点分配空间
    struct Node * pNew =(struct Node *)malloc(sizeof(struct Node));
    if(NULL == pNew)
    {
        printf("Can not assigon space for the pNew");
        exit(1);

    }
    pNew->data = data;
    //将新节点的下一个节点地址指向栈的头节点地址
    pNew->pNext = sta->pTop;
    //将新节点作为栈顶节点
    sta->pTop = pNew;
    //这时栈底节点的数据和pNext都为空
}

//判断栈是否为空
bool is_empty(struct stack * sta)
{
    //当栈顶节点的地址和栈底节点相同时，表示栈为空
    if(sta->pBottom == sta->pTop)
        return true;
    
    return false;
}

//从栈顶处弹出节点
bool pop_el(struct stack * sta,int * val)
{
    //判断栈是否为空
    if(is_empty(sta))
        return false;

    struct Node * p = sta->pTop;
    //*val用于提取出栈的值，可以根据需求添加
    *val = p->data;
    //把当前栈顶节点的下一个节点的地址作为栈顶的节点
    sta->pTop = p->pNext;
    //释放掉当前的栈顶节点
    free(p);
    p = NULL;
    return true;
}

//清空栈
void clearall_stack(struct stack * sta)
{   
    //检查栈是否为空
    if(is_empty(sta))
    {
        printf("Stack is empty!");
        exit(1);
    }
    
    struct Node * p = sta->pTop;
    struct Node * q = NULL;
    //循环的条件为当前栈顶节点是否和栈底节点相同
    while(sta->pBottom != p)
    {
        //临时节点q用来当前栈顶节点的下一个节点
        q = p->pNext;
        //释放当前的栈顶节点
        free(p);
        //将下一个栈顶节点赋给当前的栈顶节点
        p = q;
    }
    sta->pTop = sta->pBottom;
}



void traverse_stack(struct stack * sta)
{
    struct Node * p  = sta->pTop;
    while(sta->pBottom != p)
    {
        printf("%d\n",p->data);
        p = p->pNext;

    }
}

