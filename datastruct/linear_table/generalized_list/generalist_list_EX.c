/*

广义表的扩展线性链表存储结构

*/
#if defined(__caplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

#include "mystring.h"



typedef char AtomType;

//广义表头尾链表存储结构
enum ElemTag{ATOM,LIST};    //创建一个枚举ATOM表示单一原子，LIST表示子表

typedef struct GLNode
{
    enum ElemTag tag;    //广义表的元素类型，是原子或者一个子表
    union
    {
        AtomType atom; //原子节点的值域
        //广义表的头节点指针,广义表的尾节点指针
        struct 
        {
            struct GLNode * hp;
            
        }ptr; 
        
    }a;
    struct GLNode * tp;
}* GList,GLNode;

void server(SString,SString);
void InitGlist(GList *);
void CreateGlist(GList *,SString);
int  GListLength(GList);
int  GListDeep(GList);
void CopyGList(GList *,GList);
GList GetHead(GList);
GList GetTail(GList);
void Traverse_GL(GList);



int main(void)
{
    int len;
    int deep;
    GList G;
    GList E;
    InitGlist(&G);
    SString S;
    StrAssign(S,"(a,(b,c,d))");
    CreateGlist(&G,S);
    E = GetTail(G); 
    Traverse_GL(E);
    //len = GListLength(G);
    //printf("%d",StrLength(S));
    return 0;
}

void server(SString str,SString hstr)
{
    int i;
    int n;
    int k;
    SString ch;
    SString c1;
    SString c2;
    SString c3;
    SString temp;  
    StrAssign(c1,",");
    StrAssign(c2,"(");
    StrAssign(c3,")");
    
    n = StrLength(str);
    SubString(ch,str,1,1);
     
    //hstr保存第一个','号前的值，str用于保存第一个','后的值
    for(i = 1,k = 0;(i <= n && (StrCompare(ch,c1))) || k!=0;i++)
    {
        SubString(ch,str,i,1);
        //用于抓取广义:表中的括号
        if(!StrCompare(ch,c2))
            k++;
        else if(!StrCompare(ch,c3))
            k--;
    }
    
    if(i <= n)
    {
        //获取第一个','号前的值
        SubString(hstr,str,1,i-2);
        //获取第一个','号后面的值
        SubString(temp,str,i,n - i + 1);
        ClearString(str);
        StrCopy(str,temp);
    }
    else
    {
        //如果i的值大于表达式的总长度，表示没有子串，那么就将str就是hstr
        StrCopy(hstr,str);
        ClearString(str);
    }
}

void InitGlist(GList * G)
{
    *G = NULL;
}



void CreateGlist(GList * G,SString S)
{
    SString sub;
    SString hs;
    SString emp;
    GList p;
    StrAssign(emp,"()");
    *G = (GList)malloc(sizeof(struct GLNode));
    if(NULL == *G)
    {
        printf("ERROR:can not assign the space for G!");
        exit(1);
    }
    
    if(!StrCompare(S,emp))
    {
        (*G)->tag = LIST;
        (*G)->a.ptr.hp = NULL;
        (*G)->tp = NULL;
    }
    else if(1 == StrLength(S))
    {
        (*G)->tag = ATOM;
        (*G)->a.atom = S[1];
        (*G)->tp = NULL;
    }
    else
    {

        (*G)->tag = LIST;
        (*G)->tp = NULL;
        SubString(sub,S,2,StrLength(S) - 2);
        server(sub,hs);
        CreateGlist(&(*G)->a.ptr.hp,hs);
        p =(*G)->a.ptr.hp;

            
        while(!StrEmpty(sub))
        {    
            server(sub,hs);
            CreateGlist(&p->tp,hs);
            p = p->tp;
        }

    }
}


int  GListLength(GList G)
{
    int i = 0;
    GList p = G->a.ptr.hp;
    while(p)
    {
        i++;
        p = p->tp;
        

    }
    return i;
}



int  GListDeep(GList G)
{
    GList p;
    int max;
    int deep;

    if(NULL == G || (NULL == G->a.ptr.hp && G->tag == LIST))
        return 1;

    if(G->tag == ATOM)
        return 0;

    for(max = 0,p = G->a.ptr.hp;p;p = p->tp)
    {
       
       deep = GListDeep(p);
       
       if(deep > max)
        max = deep;
    }
    return max + 1;
}

//将广义表B复制到广义表A
void CopyGList(GList * A,GList B)
{
    *A = NULL;
    if(B)
    {
        *A = (GList)malloc(sizeof(struct GLNode));
        if(NULL == *A)
        {
            printf("ERROR:can not assign the space for B");
            exit(1);
        }
        (*A)->tag = B->tag;
        
        if((B)->tag == ATOM)
            (*A)->a.atom = B->a.atom;
        else
            CopyGList(&(*A)->a.ptr.hp,B->a.ptr.hp);
        
        
        if(NULL != (*A)->tp)
           CopyGList(&(*A)->tp,B->tp);
        else
          (*A)->tp = B->tp;
    }
}


GList GetHead(GList G)
{
    GList h;
    GList p;
    
    if(NULL == G)
        h = NULL;
    else
        p = G->a.ptr.hp->tp;
        G->a.ptr.hp->tp = NULL;
        CopyGList(&h,G->a.ptr.hp);
        G->a.ptr.hp->tp = p;
    return h;

}


GList GetTail(GList G)
{
    GList p;
    GList t;
    
    if(NULL == G || (G->tag == LIST && NULL == G->a.ptr.hp))
        return NULL;
    
    p = G->a.ptr.hp;
    G->a.ptr.hp = p->tp;
    CopyGList(&t,G);
    G->a.ptr.hp = p;


    return t;

}









void Traverse_GL(GList G)
{
    GList p;
    char a;
    
    if(G)
    {
        if(G->tag == ATOM)
        {
            a = G->a.atom;
            printf("%c",a);
            p = NULL;
        }
        else
        {
            p = G->a.ptr.hp;
        }
        Traverse_GL(p);
        Traverse_GL(G->tp);

    }
}
