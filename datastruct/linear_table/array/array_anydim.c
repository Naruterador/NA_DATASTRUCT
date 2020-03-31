/*
实现任意维的数组

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//这个模块用于使用va系列函数
#include <stdarg.h>




//定义数组的最大维度为8
#define MAX_ARRAY_DIM 8


struct Array
{
    //每个元素的指针
    int * base;
    
    //维度
    int dim;

    //维度的基地址
    int * bounds;

    //数组映像函数地址
    int * constants;
};


//初始化一个N维数组
void InitArray(struct Array *,int dim,...);
//销毁一个数组
void DestroyArray(struct Array *);
//求出元素在数组中的相对地址，用off来表示
void Locate(struct Array *,va_list ap,int * off);
//变量e被赋值为数组相应的元素值
void Value(int * e,int * off,struct Array *,...);
//将变量e的值赋值给元素地址
void Assign(struct Array *,int * off,int e,...);


int main(void)
{
    struct Array array;
    int dim = 2;
    int bounds1 = 2;
    int bounds2 = 2;
    int e;
    int testelement;
    int off = 0;
    //申明一个2X2的数组
    InitArray(&array,dim,bounds1,bounds2);
    
    int i;
    int j;
 
    printf("数组的bounds为:");
    for(i = 0;i < dim;i++)
    {
        printf("%d ",*(array.bounds + i));
    }
    printf("\n");
    printf("数组的contants值为:");
    for(i = 0;i < dim;i++)
    {
        printf("%d ",*(array.constants + i));
    }
    printf("\n");

    //给每一位数组元素赋值
    for(i = 0;i < 2;i++)
    {    
        for(j = 0;j < 2;j++)
        {    
            e = i * 10 + j;
            Assign(&array,&off,e,i,j);
            Value(&testelement,&off,&array,i,j);
            printf("array[%d][%d] = %d ",i,j,testelement);
        }
        printf("\n");
    }
    
    //每个数组的值按顺序输出
    for(i = 0;i < bounds1*bounds2;i++)
    {
        printf("%d ",*(array.base + i));
    }

    
    return 0;
}



void InitArray(struct Array * array,int dim,...)
{
    //用于存放元素总个数
    int elementtotal;

    int i = 0;
    //AP用于申明每个维度的值
    va_list ap;
    if(dim < 0 ||dim > MAX_ARRAY_DIM)
    {
        printf("ERROR,OUT OF MAX_ARRAY_DIM or less than 0!");
        exit(1);
    }
    
    array->dim = dim;
    
    //为维度配空间
    array->bounds = (int *)malloc(sizeof(int) * dim);
    if(NULL == array->bounds)
    {
        printf("Can not assign the space for bounds");
        exit(1);
    }

    va_start(ap,dim);
    //下面的循环用于将每个维度的大小值赋给bounds
    for(i = 0;i < dim;i++)
    {
        array->bounds[i] = va_arg(ap,int);
        if(0 == array->bounds[i])
        {
            printf("ERROR dim equal to 0!");
            exit(1);
        }
        elementtotal = elementtotal * array->bounds[i];
    }

    va_end(ap);
        //上面的代码用于计算元素的总个数
    //------------------------------------------------------------

   //为所有元素开辟内存空间
   array->base = (int * )malloc(sizeof(int) *elementtotal);
   if(NULL == array->base)
   {
        printf("Can not assign the space for bae");
        exit(1);
   }

   //为映射地址分配空间
   array->constants =(int *)malloc(sizeof(int) * dim);
   
   //将数组地址大小设置为1
   array->constants[dim - 1] = 1;

   for(i = dim - 2;i >= 0;i--)
   {    
        array->constants[i] = array->bounds[i + 1] * array->constants[i + 1];
   }
   
   //有关constants值的解释:保存每个维度的元素总数，每个数组的元素个数，以及元素大小
   //这里就全部设置为1了
   /*
        举例，比如声明的数组是a[3[4]][2]这样的一个三维数组
        那么在bounds中保存的值就是3,4,2
        而在constant中保存的值为8,2,1
        其中8是三维数组每一页的元素数量总和，2为每个一维数组的元素个数，1为数组大小。
   */
}

void DestroyArray(struct Array * array)
{
    if(NULL != array->base)
    {
        free(array->base);
    }
    

    if(NULL != array->bounds)
    {
        free(array->bounds);
    }
     
    if(NULL != array->constants)
    {
        free(array->constants);
    }
    
    array->base = NULL;
    array->bounds = NULL;
    array->constants = NULL;

    array->dim = 0;
}


void Locate(struct Array * array,va_list ap,int * off)
{
    int i = 0;
    int ind = 0;
    *off = 0;    
    for(i = 0;i < array->dim;i++)
    {
        ind = va_arg(ap,int);
        if(ind < 0 || ind > array->bounds[i])
        {
            printf("ERROR OVERFLOW!");
            exit(1);
        }
        *off = *off + array->constants[i] * ind;
    }
    /*
        locate函数的说明:
        这个函数用于定位每个元素的相对地址
        这里的ap用于接收目前数组的位置
        在array数组中，第一个值的地址为array->base
        off是一个偏移量根据数组的映射地址的值来决定每个元素的相对地址是多少
        举例:
        现有数组如下:
        array[3][4][2]    array->bounds分别为3,4,2那元素总数就是24个
                          array->contants分别为8,2,1
        
        假设目前数组的位置是array[1][1][1]
        那么当前地址偏移就为
                1 x 8 + 1 x 2 + 1 x 1 = 11
        所以这个元素的地址为array->base + 11;
    */
    
}


//Value函数的作用为取出数组元素地址所对应值
void Value(int * e,int * off,struct Array * array,...)
{
    va_list ap;
    va_start(ap,array);
    Locate(array,ap,off);
    *e = *(array->base + *off);
}


//Assign为数组的每个元素赋值
void Assign(struct Array * array,int * off,int e,...)
{
    va_list ap;
    va_start(ap,e);
    Locate(array,ap,off);
    //把e的值赋给每个元素
    *(array->base + *off) = e;
}

