/*

使用链表来实现串

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

    //用户自定义块大小
#define CHUNK_SIZE 4

    struct Chunk
    {
        char ch[CHUNK_SIZE];    
        struct Chunk * pNext;

    };

    struct LString
    {
        struct Chunk * pHead;
        struct Chunk * pTail;
        int len;
    };



//初始化一个字符串
void StrAssigin(struct LString *,char *chars);
void StrPrint(struct LString *);
char * ToChars(struct LString *);
void StrCopy(struct LString *,struct LString *);
bool StrEmpty(struct LString *);
int StrCompare(struct LString *,struct LString *);
int StrLength(struct LString *);
void ClearString(struct LString *);
void Concat(struct LString *,struct LString *,struct LString *);
void SubString(struct LString *,struct LString *,int pos,int len);
int Index(struct LString *,struct LString * ,int pos);
struct LString StrInsert(struct LString *,int pos,struct LString *);
struct LString StrDelete(struct LString * S,int pos,int len);
void Replace(struct LString * ,struct LString *,struct LString*);


int main(void)
{
    char * chars;
    int val;
    struct LString S;
    struct LString T;
    struct LString V;
    StrAssigin(&S,"ABCABACGACBCGHHAHABC");
    StrAssigin(&T,"ABC");
    StrAssigin(&V,"GGG");
    Replace(&S,&T,&V);
    chars = ToChars(&S);

    printf("%s\n",chars);
    return 0;
}


void StrAssigin(struct LString * st,char * strings)
{
        int i = 0;
        int k = 0;
        st->len = strlen(strings);
        st->pHead = (struct Chunk *)malloc(sizeof(struct Chunk));
        if(NULL == st->pHead)
            exit(1);
         
        
        //当插入的字符串小于1个块的大小时的处理 
        for(k = 0;k < CHUNK_SIZE;k++)
        {
            //多余的部分用#号来填充
            if(k > strlen(strings) - 1)
            {
                st->pHead->ch[k] = '#';
            }
            else
                st->pHead->ch[k] = strings[k];    
        }
        st->pTail = st->pHead;
        st->pTail->pNext = NULL;

        //当插入字符串大于1个块的大小时的处理
        while(k < strlen(strings))
        {
            //开辟新的块空间
            struct Chunk * pNew = (struct Chunk *)malloc(sizeof(struct Chunk)); 
            if(NULL == pNew)
                exit(1);
            
            for(i = 0;i < CHUNK_SIZE;i++)
            {
                //多余部分用#号来填充
                if(k > strlen(strings) - 1)
                {
                    pNew->ch[i] = '#';
                }
                else
                {
                    pNew->ch[i] = strings[k];
                    k++;
                }
            }
            //常规链表操作
            st->pTail->pNext = pNew;
            pNew->pNext = NULL;
            st->pTail = pNew;
        }

}

char * ToChars(struct LString * st)
{
    int i = 0;
    int k = 0;
    //为字符串开辟内存空间，这里会开一个char,用于存放字符串结束符'\0'
    char * strings = (char * )malloc(sizeof(char) * st->len + 1);
    if(NULL == strings)
    {
        printf("Can not assign the space for strings!");
        exit(1);
    }
    struct Chunk * p = st->pHead;
    
    while(NULL != p->pNext)
    {
        
        for(i = 0;i < CHUNK_SIZE;i++)
        {
            strings[k] = *(p->ch+i);
            k++;
        }
        p = p->pNext;
    }

    for(i = 0;i < CHUNK_SIZE;i++)
    {   
        //发现填充符时，输出停止
        if(*(p->ch+i) == '#')
            break;
        strings[k] = *(p->ch+i);
        k++;
    }
    return strings;
}

//将st1串的内容复制到st2
void StrCopy(struct LString * st1,struct LString * st2)
{   
    //先将st1的内容转换为字符串
    char * strings  = ToChars(st1);
    //判断字符串是否存在
    if(!strings)
    {
        printf("Can not get any strings!");
        exit(1);
    }
    //将st1的字符串放入st2内
    StrAssigin(st2,strings);
    free(strings);
}


int StrCompare(struct LString * st1,struct LString * st2)
{
    int i,j,k,m;

    //字符串块1的大小
    int chunksize1 = st1->len / CHUNK_SIZE;
    //如果有余数，块大小 + 1;
    if(st1->len % CHUNK_SIZE)
        chunksize1++;
 
    //字符串块2的大小
    int chunksize2 = st2->len / CHUNK_SIZE;
    //如果有余数，块大小 + 1;
    if(st2->len % CHUNK_SIZE)
        chunksize2++;
    
    struct Chunk * p = st1->pHead;
    struct Chunk * q = st2->pHead;



    for(i = 0,j = 0;i < chunksize1 && j < chunksize2;i++,j++)
    {
        for(k = 0;k < CHUNK_SIZE;k++)
        {
            if(*(p->ch + k) != *(q->ch + k))
                return *(p->ch + k) - *(q->ch + k); 
            
        }
        
        if (NULL != p->pNext || NULL != q->pNext)
        {
            p = p->pNext;
            q = q->pNext;
        }

    }
    return *(p->ch + k) - *(q->ch + k); 
}           



void Concat(struct LString * T,struct LString * st1,struct LString * st2)
{
    //计算新串T的长度
    T->len = st1->len + st2->len;

    //将原串st1的头节点地址赋给新串T
    T->pHead = st1->pHead;
    T->pTail = st1->pTail;
    T->pTail->pNext = st2->pHead;

    /*
    其它写法:
    T->pHead = st1->pHead;
    st1->pTail->pNext = st2->pHead;
    T->pTail = st2->pTail;
    */
}


