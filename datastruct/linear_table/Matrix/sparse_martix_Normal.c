/*
使用三元组来实现稀疏矩阵的各种操作
*/

#include <stdio.h>
#include <stdlib.h>

//最大的非零元素个数
#define MAX_ELEMENT_SIZE  100

//每个元素的信息节点结构体
struct Triple
{
    //非零元素的横坐标
    int i;
    //非零元素的纵坐标
    int j;
    //非零元素的元素值
    int evalue;
};

//矩阵结构体
struct Matrix
{
    //节点数组,需要+1,因为0行是用来存储总行数、总列数和总非零元素个数的。
    struct Triple data[MAX_ELEMENT_SIZE + 1];
    
    //矩阵的总行数
    int row;
    //矩阵的总列数
    int column;
    //非零元素个数
    int countele;
};


//创建矩阵
void CreateMatrix(struct Matrix *);
//销毁矩阵
void DestroyMatrix(struct Matrix *);
//打印矩阵
void PrintMatrix(struct Matrix *);
//按矩阵的形式打印
void PrintMatrixM(struct Matrix *);
//复制矩阵
void CopyMatrix(struct Matrix *,struct Matrix *);
//求稀疏矩阵的和(Q = M + N)
void AddMatrix(struct Matrix * M,struct Matrix * N,struct Matrix * Q);
//辅助函数用于判断2个值的大小AddMartx用
int comp(int,int);
//矩阵求差
void SubMatrix(struct Matrix * M,struct Matrix * N,struct Matrix * Q);
//稀疏矩阵M转置矩阵T
void TransportMartix(struct Matrix * M,struct Matrix * T);
//求稀疏矩阵的乘积
void MultMatrix(struct Matrix * M,struct Matrix * N,struct Matrix * Q);
//快速求稀疏矩阵M的转置矩阵T
void FastTransposeMatrix(struct Matrix * M,struct Matrix * T);







int main(void)
{
    struct Matrix M;
    struct Matrix N;
    struct Matrix Q;
    struct Matrix T;
    CreateMatrix(&M);
    FastTransposeMatrix(&M,&T);
    //CreateMatrix(&N);
    //MultMatrix(&M,&N,&Q);
    //TransportMartix(&M,&T);
    //SubMatrix(&M,&N,&Q);
    //AddMatrix(&M,&N,&Q);
    PrintMatrix(&T);
    //PrintMatrixM(&ma);
    
    return 0;

}


void CreateMatrix(struct Matrix * ma)
{
    int i = 0;
    int row = 0;
    int col = 0;
    int eleV = 0;
    int k = 0;
    
    printf("请输入矩阵的总行数，总列数，以及非零元素的个数，格式为d,d,d:");
    scanf("%d,%d,%d",&ma->row,&ma->column,&ma->countele);
    
    //检查非零元素总个数是否大于最大非零元素个数
    if(ma->countele > MAX_ELEMENT_SIZE)
    {
        printf("ERROR:非零元素个数超过上限");
        exit(1);
    }
    /*
    //检查是否矩阵是否满足稀疏矩阵的要求
    double temprow = ma->row;
    double tempcol = ma->column;
    double tempelecount = ma->countele;
    double Z = ma->countele / (ma->row * ma->column);    
    if(Z > 0.05)
    {
        printf("ERROR:这不是一个稀疏矩阵");
        exit(1);
    }
    */

    //将矩阵的0行设矩阵的总行数，总列数，以及非零元素的个数
    ma->data[i].i = 0;
    ma->data[i].j = 0;
    ma->data[i].evalue = 0;
    for(i = 1;i <= ma->countele;i++)
    {
        
        do{
            k = 0;
            printf("请输入一个节点的横坐标值，纵坐标值，以及元素的值，格式为d,d,d:");
            scanf("%d,%d,%d",&row,&col,&eleV);
            
            //对输入的元素三元组进行检查
            //检查坐标是否越界
            if(row < 1 || row > ma->row || col < 1 || col > ma->column)
            {
                printf("ERROR:错误的做标值,请从新输入");
                k = 1;
            }
            //检测输入坐标是否冲突
            if(row <= ma->data[i - 1].i && col <=ma->data[i-1].j )
            {
                printf("ERROR:错误的矩阵节点输入，请从新输入");
                k = 1;
            }

        }while(k);

        ma->data[i].i = row;
        ma->data[i].j = col;
        ma->data[i].evalue = eleV;

    }

}



void DestroyMatrix(struct Matrix * ma)
{
    ma->column = 0;
    ma->row = 0;
    ma->countele = 0;
}


//输出矩阵保存的所有非0元素
void PrintMatrix(struct Matrix * ma)
{
    int i = 1;
    for(i = 1;i <= ma->countele;i++)
    {   
        printf("节点%d的横坐标为%d,纵坐标为%d,元素值为%d\n",i,ma->data[i].i,ma->data[i].j,ma->data[i].evalue);
    }
}


