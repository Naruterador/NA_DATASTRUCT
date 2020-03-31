# C语言中va函数的介绍
<pre>

VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数 
——摘自百度百科 
va_list 是一个字符指针，在代码中可以理解为指向当前参数的一个指针，这里有几个与 va_list 相关的常见的函数

void va_start ( va_list ap, param );
//对va_list变量进行初始化，将ap指针指向参数列表中的第一个参数
type va_arg ( va_list ap, type ); 
//获取参数，类型为 type 类型，返回值也为 type 类型
int vsprintf(char *string, char *format, va_list ap);
//将ap(通常是字符串) 按format格式写入字符串string中
void va_end ( va_list ap ); 
//回收ap指针

所以解决变参问题就分为四步：

（1）首先在函数里定义 va_list 型的变量 ap，即指向参数的指针；
（2）然后用 va_start 函数初始化刚定义的 ap 指针；
（3）然后用 va_arg 返回可变的参数即 va_arg(va_list ap, type)
（4）最后用 va_list 回收 va_list 指针

eg.：求多个数的最大值：

code：

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
int Max(int ss, ...){
    va_list ap;
    int ret = -999999, tmp;
    va_start(ap, ss);
    for(int i=0; i<ss; i++){
        tmp = va_arg(ap, int);
        if(ret < tmp)
            ret = tmp;
    }
    va_end(ap);
    return ret;
}
int main()
{
    int cnt = 5;
    printf("%d\n",Max(cnt, 2, 3, 4, 5, 6));
    return 0;
}

</pre>
        '''
            其他说明：va_list初始话的ap值，只会对应...所赋的值。    
        '''