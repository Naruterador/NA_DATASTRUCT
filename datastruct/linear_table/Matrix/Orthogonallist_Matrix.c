/*
   使用十字链表来实现稀疏矩阵的存

*/

#include <stdio.h>
#include <stdlib.h>


//非零元素结构体
typedef struct OLNode {
    //横坐标
    int i;
    //纵坐标
    int j;
    //矩阵元素保存的值
    int e;
    
    //非零元素的后继链接域向右
    struct OLNode * right;
    //非零元素的后继链接区向下
    struct OLNode * down;
} * OLink;

//十字链表
typedef struct {
    //行的头指针，因为创建的rhead的数量根据总行数，所以定义为OLink *
    OLink * rhead;
    //列的头指针
    OLink * chead;
    
    int rowcount;
    int columncount;
    int elementcount;
}CrossList;


//用于初始化十字链表的值，否则在创建时可能会出错
void InitSMatrix(CrossList *);
//生成一个空的十字链表
void InitSMatrixList(CrossList *);
//向矩阵中插入非零节点
void InsertAscend(CrossList *,OLink);
//创建十字链表
void CreateMatrix(CrossList *);
//打印当前的矩阵
void PrintMatrix(CrossList *); 
//按照数组的样式打印当前矩阵
void PrintMatrixOri(CrossList *); 
//矩阵相加
void AddMatrix(CrossList *,CrossList *,CrossList *);
//相加比较的辅助函数
int comp(int,int);
//矩阵相减
void SubMatrix(CrossList *,CrossList *,CrossList *);
//转置矩阵
void TransposeMatrix(CrossList *,CrossList *);
//矩阵相乘以
void MultiSmatrix(CrossList *,CrossList *,CrossList *);




int main(void)
{

    CrossList C1;
    CrossList C2;
    CrossList C3;
    InitSMatrix(&C1);
    //InitSMatrix(&C2);
    CreateMatrix(&C1);
    //CreateMatrix(&C2);
    //PrintMatrix(&M);
    //AddMatrix(&C1,&C2,&C3);
    //SubMatrix(&C1,&C2,&C3);
    //TransposeMatrix(&C1,&C2);
    //MultiSmatrix(&C1,&C2,&C3);
    PrintMatrix(&C1);
    return 0;

}


void InitSMatrix(CrossList * M)
{
    
    //初始化链表M的值，否则可能在后面操作中会出错
    M->rhead = NULL;
    M->chead = NULL;
    
    M->rowcount = 0;
    M->columncount = 0;
    M->elementcount = 0;
}




void InitSMatrixList(CrossList * M)
{
    int i = 1;
    
    //横坐标节点创建空间，根据最大行数
    M->rhead = (OLink *)malloc(sizeof(struct OLNode) * (M->rowcount + 1));
    if(NULL == M->rhead)
    {
        printf("ERROR: Can not assign space for M->rhead");
        exit(1);
    }
    //纵坐标节点创建空间，根据最大列数
    M->chead = (OLink *)malloc(sizeof(struct OLNode) * (M->columncount + 1));
    if(NULL == M->chead)
    {
        printf("ERROR:Can not assign the space for M->chead");
        exit(1);

    }
    
    for(i = 1;i <= M->rowcount;i++)
        M->rhead[i] = NULL;
    
    for(i = 1;i <= M->columncount;i++)
        M->chead[i] = NULL;

}

void InsertAscend(CrossList * M,OLink p)
{
    //将元素插入十字链表
    
    //处理行内容
    //q指向行的头节点    
    OLink q = M->rhead[p->i];
    
    if(!q || p->j < q->j)
    {
      p->right = M->rhead[p->i];
      M->rhead[p->i] = p;
    }
    else
    {
        //处理元素的行链接和插入
        while(q->right && q->right->j < p->j)
            q = q->right;
        p->right = q->right;
        q->right = p;
    }

    //处理元素的列链接和插入
    q = M->chead[p->j];
    if(!q || p->i < q->i)
    {
        p->down = M->chead[p->j];
        M->chead[p->j] = p;
    }
    else
    {    
        while(q->down && q->down->i < p->i)
            q = q->down;
        p->down = q->down;
        q->down = p;
    }


    M->elementcount ++;
}

