/*
使用va函数来求一组数的最大值
*/

#include <stdio.h>
#include <stdarg.h>


int find_MAX(int a,...);


int main(void)
{
    int a;
    a = find_MAX(5,1,2,3,4,10);
    printf("%d\n",a); 

    return 0;
}


int find_MAX(int a,...)
{
    int i = 0;
    int temp;
    va_list ap;
    
    va_start(ap,a);
    int MAX = -99999999;
    for(i = 0;i < a; i++)
    {
        temp = va_arg(ap,int);
        if(temp > MAX)
            MAX = temp;
    }
    va_end(ap);
    return MAX;
}