//按照矩阵的形式打印
/*
矩阵样式为:

1 0 2 0
0 3 0 4
0 0 5 0

*/

void PrintMatrixM(struct Matrix * ma)
{
    int i = 1;
    int j = 1;
    int k = 1;
    int m = 1;
    int flag = 0;
    
    for(i = 1;i <= ma->row;i++)
    {
        for(j = 1;j <= ma->column;j++)
        {
            for(k = m;k <= ma->countele;k++)
            {
                if(ma->data[k].i == i && ma->data[k].j == j)
                {
                    printf("%d ",ma->data[k].evalue);
                    m++;
                    flag = 1;
                    break;
                }
            }
            if(!flag)
                printf("%d ",0);
            flag = 0;

        }
        printf("\n");
    }
}

//将矩阵N赋值给矩阵M
void CopyMatrix(struct Matrix * M,struct Matrix * N)
{
    M = N;
}

int comp(int a,int b)
{
    if(a < b)
        return - 1;
    else if(a == b)
        return 0;
    else
        return 1;
}

//求稀疏矩阵的和
//原理：将矩阵M和矩阵N中的非零数组相加，放到新的矩阵Q中，新矩阵的非零元素数量为元素多的那个矩阵
//矩阵相加时，只有2个值相同才会发生相加运算，否则就取坐标较小的值
void AddMatrix(struct Matrix * M,struct Matrix * N,struct Matrix * Q)
{
    int m = 1;
    int n = 1;
    int q = 0;
    Q->data[q].i= 0;
    Q->data[q].j = 0;
    Q->data[q].evalue = 0;
    
    if((M->column != N->column) || (M->row != N->row))
    {
        printf("ERROR:两个矩阵的总行数或总列数不同");
        exit(1);
    }
    
    while(m <= M->countele && n <= N->countele)
    {   
        q++;
        //M的横坐标比N的横坐标小时，将现在M的值直接赋给Q
        if(-1 == comp(M->data[m].i,N->data[n].i))
            Q->data[q] = M->data[m];
        //M的横坐标与N的横坐标相同时的处理
        else if(0 == comp(M->data[m].i,N->data[n].i))
        {   
            //比较M，N的纵坐标
            if(-1 == comp(M->data[m].j,N->data[n].j))
                Q->data[q] = M->data[m];
            else if(0 == comp(M->data[m].j,N->data[n].j))
            {
                Q->data[q].i = M->data[m].i;
                Q->data[q].j = M->data[m].j;
                Q->data[q].evalue = M->data[m].evalue + N->data[n].evalue;
                //有可能会出现相加一个负数为0的情况
                if(Q->data[q].evalue == 0)
                    q--;
            }
            else if(1 == comp(M->data[m].j,N->data[n].j))
                Q->data[q] = N->data[n];
        }     
        else if(1 == comp(M->data[m].i,N->data[n].i))
            Q->data[q] = N->data[n]; 

        m++;
        n++;
    }
    
    //处理剩余的M的值
    while(m <= M->countele)
    {
        
        q++;
        Q->data[q] = M->data[m];
        m++;
    }
    
    //处理剩余的N的值
    while(n <= N->countele)
    {
        q++; 
        Q->data[q] = N->data[n];
        n++;
    }
    Q->countele = q;
    
    if(q > MAX_ELEMENT_SIZE)
    {
        printf("ERROR:相加后矩阵的非零元素数量超过最大值！");
        exit(1);
    }
}

//矩阵相减Q = M - N
void SubMatrix(struct Matrix * M,struct Matrix * N,struct Matrix * Q)
{
    int i = 1;
    for(i = 1;i <= N->countele;i++)
    {
        //将N矩阵内的非零元素的值，变成负数，然后和M矩阵相加
        N->data[i].evalue = N->data[i].evalue * -1;
    }
    
    AddMatrix(M,N,Q);
}

/*
把mxn矩阵M的行换成同序数的列得到一个nxm的矩阵T，这个T就叫做M的转置矩阵。
举例：
矩阵M为
1  2  0
3 -1  4

转置后的矩阵T为
1  3
2 -1
0  4

//本质其实就是根据列来排序
这个转置的时间复杂度为O(M*N)
但是当非零元素的个数和总元素个数在同数量级时
复杂度就变成了O(muXnu^2)

这个算法适用于

非零元素个数远小于总元素个数，即:
tu << mu X nu


*/
void TransportMartix(struct Matrix * M,struct Matrix * T)
{
    T->column = M->column;
    T->countele = M->countele;
    T->row = M->row;
    int m = 1;
    int n = 1;
    int q = 1;
    

    
    for(m = 1;m <= M->column;m++)
        for(n = 1;n <= M->countele;n++)
            //如果列的值相同，就想行和列颠倒
            if(m == M->data[n].j)
            {
                T->data[q].i = M->data[n].j;
                T->data[q].j = M->data[n].i;
                T->data[q].evalue = M->data[n].evalue;
                q++;
            }
}

