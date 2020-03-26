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

int main(void)
{

    struct LString st;
    StrAssigin(&st,"ABCDA");
    StrPrint(&st);
    

    return 0;
}



void StrAssigin(struct LString * st,char * strings)
{
        int i = 0;
        int k = 0;
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
