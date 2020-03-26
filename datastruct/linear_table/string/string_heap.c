/*
使用堆分配存储来表示字符串


堆分配地址空间的优势：
1.不浪费空间
2.对于串长度没有限制
3.浪费较小
4.是比较理想的结构

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>



typedef struct heapString
{
    char * string;
    int len;

}hS;






//声明一个字符串
void StrAssign(struct heapString * st,char * strings);


int main(void)
{
    struct heapString st;
    StrAssign(&st,"ABCDEFGHIJK");

    printf("%s",st.string);
    return 0;

}



void StrAssign(struct heapString * st,char * strings)
{
    int i = 0;
    //先判断string的空间是否为空
    if(NULL != st->string)
        free(st->string);
    st->len = strlen(strings);
    st->string = (char *)malloc(sizeof(char) * (st->len));
    for(i = 0;i < st->len;i++)
    {
        st->string[i] = strings[i];
    }
}


