/*

广义表的实现

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
            struct GLNode * tp;
        }ptr; 
    }a;

}* GList,GLNode;


//广义表输入字符串处理函数
void server(SString str,SString hstr);
//初始化广义表
void InitGList(GList *);
//创建广义表
void CreateGList(GList *,SString str);
//销毁广义表
void DestroyGList(GList *);
//复制广义表
void CopyGList(GList *,GList);
//返回广义表的长度
int GListLength(GList);
//返回广义表的深度
int GListDepth(GList);
//判断广义表是否为空
bool is_empty(GList);
//获取广义表的表头
GList GetHead(GList);
//获取广义表的表尾
GList GetTail(GList);
//向广义表中插入结点
void InsertFirst(GList *,GList);
//删除广义表中的结点
void DeleteFirst(GList *,GList *);
//利用递归算法遍历广义表
void Traverse_GL(GList);

int main(void)
{
    int len;
    int dep;
    GList G;
    GList G1;
    SString str;
    SString hstr;
    StrAssign(str,"(a,(b,c,d))");
    InitGList(&G);
    CreateGList(&G,str);
    len = GListLength(G);
    dep = GListDepth(G);
    //CopyGList(&G1,G);
    GLNode e;
    GList E;
    
    e.tag = ATOM;
    e.a.atom = 'f';
    InsertFirst(&G,&e);
    DeleteFirst(&G,&E);
    //printf("%c",G1->a.ptr.hp->a.atom);
    Traverse_GL(E);
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
        //用于抓取广义表中的括号
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



void InitGList(GList * G)
{

    *G = NULL;

}


void CreateGList(GList * G,SString expression)
{
    int len;
    len = StrLength(expression);
    GList p;
    GList q;
    SString S;
    SString sub;
    SString hsub;
    SString temp;
    StrAssign(S,"()");
    
    if(!StrCompare(S,expression))   //判断是不是空表
        *G = NULL;
    else
    {
        *G =(GList)malloc(sizeof(struct GLNode)); //为广义表的结点分配空间
        if(NULL == *G)
        {
            printf("ERROR:Can not assign the space for GList");
            exit(1);
        }
        if(1 == len) //判断广义表长度是否为1，如果为1表示只有1个值，就直接创建1个结点
        {
            (*G)->tag = ATOM;
            (*G)->a.atom = expression[1];
        }else{
            (*G)->tag = LIST; //创建1个子表
            p = *G;
            SubString(sub,expression,2,len - 2); //删除表达式两边的括号，只取中间值
            do
            {
                server(sub,hsub); 
                CreateGList(&p->a.ptr.hp,hsub); //递归创建新的结点
                q = p;
                if(!StrEmpty(sub)) //判断表是否结束
                {
                    p = (GLNode *)malloc(sizeof(struct GLNode));
                    if(NULL == p)
                    {
                        printf("ERROR: can not assign the space for p!");
                        exit(1);
                    }
                    p->tag = LIST;
                    q->a.ptr.tp = p;
                }
                }while(!StrEmpty(sub));
                q->a.ptr.tp = NULL;
        }

    }

}

//由广义表S赋值到广义表D
void CopyGList(GList * D,GList S)
{
    
    if(!S)
        D = NULL;
    else
        {
            (*D) = (GList)malloc(sizeof(struct GLNode));
            if(*D == NULL)
            {
                printf("ERROR:can not assign the space for *D");
                exit(1);
            }
            (*D)->tag = S->tag;
            if(S->tag == ATOM)
                (*D)->a.atom = S->a.atom;
            else{
                CopyGList(&(*D)->a.ptr.hp,S->a.ptr.hp); 
                CopyGList(&(*D)->a.ptr.tp,S->a.ptr.tp);
            }


        }
}


int GListLength(GList G)
{
    int i = 0;
    while(G)
    {
        G = G->a.ptr.tp;
        i++;
    }

    return i;

}




int GListDepth(GList G)
{
    int dep;
    int max;
    GList p;
    if(!G)
        return 1;
    if(G->tag == ATOM)
        return 0;
    for(max = 0,p = G;p;p = p->a.ptr.tp)
    {
        dep = GListDepth(p->a.ptr.hp);
        if(dep > max)
            max = dep;
    }
    return max + 1;

}



GList GetHead(GList G)
{
    GList p;
    GList h;
    
    if(!G)
        return NULL;
    
    p = G->a.ptr.hp;
    CopyGList(&h,p);
    return h;
}



GList GetTail(GList G)
{
    GList t;
    if(!G)
        return NULL;

    CopyGList(&t,G->a.ptr.tp);
    
    return t;
}



void Traverse_GL(GList G)
{
    if(G)
    {
        if(G->tag == ATOM)
            printf("%c",G->a.atom);
        else
            {
                Traverse_GL(G->a.ptr.hp);
                Traverse_GL(G->a.ptr.tp);
            }
    }
}


bool is_empty(GList G)
{
    if(NULL == G)
        return true;
    else
        return false;
}


void DestroyGList(GList * G)
{
    GList qh;
    GList qt;
    
    if((*G)->tag == LIST)
    {
        qh = (*G)->a.ptr.hp;
        qt = (*G)->a.ptr.tp;
        DestroyGList(&qh);
        DestroyGList(&qt);
    }
    free(*G);
    *G = NULL;
}

//将结点e插入广义表A，也可以插入子表,插入的结点或者子表作为第一元素
void InsertFirst(GList * A,GList E)
{
    
    GList p;
    p = (GList)malloc(sizeof(struct GLNode));
    
    if(NULL == p)
    {
        printf("ERROR:can not assign the space for p");
        exit(1);
    }
    
    p->tag = LIST;
    p->a.ptr.hp = E;
    p->a.ptr.tp = *A;
    *A = p;
}


//删除广义表A的第一个元素，并用E返回其值
void DeleteFirst(GList * A,GList * E)
{
    GList p;

    p = *A;
    *E = (*A)->a.ptr.hp;
    *A = (*A)->a.ptr.tp;
    free(p);
    








}