void CreateMatrix(CrossList * M)
{

    int i = 0;
    int k = 0;
    printf("请输入对应矩阵的总行数，总列数，以及非零元素个数格式为d,d,d:");
    scanf("%d,%d,%d",&M->rowcount,&M->columncount,&k);
    InitSMatrixList(M);
    for(i = 0; i < k;i++)
    {
        OLink p =(OLink)malloc(sizeof(struct OLNode));
        if(NULL == p)
        {
            printf("ERROR:Can not assign the space for p");
            exit(1);
        }
        printf("请输入非零元素的横坐标，纵坐标，以及值格式为d,d,d:");
        scanf("%d,%d,%d",&p->i,&p->j,&p->e);
        InsertAscend(M,p);
    }

}


void PrintMatrix(CrossList * M)
{
    
    int i  = 1;
    int num = 1;
     
    OLink q;
    //按行输出
    for(i = 1;i <= M->rowcount;i++)
    {
        q = M->rhead[i];
        while(q)
        {
            printf("第%d个元素，横坐标为%d,纵坐标为%d,值为%d\n",num,q->i,q->j,q->e);
            q = q->right;
            num++;
        }
    }

    printf("\n");
    printf("\n");
    //按列输出
    num = 1;
    for(i = 1;i <= M->columncount;i++)
    {
        q = M->chead[i];
        while(q)
        {
            printf("第%d个元素，横坐标为%d,纵坐标为%d,值为%d\n",num,q->i,q->j,q->e);
            q = q->down;
            num++;
        }
    }
    
}



void PrintMatrixOri(CrossList * M)
{
    int i = 1;
    int j = 1;
    OLink q;
    for(i = 1;i <= M->rowcount;i++)
    {
        q = M->rhead[i];
        if(q)
        {
            for(j = 1; j <= M->columncount;j++)
            {
                if(j == q->j)
                {
                    printf("%d ",q->e);
                    if(q->right)
                        q = q->right;
                }   
                else
                    printf("%d ",0);
            }
        }
        else
        {
            for(j = 1;j <= M->columncount;j++)
                printf("%d ",0);
        }
        printf("\n");

    }

}


int comp(int a,int b)
{
    if(a < b)
        return -1;
    else if(a > b)
        return 1;
    else
        return 0;
}


