/*
利用递归实现ackerman函数计算

定义:

           { n + 1;               m = 0,n > 0   
  A(m,n) = { A(m - 1,1);          n = 0,m > 0   
           { A(m - 1,A(m,n - 1))    n > 0,m > 0 


*/


#include <stdio.h>

int ackerman(int,int);


int main(void)
{

    printf("%d\n",ackerman(2,3));
    return 0;
}

int ackerman(int m,int n)
{
     if(m == 0)
        return n + 1;
    else if(n == 0)
        return ackerman(m -1,1);
    else
        return ackerman(m - 1,ackerman(m,n - 1));
}
