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

int main(void)
{

    CrossList M;
    InitSMatrix(&M);
    CreateMatrix(&M);
    //PrintMatrix(&M);
    PrintMatrixOri(&M);



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
    M->rhead = (OLink *)malloc(sizeof(OLink) * (M->rowcount + 1));
    if(NULL == M->rhead)
    {
        printf("ERROR: Can not assign space for M->rhead");
        exit(1);
    }
    //纵坐标节点创建空间，根据最大列数
    M->chead = (OLink *)malloc(sizeof(OLink) * (M->columncount + 1));
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
        printf("\n");

    }

}
