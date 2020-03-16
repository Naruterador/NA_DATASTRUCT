/*
栈实现括号检测:

检验括号匹配的方法，就是对给定的字符串依次检验：若是左括号，入栈；若是右括
号，出栈一个左括号判断是否与之相匹配；是其它字符，不检验。检验到字符串尾，还要
检查栈是否空。只有栈空，整个字符串才匹配完。


情况分析:
1.[ABCDEFG]
2.ABCD[EFG]
3.A[BCD][EFG]
4.AB[[CD]EFG]
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    char character;
    struct Node * pNext;



} * pNode;

typedef struct stackce
{

    pNode pTop;
    pNode pBottom;

} * stack;





void init_stack(stack);
void push_stack(stack,char);
bool pop_stack(stack);
bool is_empty(stack);
void traverse_stack(stack);
void check_bracker(stack,char * );
void clearall_stack(stack);


int main(void)
{
    struct stackce sta;
    init_stack(&sta);
    //push_stack(&sta,'a');
    //push_stack(&sta,'b');
    //push_stack(&sta,'c');
    //clearall_stack(&sta);
    //pop_stack(&sta);
    check_bracker(&sta,"{[(5-2)*(7-3)+2]*4+8}*6");
    //traverse_stack(&sta);
    return 0;
}

void init_stack(stack sta)
{
    sta->pTop = (pNode)malloc(sizeof(struct Node));
    if(NULL == sta->pTop)
    {
        printf("Can not assign the space for the sta->pTop!");
        exit(1);
    }
    sta->pBottom = sta->pTop;
    sta->pTop->pNext = NULL;
}

void push_stack(stack sta,char charval)
{
    pNode pNew =(pNode)malloc(sizeof(struct Node));
    if(NULL == pNew)
    {
        printf("Can not assigin the space for the pNew");
        exit(1);
    }
    pNew->character = charval;
    pNew->pNext = sta->pTop;
    sta->pTop = pNew;
}


bool pop_stack(stack sta)
{
    
    if(is_empty(sta))
        return false;

    pNode p = sta->pTop;
    sta->pTop = p->pNext;
    free(p);
    p = NULL;
}







void traverse_stack(stack sta)
{
    pNode p = sta->pTop;
    while(sta->pBottom != p)
    {
        printf("%c\n",p->character);
        p = p->pNext;
    }

}

bool is_empty(stack sta)
{
    if(sta->pBottom == sta->pTop)
        return true;
    return false;
}



void clearall_stack(stack sta)
{
    pNode p = sta->pTop;
    pNode q;
    while(sta->pBottom != p)
    {
        q = p->pNext;
        free(p);
        p = NULL;
        p = q;
    }
    sta->pBottom = sta->pTop;
}


void check_bracker(stack sta,char * strings)
{
    int i = 0;
    int j = 0;
    char currentchar;
    while(strings[i] != '\0')
    {
        if('(' == strings[i] || '[' == strings[i] || '{' == strings[i])
        {
            push_stack(sta,strings[i]);
            j = i;
            currentchar = strings[i];
        }
        
        if(')' == strings[i] || ']' == strings[i] || '}' == strings[i])
        {
            pop_stack(sta);
        }   
        i++;
    }
    if(is_empty(sta))
    {
        printf("ALL Matched!");

    }
    else
        printf("Miss the %c with %d position.",currentchar,j);
}



