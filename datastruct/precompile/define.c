
/*

#define           定义一个预处理宏
#undef            取消宏的定义

#if               编译预处理中的条件命令，相当于C语法中的if语句
#ifdef            判断某个宏是否被定义，若已定义，执行随后的语句
#ifndef           与#ifdef相反，判断某个宏是否未被定义
#elif             若#if, #ifdef, #ifndef或前面的#elif条件不满足，则执行#elif之后的语句，相当于C语法中的else-if
#else             与#if, #ifdef, #ifndef对应, 若这些条件不满足，则执行#else之后的语句，相当于C语法中的else
#endif            #if, #ifdef, #ifndef这些条件命令的结束标志.
defined         　与#if, #elif配合使用，判断某个宏是否被定义

*/


#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


//常量定义
#define MAX_LENGTH 100
//通用标识
#define SLog printf
//预编译宏
#define _DEBUG


//最小函数值
#define MIN(a,b) ((a) > (b) ? (a) : (b))

//安全释放内存函数
#define SAFE_DELETE(p) {if(NULL != p){delete p;p = NULL;}}





int main(void)
{
    


    return 0;


}