//求稀疏矩阵的乘积Q=MXN;
void MultMatrix(struct Matrix * M,struct Matrix * N,struct Matrix * Q)
{
    int i = 1;
    int j = 1;
    //Nc数组用于存放按列序排的矩阵N的值
    int * Nc;
    //Tc数组用于存放，相乘后的结果
    int * Tc;
    
    struct Matrix T;
    
    //检测矩阵是否符合做乘法的标准
    if(M->row != N->column)
    {
        printf("ERROR：矩阵不符合做乘法的要求!");
        exit(1);
    }

    //初始化一个矩阵T用来保存结果
    T.row = N->column;
    T.column = M->row;
    //矩阵T的初始元素数量为0
    T.countele = 0;
    
    //由于数组序列不包括0,所以大小+1
    //初始化Nc数组的空间
    Nc = (int *)malloc(sizeof(int) * N->row + 1);
    //初始化Tc数组的空间
    Tc = (int *)malloc(sizeof(int) * M->column + 1);
    if(NULL == Nc || NULL == Tc)
    {
        printf("Can not assign space for Nc or Tc");
        exit(1);
    }
    
    //核心部分
    for(i = 1;i <= N->column;i++)
    {
        //预赋值，将Nc各值赋0,0序列不用
        for(j = 1;j <= N->row;j++)
            Nc[j] = 0;
        //预赋值，将Tc各值赋0,0序列不用
        for(j = 1;j <= M->column;j++)
            Tc[j] = 0;
        
        //处理Nc数组的值
        for(j = 1;j <= N->countele;j++)
            //将纵坐标相等的值存入存入数组Nc
            if(i == N->data[j].j)
                Nc[N->data[j].i] = N->data[j].evalue;
        
        //处理Tc数组的值
        for(j = 1;j <= M->countele;j++)
            Tc[M->data[j].i] = Tc[M->data[j].i] +  M->data[j].evalue * Nc[M->data[j].j];
        
        //将Tc中的数放入矩阵T
        for(j = 1;j <= M->row;j++)
        {
            if(Tc[j] != 0)
            {
                T.countele++;
                T.data[T.countele].i = i;
                T.data[T.countele].j = j;
                T.data[T.countele].evalue = Tc[j];
            }

        }
    }


    //检查是否新数组是否越界限
    if(T.countele > MAX_ELEMENT_SIZE)
    {
        printf("ERROR:新矩阵中的非零元素超过最大值！");
        exit(1);
    }
    
    //把矩阵T赋给矩阵Q
    TransportMartix(&T,Q);
    DestroyMatrix(&T);
    free(Nc);
    free(Tc);
}




void FastTransposeMatrix(struct Matrix * M,struct Matrix * T)
{
    int m = 1;
    int n = 1;
    int t = 1;
    int col = 1;
    //n用于保存每列的元素数量
    int * numcol;
    //pot用于保存T每行的下一个非零元素的存储位置
    int * pot;
    

    //序号都从0开始，所以空间+1
    //为numcol开辟空间
    numcol = (int *)malloc(sizeof(int) * (M->column + 1));
    //为pot开辟空间
    pot = (int *)malloc(sizeof(int) * (M->column +1));

    //矩阵T的总列数、总行数、总元素数量赋值
    T->column = M->row;
    T->row = M->column;
    T->countele = M->countele;

    //核心部分
    //判断T矩阵是不是一个非零矩阵
    if(T->countele)
    {
        //先将numcol初始化，并将值全赋0
        for(col = 1;col <= M->column;col++)
        {
            numcol[col] = 0;
        }
        //计算M矩阵每一列的非零元素个数
        for(t = 1;t <= M->countele;t++)
            ++numcol[M->data[t].j];
        
        //将pot的序列1位置初始化为1
        pot[1] = 1;
        //求T的第COL行的第一个非零元素在T.data中的序号
        for(col = 2;col <= M->column;col++)
            pot[col] = pot[col - 1] + numcol[col - 1];
        
        for(m = 1;m <= M->countele;m++)
        {
            //求出M的列数
            col = M->data[m].j;
            //n为M当前元素在T中的序号
            n = pot[col];
            T->data[n].i = M->data[m].j;
            T->data[n].j = M->data[m].i;
            T->data[n].evalue = M->data[m].evalue;
            //T第col行下的下一个非零元素在T.data中的序号
            pot[col]++;

        }

    }
    free(numcol);
    free(pot);

}

