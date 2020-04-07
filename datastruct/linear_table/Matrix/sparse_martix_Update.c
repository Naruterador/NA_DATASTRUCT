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
void MulSMatrixNor(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T,struct RSLMatrix * Q);
void MulSMatrixUpd(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T);
void TransposeRSLMatrixNor(struct RSLMatrix * M,struct RSLMatrix * T);
void TransposeRSLMatrixUpd1(struct RSLMatrix * M,struct RSLMatrix * T);
void TransposeRSLMatrixUpd2(struct RSLMatrix * M,struct RSLMatrix * T);


int main(void)
{
    struct RSLMatrix M;
    struct RSLMatrix N;
    struct RSLMatrix T;
    struct RSLMatrix Q;
    
    CreateRSLMatrix(&M);
    //CreateRSLMatrix(&N);
    //MulSMatrixNor(&M,&N,&T,&Q);
    //MulSMatrixUpd(&M,&N,&T);
    TransposeRSLMatrixUpd2(&M,&T);
    //CreateRSLMatrix(&N);
    //AddRSLMatrix(&M,&N,&T);
    PrintRSLMatrix(&T);
    return 0;
}




void CreateRSLMatrix(struct RSLMatrix * ma)
{
    
    int i = 0;
    int k = 0;
    int j = 0;
    

    printf("请输入矩阵的总行数，总列数，以及非零元素的个数，格式为d,d,d:");
    scanf("%d,%d,%d",&ma->rowc,&ma->colc,&ma->eleco);
    
    //检查非零元素总个数是否大于最大非零元素个数
    if(ma->eleco > MAX_SIZE)
    {
        printf("ERROR:非零元素个数超过上限");
        exit(1);
    }
    
    ma->ma[i].i = 0;
    ma->ma[i].j = 0;
    ma->ma[i].e = 0;

    for(i = 1;i<= ma->eleco;i++)
    {   
        do{
            printf("请输出第%d个非零元素的横坐标值,纵坐标值,参数值,格式为d,d,d:",i);
            scanf("%d,%d,%d",&ma->ma[i].i,&ma->ma[i].j,&ma->ma[i].e);
            if(ma->ma[i].i < 1 || ma->ma[i].j < 1 || ma->ma[i].i > ma->rowc || ma->ma[i].j > ma->colc)
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



void SubRSLMatrix(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T)
{
    int i = 1;
    for(i = 1;i <= N->eleco;i++)
    {
        N->ma[i].e = N->ma[i].e * -1;
    }
    AddRSLMatrix(M,N,T);
}

//矩阵转置的普通做法
void TransposeRSLMatrixNor(struct RSLMatrix * M,struct RSLMatrix * T)
{
    int m = 1;
    int n = 1;
    int q = 1;
    T->eleco = M->eleco;
    T->rowc = M->colc;
    T->colc = M->rowc;
    for(m = 1;m <= M->colc;m++)
        for(n = 1;n <= M->eleco;n++)
        {
            if(m == M->ma[n].i)
            {
                T->ma[q].i = M->ma[n].j;
                T->ma[q].j = M->ma[n].i;
                T->ma[q].e = M->ma[n].e;
                q++;
            }
        }
}


void TransposeRSLMatrixUpd1(struct RSLMatrix * M,struct RSLMatrix * T)
{
    int m = 1;
    int n = 1;
    int col = 1;
    int q = 1;
    int * countcol;
    int * cpot;
    
    T->colc = M->rowc;
    T->rowc = M->colc;
    T->eleco = M->eleco;
    
    countcol =(int *)malloc(sizeof(int) * (M->colc + 1));
    cpot = (int *)malloc(sizeof(int) * (M->colc + 1));
    
    //计算矩阵M每列的元素数量
    for(m = 1;m <= M->eleco;m++)
        ++countcol[M->ma[m].j];
    
    //初始化cpot的值
    for(m = 1;m <= M->colc;m++)
        cpot[m] = 0;
    
    //计算矩阵M转置之后没一个非0元素的新位置
    cpot[1] = 1;
    for(n = 2;n <= M->colc;n++)
        cpot[n] = cpot[n - 1] + countcol[n - 1];
    
    for(m = 1;m <= M->eleco; m++)
    {
        n = M->ma[m].j;
        col = cpot[n];
        
        T->ma[col].j = M->ma[m].i;
        T->ma[col].i = M->ma[m].j;
        T->ma[col].e = M->ma[m].e;
        cpot[n]++;
    }
    

    //初始化T-rpos的值
    for(m = 1;m <= T->rowc;m++)
        T->rpos[m] = 0;

    //计算每一行的非零元素个数
    for(m = 1;m <= M->eleco;m++)
       ++T->rpos[T->ma[m].i];
    
    //计算rpos
    for(m = T->rowc;m >= 1;m--)
    {
        T->rpos[m] = 1;
        for(n = m - 1;n >= 1;n--)
            T->rpos[m] = T->rpos[m] + T->rpos[n];
    }
}


void TransposeRSLMatrixUpd2(struct RSLMatrix * M,struct RSLMatrix * T)
{
    int i;
    int j;
    int m;
    int n;
    int * num;
    
    T->rowc = M->colc;
    T->colc = M->rowc;
    T->eleco = M->eleco;

    
    num =(int *)malloc(sizeof(int) * (M->colc + 1));
    
    if(T->eleco)
    {
        for(i = 1;i <= M->colc;i++)
            num[i] = 0;
        
        for(i = 1;i <=M->eleco;i++)
            ++num[M->ma[i].j];
        
        T->rpos[1] = 1;
        for(j = 2;j <= M->colc;j++)
            T->rpos[j] = T->rpos[j - 1] + num[j - 1];

        
        for(j = 1; j <= M->colc;j++)
            num[j] = T->rpos[j];
        
        for(j = 1;j <= M->eleco;j++)
        {
            m = M->ma[j].j;
            n = num[m];
            
            T->ma[n].i = M->ma[j].j;
            T->ma[n].j = M->ma[j].i;
            T->ma[n].e = M->ma[j].e;
            ++num[m];
        }

    free(num);

    }

}

void MulSMatrixNor(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T,struct RSLMatrix * Q)
{
    int * Nc;
    int * Tc;
    
    int m = 1;
    int n = 1;
    int q = 1;



    //判断2个矩阵是否可以做相乘运算
    if(M->rowc != N->colc)
    {
        printf("ERROR:这个2个矩阵无法进行相乘！");
        exit(1);
    }
    //初始化矩阵T的非零元素属性
    T->rowc = N->colc;
    T->colc = M->rowc;
    T->eleco = 0;
    
    //矩阵N每一行的非零元素值
    Nc = (int *)malloc(sizeof(int) * (N->rowc + 1));
    //保存相乘之后的值
    Tc = (int *)malloc(sizeof(int) * (M->colc + 1));
    
    //核心部分
    for(m = 1;m <= N->colc;m++)
    {
        //初始化Nc的值
        for(n = 1;n <= N->rowc;n++)
            Nc[n] = 0;
        
        //初始化Tc的值
        for(n = 1;n <= M->colc;n++)
            Tc[n] = 0;
        
        //求出Nc的值
        for(n = 1;n <= N->eleco;n++ )           
            if(m == N->ma[n].j)
                Nc[N->ma[n].i] = N->ma[n].e;


        //求出Tc的值
        for(n = 1;n <= N->eleco; n++)
        {
            Tc[M->ma[n].i] = Tc[M->ma[n].i] + M->ma[n].e * Nc[M->ma[n].j];
        }
        
        for(n = 1;n <= T->colc; n++)
        if(Tc[n] != 0)
        {
            T->eleco++;
            T->ma[q].e = Tc[n];
            T->ma[q].i = m;
            T->ma[q].j = n;
            q++;
        }
    }
    TransposeRSLMatrixUpd1(T,Q);
    free(Nc);
    free(Tc);
}



void MulSMatrixUpd(struct RSLMatrix * M,struct RSLMatrix * N,struct RSLMatrix * T)
{
    int arow;
    int brow;
    int col;
    int p;
    int q;
    int tp;
    int tq;
    //相乘后的结果
    int ctemp[MAX_RC + 1];
    int m;
    int n = 1;
    int i = 1;
    
    //判断是否可以进行矩阵相乘操作
    if(M->rowc != N->colc)
    {
        printf("ERROR:不能进行矩阵相乘");
        exit(1);
    }

    T->rowc = M->rowc;
    T->colc = N->colc;
    T->eleco = 0;

    for(arow = 1; arow <= M->rowc; arow++)
    {
        //清空累计器
        for(col = 1;col <= i;col++)
            ctemp[col] = 0;

        T->rpos[arow] = T->eleco + 1;
        
        //循环结束点为
        if(arow < M->rowc)
            tp = M->rpos[arow + 1];
        else
            tp = M->eleco + 1;

        for(p = M->rpos[arow];p < tp; p++)
        {
            brow = M->ma[p].j;
            
            if(brow < N->rowc)
                tq = N->rpos[brow + 1];
            else
                tq = N->eleco + 1;
            for(q = N->rpos[brow];q < tq;q++)
            {
                col = N->ma[q].j;
                ctemp[col] = ctemp[col] + M->ma[p].e * N->ma[q].e;

            }
        }

        for(i = 1; i<= col;i++)
        {
            if(ctemp[i] != 0)    
            {
                if(T->eleco > MAX_SIZE)
                {
                    printf("ERROR:非零数组元素个数超过最大值！");
                    exit(1);
                }
                
                T->ma[n].i = arow;
                T->ma[n].j = i;
                T->ma[n].e = ctemp[i];
                T->eleco++;
                n++;
            }
        }
        
    }    
}










