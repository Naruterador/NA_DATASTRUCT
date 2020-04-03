/*
行逻辑链接的顺序表

特点:
可以快速存取一个非零元素在矩阵中的位置(通过行来查找),这样就可以快速的找到某一行的元素了。

实现方式:
将快速转置矩阵的算法中的指示行信息作为辅助数组cpot固定在稀疏矩阵的存储结构中
*/



#include <stdio.h>
#include <stdlib.h>



//最大非零元素个数为100
#define MAX_SIZE 100
//最大行数
#define MAX_RC 20

struct Triple
{
    //矩阵的横坐标
    int i;
    //矩阵的纵坐标
    int j;
    //用于存入矩阵的值
    int e;
};


struct RSLMatrix
{
    //最大行数
    int rowc;
    //最大列数;
    int colc;
    //非零元素个数
    int eleco;
    
    //用于存放矩阵的每个元素
    struct Triple ma[MAX_SIZE + 1];
    
    //rpos数组用于存放每一行的第一个非零元素的位置
    int rpos[MAX_RC + 1];
};

void CreateRSLMatrix(struct RSLMatrix *);
void PrintRSLMatrix(struct RSLMatrix *);
void PrintRSLMatrixOrigin(struct RSLMatrix *);
void AddRSLMatrix(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T);
void SubRSLMatrix(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T);
void MulSMatrix(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T);
void TransposeRSLMatrix(struct RSLMatrix * M,struct RSLMatrix * T);


int main(void)
{
    struct RSLMatrix M;
    struct RSLMatrix N;
    struct RSLMatrix T;
    
    CreateRSLMatrix(&M);
    //CreateRSLMatrix(&N);
    //AddRSLMatrix(&M,&N,&T);
    //PrintRSLMatrix(&T);
    return 0;
}




void CreateRSLMatrix(struct RSLMatrix * ma)
{
    
    int i = 0;
    int k = 0;
    int j = 0;

    printf("请输入矩阵的总行数，总列数，以及总元素个数,格式为d,d,d:");
    scanf("%d,%d,%d",&ma->rowc,&ma->colc,&ma->eleco);
    
    if(ma->rowc < 1 || ma->colc < 1 || ma->eleco > MAX_SIZE)
    {
        printf("ERROR：矩阵创建失败");
        exit(1);
    }
    
    ma->ma[i].i = 0;
    ma->ma[i].j = 0;
    ma->ma[i].e = 0;
    //输入每个元素在矩阵中的位置和值
    for(i = 1;i <= ma->eleco;i++)
    {
        k = 0;
        do{
            printf("输入第%d个非零元素的横坐标值,纵坐标值,参数值,格式为d,d,d:",i);
            scanf("%d,%d,%d",&ma->ma[i].i,&ma->ma[i].j,&ma->ma[i].e);
            
            if(ma->ma[i].i < 1 || ma->ma[i].j < 1)
            {
                printf("ERROR:1");
                k = 1;
            }
            if(ma->ma[i].i <= ma->ma[i-1].i && ma->ma[i].j <= ma->ma[i-1].j)
            {
                printf("ERROR:2");
                k = 1;
                
            }
        }while(k);        
    }

    //处理rpos用于记录每一行第一个非零元素的位置
    
    //为rpos元素预赋值
    ma->rpos[0] = 0;
    for(j = 1;j <= ma->rowc;j++)
        ma->rpos[j] = 0;
    
    //求出每一行的非零元素个数
    for(j = 1;j <= ma->eleco;j++)
        ma->rpos[ma->ma[j].i]++;
    

    //计算rpos的值，核心部分
   for(i = ma->rowc;i >= 1;i--) //从最后一行开始一次计算每一行
   {
        ma->rpos[i] = 1;
        for(j = i - 1;j >= 1;j--)
        {
            ma->rpos[i] = ma->rpos[i] + ma->rpos[j]; //后一行的非零元素开始位置使用当前行现有的元素个数，加上上一行的元素个数 
        }

   }

}


void PrintRSLMatrix(struct RSLMatrix * ma)
{
    int i = 1;
    
    printf("矩阵最大行数为%d,矩阵最大列数为%d,总非零元素个数为%d\n",ma->rowc,ma->colc,ma->eleco);




    for(i = 1;i <= ma->eleco;i++)
        printf("第%d个非零元素的横坐标为%d,总坐标为%d,所保存的值为%d\n",i,ma->ma[i].i,ma->ma[i].j,ma->ma[i].e);
    
    for(i = 1;i <= ma->rowc;i++)
        printf("第%d行的第一个非零元素位置为%d\n",i,ma->rpos[i]);

}


void PrintRSLMatrixOrigin(struct RSLMatrix * ma)
{
    int i = 1;
    int j = 1;
    int k = 1;
    for(i = 1;i <= ma->rowc;i++)
    {
        for(j = 1;j <= ma->colc;j++)
        {
            if(i == ma->ma[k].i && j == ma->ma[k].j)
            {
                printf("%d ",ma->ma[k].e);
                k++;
            }else
                printf("%d ",0);   
                
        }
        printf("\n");
    }
}


void AddRSLMatrix(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T)
{
    int k;
    int m;
    int n;
    int q;

    int Tm;
    int Tn;
    
    if(M->rowc != N->rowc || M->colc != N->colc)
    {
        printf("ERROR:Can not add two Matrix!");
        exit(1);
    }
    
    T->rowc = M->rowc;
    T->colc = M->colc;
    //初始化矩阵T的元素总数为0
    T->eleco = 0;
    
    //核心部分
    for(k = 1;k <= M->rowc;k++)
    {
        //初始化矩阵的T的rpos的值，将第一行非零元素的初始值设置为1
        T->rpos[k] = ++T->eleco;
        
        //m,n是用于矩阵M和矩阵N相加的索引值
        m = T->rpos[k];
        n = T->rpos[k];
        
        //这个if用于控制每次矩阵T中加入的元素个数数量
        //原理:在K != 矩阵M的最大行数之前，每次循环次数都等于下一个的矩阵M和矩阵N的rpos的值
        if(k == M->rowc)
        {            
            Tm = M->eleco + 1;
            Tn = N->eleco + 1;

        }
        else
        {
            Tm = M->rpos[k + 1];
            Tn = N->rpos[k + 1];
        }
        
        while(m < Tm && n < Tn)
        {
            q++;
            if(M->ma[m].i == N->ma[n].i)
            {
                if(M->ma[m].j == N->ma[n].j)
                {

                    T->ma[q].i = M->ma[m].i;
                    T->ma[q].j = M->ma[m].j;
                    T->ma[q].e = M->ma[m].e + N->ma[n].e;
                    if(T->ma[q].e == 0)
                        q--;
                }
                else if(M->ma[m].j < N->ma[n].j)
                {
                    T->ma[q] = M->ma[m];
                }
                else
                    T->ma[q] = N->ma[n];
            }
            else if(M->ma[m].i < N->ma[n].i)
            {
                T->ma[q] = M->ma[m];
            }
            else
                T->ma[q] = N->ma[n];

            m++;
            n++;

        }

        while(m < Tm)
        {
            q++;
            T->ma[q] = M->ma[m];
            m++;
        }

        while(n < Tn)
        {
            q++;
            T->ma[q] = N->ma[n];
            n++;
        }

        T->eleco = q;
    }
    if(T->eleco > MAX_SIZE)
    {   
        printf("ERROR:矩阵T超过最大值!");
        exit(1);

    }
}