void AddMatrix(CrossList * C1,CrossList * C2,CrossList * C3)
{
   int c1 = 1;
   int c2 = 1;
   int c3row;
   int c3col;
   OLink qc1;
   OLink qc2;
   OLink qc3;
   if(C1->rowcount != C2->rowcount || C1->columncount != C2->columncount)
   {
        printf("ERROR:2种不同类型的矩阵");
        exit(1);

   }
   //初始化C3矩阵
   if(C1->rowcount > C2->rowcount)
        c3row = C1->rowcount;
   else if(C1->rowcount < C2->rowcount)
        c3row = C2->rowcount;
   else
        c3row = C2->rowcount;

   if(C1->columncount > C1->columncount)
        c3col = C1->columncount;
   else if(C1->columncount < C1->columncount)
        c3col = C2->columncount;
   else
        c3col = C2->columncount;
   InitSMatrix(C3);
   C3->rowcount = c3row;
   C3->columncount = c3col;
   C3->elementcount = 0;
   InitSMatrixList(C3);
    
    while(c1 <= C1->rowcount && c2 <= C2->rowcount)
    {
      qc1 = C1->rhead[c1];
      qc2 = C2->rhead[c2];
      
      while(qc1 && qc2)
      { 
        if(qc1->i < qc2->i)
        {
            InsertAscend(C3,qc1); 
        }
        else if(qc1->i > qc2->i)
        {
            InsertAscend(C3,qc2);  
        }
        else if(qc1->i == qc2->i)
        {
            if(qc1->j < qc2->j)
                InsertAscend(C3,qc1);
            else if(qc1->j > qc2->j)
                InsertAscend(C3,qc2);
            else if(qc1->j == qc2->j)
            {
                qc3 = (OLink)malloc(sizeof(struct OLNode));
                if(NULL == qc3)
                {
                    printf("Can not assign the space for qc3!");
                    exit(1);

                }
                qc3->i = qc1->i;
                qc3->j = qc1->j;
                qc3->e = qc1->e + qc2 ->e;
                if(qc3->e == 0)
                {
                    qc1 = qc1->right;
                    qc2 = qc2->right;
                    continue;
                }
                else
                    InsertAscend(C3,qc3);
            }
         }
            qc1 = qc1->right;
            qc2 = qc2->right;
            C3->elementcount++;
       }
        c1++;
        c2++;
     }

     //处理矩阵C1和矩阵C2中剩下的值
     while(c1 <= C1->rowcount)
     {
        qc1 = C1->rhead[c1];
        while(qc1)
        {
          InsertAscend(C3,qc1);
          qc1 = qc1->right;
          C3->elementcount++;
        }

        c1++;

     }
     
    while(c2 <= C2->rowcount)
    {
        qc2 = C2->rhead[c2];
        while(qc2)
        {
            InsertAscend(C3,qc2);
            qc2 = qc2->right;
            C3->elementcount++;
        }

        c2++;
    }

}


void SubMatrix(CrossList * C1,CrossList * C2,CrossList * C3)
{
    int c1;
    int c2;
    int i = 1;
    OLink q;
    for(i = 1;i <= C2->rowcount;i++)
    {
        q = C2->rhead[i];
        while(q)
        {
            q->e = q->e * -1;
            q = q->right;
        }
    }
    AddMatrix(C1,C2,C3);
}



void TransposeMatrix(CrossList * C1,CrossList * C2)
{
    InitSMatrix(C2);
    C2->rowcount = C1->columncount;
    C2->columncount = C1->rowcount;
    C2->elementcount = C1->elementcount;
    InitSMatrixList(C2);

    int i;
    OLink q;
    OLink p;
    for(i = 1;i <= C1->rowcount;i++)
    {
        q = C1->rhead[i];
        while(q)
        {
            p =(OLink)malloc(sizeof(struct OLNode));
            if(NULL == p)
            {
                printf("Can not assign the space for p");
                exit(1);
            }
            p->i = q->j;
            p->j = q->i;
            p->e = q->e;
            InsertAscend(C2,p);
            q = q->right;
        }
    }

}




void MultiSmatrix(CrossList * C1,CrossList * C2,CrossList * C3)
{
    if(C1->rowcount != C2->columncount)
    {
        printf("ERROR:这两个矩阵不符合相乘的要求！");
        exit(1);
    }
    InitSMatrix(C3);
    C3->rowcount = C1->columncount;
    C3->columncount = C2->rowcount;
    C3->elementcount = 0;
    InitSMatrixList(C3);
    
    OLink q;
    OLink p;
    OLink pnew;
    int temp = 0;
    
    int i;
    int j = 1;

    for(j = 1;j <= C1->rowcount;j++)
    {
        for(i = 1;i <= C2->columncount;i++)
        {

            q = C1->rhead[j];
            p = C2->chead[i];
        
            while(q && p)
            {
                temp = temp + (q->e * p->e);
                q = q->right;
                p = p->down;
            }
            pnew = (OLink)malloc(sizeof(struct OLNode));
            if(NULL == pnew)
            {
                printf("Can not assign the space for pnew!");
                exit(1);
            }
            pnew->i = j;
            pnew->j = i;
            pnew->e = temp;
            InsertAscend(C3,pnew);
            temp = 0;
        }   
    }   
}

