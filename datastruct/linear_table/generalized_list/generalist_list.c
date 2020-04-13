/*

广义表的实现

*/
#include <stdlib.h>
#include "mystring.h"
#include <stdbool.h>

typedef char AtomType;

//广义表头尾链表存储结构
enum ElemTag{ATOM,LIST};    //创建一个枚举ATOM表示单一原子，LIST表示子表

typedef struct GLNode
{
    enum ElemTag tag;    //广义表的元素类型，是原子或者一个子表
    union
    {
        AtomType atom; //原子节点的值域

        struct GLNode *hp; //广义表的头节点指针
        struct GLNode *tp; //广义表的尾节点指针
    }ptr;

}* GList,GLNode;



//广义表的扩展线性链表存储表示
typedef struct GLNode1
{
    enum ElemTag tag;   //广义表节点类型
    union
    {
        AtomType atom;
        struct GLNode1 * hp;
    }ptr;

    struct GLNode1 * tp;
}* GList1,GLNode1;


//广义表输入字符串处理函数
void server(SString str,SString hstr);
//初始化广义表
void InitGList(GList);
//创建广义表
void CreateGList(GList,SString str);
//销毁广义表
void DestroyGList(GList);
//复制广义表
void CopyGList(GList,GList);
//返回广义表的长度
void GListLength(GList);
//返回广义表的深度
void GListDepth(GList);
//判断广义表是否为空
bool is_empty(GList);
//获取广义表的表头
GList1 GetHead(GList);
//获取广义表的表尾
GList1 GetTail(GList);
//向广义表中插入结点
void InsertFirst(GList,GList);
//删除广义表中的结点
void DeleteFirst(GList,GList);
//利用递归算法遍历广义表
void Traverse_GL(GList,void(*v)(AtomType));

int main(void)
{
    GList G;
    SString str;
    SString hstr;
    StrAssign(str,"(a,(b,c,d))");
    InitGList(G);
    CreateGList(G,str);
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



void InitGList(GList G)
{

    G = NULL;

}


void CreateGList(GList G,SString expression)
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
        G = NULL;
    else
    {
        G =(GList)malloc(sizeof(struct GLNode1)); //为广义表的结点分配空间
        if(NULL == G)
        {
            printf("ERROR:Can not assign the space for GList1");
            exit(1);
        }
        if(1 == len) //判断广义表长度是否为1，如果为1表示只有1个值，就直接创建1个结点
        {
            G->tag = ATOM;
            G->ptr.atom = S[1];
        }else{
            G->tag = LIST; //创建1个子表
            p = G;
            SubString(sub,expression,2,len - 2); //删除表达式两边的括号，只取中间值
            do
            {
                server(sub,hsub); 
                CreateGList(p->ptr.hp,hsub); //递归创建新的结点
                q = p;
                if(!StrEmpty(sub)) //判断表是否结束
                {
                    p = (GList)malloc(sizeof(struct GLNode1));
                    if(NULL == p)
                    {
                        printf("ERROR: can not assign the space for p!");
                        exit(1);
                    }
                    p->tag = LIST;
                    q->ptr.tp = p;
                }
                }while(!StrEmpty(sub));
                q->ptr.tp = NULL;
        }

    }

}
