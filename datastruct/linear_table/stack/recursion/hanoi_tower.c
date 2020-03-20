/*
汉诺塔的递归实现:

*/
#include <stdio.h>
void hanio(int n,char A,char B,char C);


int main(void)
{


    hanio(3,'A','B','C');

    return 0;

}


void hanio(int n,char A,char B,char C)
{
    if (n == 1)
        printf("move No:%d from  %c ------> %c\n",n,A,C);
    else{
        hanio(n - 1,'A','C','B');
        printf("move No:%d from  %c ------> %c\n",n,A,C);
        hanio(n - 1,'B','A','C');
    }
}
