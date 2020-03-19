/*
通过栈来实现一个简单的计算器

使用栈完成计算一个表达式的结果:
7 * 2 * 2 - 5 + 1 - 5 + 3 - 4  = ?

思路:
1.创建2个链表，1个链表用来放数字，一个链表用来放符号
2.遍历整个表达式，如果发现是一个数字，就进入数字栈，如果发现是符号就进入符号栈

3.如果发现当前符号栈为空，就直接入栈
3.1 如果发现当前符号栈有符号，就进行比较，如果当前的操作符优先级小于或等于栈中的操作符，就将当前数字栈中的数字出栈，并进行运算，将得到的结果圧入数字栈，并将当前的符号圧如符号栈
3.2 如果当前的操作符优先级大于栈中的操作符，就直接入符号栈。

4.当表达式遍历完毕之后，就从数字栈和符号栈中POP出相应的数和符号，进行运算。
5.最后在数字栈只有一个数字，就是表达式的结果。


*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
//数据节点
typedef struct dataNode
{

    int data;
    struct dataNode * pNext;

} * dNode;

//符号节点
struct sign
{
    char sign;
    int priority;
};


typedef struct signNode
{
    struct sign csign;
    struct signNode * pNext;


} * sNode;

//数据栈
typedef struct dataStack
{
    dNode pTop;
    dNode pBottom;

} * dStack;

//符号栈
typedef struct signStack
{
    sNode pTop;
    sNode pBottom;

} * sStack;

void create_datastack(dStack);
void create_signstack(sStack);
void push_datastack(dStack,int data);
void push_signstack(sStack,char sign,int priority);
int pop_datastack(dStack);
struct sign pop_signstack(sStack);
bool is_dataempty(dStack);
bool is_signempty(sStack);
void traverse_datastack(dStack);
void traverse_signstack(sStack);
void Precede(dStack,sStack,char * strings);
int prioritycheck(char);



int main(void)
{
    struct dataStack dsta;
    struct signStack ssta;
    create_datastack(&dsta);
    create_signstack(&ssta);
    Precede(&dsta,&ssta,"100X100+1-10");
    return 0;
}


void create_datastack(dStack dsta)
{
    dsta->pTop =(dNode)malloc(sizeof(struct dataNode));
    if(NULL == dsta->pTop)
    {
        printf("Can not assign the space for dsta->pTop");
        exit(1);
    }
    dsta->pBottom = dsta->pTop;
    dsta->pTop->pNext = NULL;
}

void create_signstack(sStack ssta)
{

    ssta->pTop =(sNode)malloc(sizeof(struct signNode));
    if(NULL == ssta->pTop)
    {
        printf("Can not assign the space for ssta->pTop");
        exit(1);
    }
    ssta->pBottom = ssta->pTop;
    ssta->pTop->pNext = NULL;
}

void push_datastack(dStack dsta,int data)
{
    dNode pNew =(dNode)malloc(sizeof(struct dataNode));
    if(NULL == pNew)
    {
        printf("Can not assign the space for pNew");
        exit(1);
    }
    
    pNew->data = data;
    pNew->pNext = dsta->pTop;
    dsta->pTop = pNew;
}

void push_signstack(sStack ssta,char sign,int priority)
{
    sNode pNew = (sNode)malloc(sizeof(struct signNode));
    if(NULL == pNew)
    {
        printf("Can not assign the space for spNew");
        exit(1);
    }
    
    pNew->csign.sign = sign;
    pNew->csign.priority = priority;
    pNew->pNext = ssta->pTop;
    ssta->pTop = pNew;
}

int pop_datastack(dStack dsta)
{
    
    int data = 0;
    dNode p = dsta->pTop;
    dsta->pTop = p->pNext;
    data = p->data;
    free(p);
    p = NULL;
    return data;
}

struct sign pop_signstack(sStack ssta)
{
    sNode p = ssta->pTop;
    ssta->pTop = p->pNext;
    struct sign popsign = p->csign;
    free(p);
    p = NULL;
    return popsign;
}




int prioritycheck(char s)
{
    if('+' == s || '-' == s)
        return 1;
    else if('X' == s || '/' == s)
        return 2;

    return 0;
}


void Precede(dStack dsta,sStack ssta,char * strings)
{
    int i = 0;
    int a = 0;
    int b = 0;
    int temp = 0;
    int r = 0;
    char * nums = (char *)malloc(sizeof(char) * 10);
    char tempadd;
    int add = 0;
    int n = 0;
    while('\0' != strings[i])
    {
          
        if(isdigit(strings[i]))
        {   
            
            tempadd = strings[i];
            //这里直接用&strings会出现异常结果
            temp = atoi(&tempadd);
            if(0 == n)
                add = temp;
            else
                add = add * 10 + temp;
            n++;
            
            if('X' == strings[i + 1] || '/' == strings[i + 1] || '+' == strings[i + 1] || '-' == strings[i + 1] || '\0' == strings[i + 1])
            {
                push_datastack(dsta,add);
                add = 0;
                n = 0;
               
            }
        }   

        if(is_signempty(ssta) && ('X' == strings[i] || '/' == strings[i] || '+' == strings[i] || '-' == strings[i]))
        {
                push_signstack(ssta,strings[i],prioritycheck(strings[i]));
        }else{
            if((prioritycheck(strings[i]) <= ssta->pTop->csign.priority) && ('X' == strings[i] || '/' == strings[i] || '+' == strings[i] || '-' == strings[i]))
            {

                b = pop_datastack(dsta);
                a = pop_datastack(dsta);
                if('+' == ssta->pTop->csign.sign)
                    r = a + b;
                else if('-' == ssta->pTop->csign.sign)
                    r = a - b;
                else if('X' == ssta->pTop->csign.sign)
                    r = a * b;
                else if('/' == ssta->pTop->csign.sign)
                    r = a / b;

                push_datastack(dsta,r);
                pop_signstack(ssta);
                push_signstack(ssta,strings[i],prioritycheck(strings[i]));
            }
            if((prioritycheck(strings[i]) > ssta->pTop->csign.priority) && ('X' == strings[i] || '/' == strings[i] || '+' == strings[i] || '-' == strings[i]))
            {  
            
                push_signstack(ssta,strings[i],prioritycheck(strings[i]));
            }

        }
        i++;

    }
    
    if(is_signempty(ssta))
    {
        r = pop_datastack(dsta);
        printf("%d\n",r);
    }else{
        sNode p = ssta->pTop;
        dNode q = dsta->pTop;
        while(ssta->pBottom != p)
        {
            b = pop_datastack(dsta);
            a = pop_datastack(dsta);
            if('+' == p->csign.sign)
                r = a + b;
            else if('-' == p->csign.sign)
                r = a - b;
            else if('X' == p->csign.sign)
                r = a * b;
            else if('/' == p->csign.sign)
                r = a / b;
            push_datastack(dsta,r);
            p = p->pNext;
        }
        printf("%d\n",pop_datastack(dsta));
    }
}


bool is_dataempty(dStack dsta)
{
    if(dsta->pBottom == dsta->pTop)
        return true;
    return false;
}

bool is_signempty(sStack ssta)
{
    if(ssta->pBottom == ssta->pTop)
        return true;
    return false;

}


void traverse_datastack(dStack dsta)
{
    dNode p = dsta->pTop;
    while(dsta->pBottom != p)
    {
        printf("%d\n",p->data);
        p = p->pNext;

    }

}

void traverse_signstack(sStack ssta)
{

    sNode p = ssta->pTop;
    while(ssta->pBottom != p)
    {
        printf("%c  %d\n",p->csign.sign,p->csign.priority);
        p = p->pNext;
    }

}
