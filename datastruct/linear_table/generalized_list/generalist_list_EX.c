/*

广义表的扩展线性链表存储结构

*/


#include "mystring.h"

typedef char AtomType;
enum ElemTag {ATOM,LIST};

typedef struct GLNode
{

    enum ElemTag tag;
    union
    {
        AtomType atom;
        struct GLNode * hp;
    }ptr;
    
    struct GLNode * tp;
}* GList;

void server(SString,SString);
void InitGlist(GList);
void CreateGlist(GList,SString);
int  GlistLength(GList);


int main(void)
{
    int len;
    GList G;
    InitGlist(G);
    SString S;
    StrAssign(S,"(a,b,b,d,e)");
    CreateGlist(G,S);
    len = GlistLength(G);
    printf("%d",len);

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

void InitGlist(GList G)
{
    G = NULL;
}



void CreateGlist(GList G,SString S)
{
    SString sub;
    SString hs;
    SString emp;
    GList p;
    StrAssign(emp,"()");
    G = (GList)malloc(sizeof(struct GLNode));
    if(NULL == G)
    {
        printf("ERROR:can not assign the space for G!");
        exit(1);
    }
    
    if(!StrCompare(S,emp))
    {
        G->tag = LIST;
        G->ptr.hp = NULL;
        G->tp = NULL;
    }else{
        if(1 == StrLength(S))
        {
            G->tag = ATOM;
            G->ptr.atom = S[1];
            G->tp = NULL;
        }else{

            G->tag = LIST;
            G->tp = NULL;
            SubString(sub,S,2,StrLength(S) - 2);
            server(sub,hs);
            CreateGlist(G->ptr.hp,hs);
            p = G->ptr.hp;

            
            while(!StrEmpty(sub))
            {    
                server(sub,hs);
                CreateGlist(p->tp,hs);
                p = p->tp;
            }

        }

    }

}






int  GlistLength(GList G)
{
    int i = 0;
    GList p = G->ptr.hp;
    while(p || G->tag == LIST)
    {
        i++;
        p = p->tp;
        

    }
    return i;
}