void SubString(struct LString * Sub,struct LString * T,int pos,int len)
{
    
    if(pos < 1 || pos > T->len || len < 1 || len > T->len || len + pos > T->len + 1)
    {
        printf("Out of range!");
        exit(1);
    }


    int i = 0;
    int k = 0;
    int j = pos - 1;
    char * c;
    //将主串T的转换成字符串c
    c = ToChars(T);
    if(!c)
    {
        printf("Can not find c!");
        exit(1);
    }
    

    //为串b分配空间，并将串C从POS位置开始长度len的字符复制到串b;
    char * b = (char *)malloc(sizeof(char) * len);
    if(NULL == b)
    {
        printf("Can not assign the space for b");
        exit(1);
    }
    
    for(i = 0;i < len;i++)
    {
        b[k] = c[j]; 
        j++;
        k++;
    }


    /*
        其它做法:
        //给串b的指针指向c的pos-1位置
        b = c + pos - 1;
        //将b的结束位置赋上0
        b[len] = '\0';
    */

    StrAssigin(Sub,b);
    free(b);
}


int Index(struct LString * T,struct LString * S,int pos)
{
     int i = pos;
     int lenS;
     int lenT;
     struct LString Sub;
     
    //提取出主串S的长度
    lenS = S->len;
    lenT = T->len;
    
    if(!lenS || !lenT)
    {
        printf("Can not get length from lenS or lenT!");
        exit(1);
    }
    
    //当POS + 1的值比剩余字符串大时，停止循环
    while(i <= lenS - lenT +1)
    {
       //获取在主串POS位置开始子串
       SubString(&Sub,S,i,lenT);

       //比较获取的子串和主串是否相同
       if(StrCompare(&Sub,T))
            i++;
       else
            return i;
    }

    return 0;
}



struct LString StrInsert(struct LString * S,int pos,struct LString * T)
{
    if(pos < 1 || pos > S->len)
    {
        printf("Wrong pos input!");
        exit(1);
    }

    int i,j;
    int x = pos - 1;
    //获取主串和子串的长度
    int lenS = S->len;
    int lenT = T->len;
    //起始移动的下标，由于字符串下标从0开始，所以最后一个字符串的位置为总长度-1
    int y = lenS - 1;
    //将字符原字符串向后移动的次数
    int movetimes = lenS - pos + 1;
    struct LString k;
    
    //将2个链表转换为字符串
    char * s = ToChars(S);
    char * t = ToChars(T);

    //重新分配主串S的空间来存放插入的内容
    s = (char *)realloc(s,sizeof(char) * (lenS + lenT+1));
    
    //为插入的字符串腾出空间
    for(i = 0;i < movetimes; i++)
    {
        s[y + lenT] = s[y];
        y--;
    }

    //为POS之前位置插入串T的内容
    for(i = 0;i < lenT;i++)
    {
        s[x] = t[i];
        x++;
    }
    
    StrAssigin(&k,s);
    free(s);
    free(t);
    return k;
}


struct LString StrDelete(struct LString * S,int pos,int len)
{
    if(pos < 1 || pos > S->len || len < 1 || len > S->len || pos + len > S->len + 1)
    {
        printf("Wrong pos or len set!");
        exit(1);
    }

    char * c;
    int i = 0;
    int lenS = S->len;
    struct LString k;
    
    //串S剩余字符串移动的次数
    int movetimes = (lenS - len) - (pos - 1);

    int moveSp = pos + len - 1;
    int moveEp = pos - 1;

    //将原串S转换为字符串
    c = ToChars(S);

    for(i = 0;i < movetimes;i++)
    {
        c[moveEp] = c[moveSp];
        moveEp++;
        moveSp++;
    }

    //截断多余字符串
    c[lenS - len] = '\0';
    StrAssigin(&k,c);
    
    free(c);
    return k;

}

//在S串中找到T串并替换为串V
void Replace(struct LString * S,struct LString * T,struct LString * V)
{
    //记录每一次pos的值
    int i = 1;

    do{
         i = Index(T,S,i);
         if(!i)
            break;
        *S = StrDelete(S,i,T->len);
        
        //这个if用于修复在末尾插入无法插入的问题
        if(i == S->len + 1)
        {
            S->len++;
            *S = StrInsert(S,i,V);
        }
        else
        {
            *S = StrInsert(S,i,V);
        }
        i = i + V->len - 1;
         
    }while(i);
    
}


void StrPrint(struct LString * st)
{
   struct Chunk * p = st->pHead;
   int i = 0;
   while(NULL != p->pNext) 
   { 
        for(i = 0;i < CHUNK_SIZE;i++)
        {
            printf("%c",p->ch[i]);
        }
        p = p->pNext;
   }
   for(i = 0;i < CHUNK_SIZE;i++)
   {
      printf("%c",p->ch[i]);
   }
}
