/*
线索二叉树的实现

线索二叉树用于解决在某种遍历序列中找到某个结点的前驱或后继

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



enum PointTag
{

    Link,Thread //Link(0)用于表示左子树和右子树的指针 Thread(1)用于表示线索指针，指向前驱或者后继

};


typedef struct BitNode
{
    //结点数据
    int data;
    //结点类型
    enum PointTag Ltag;
    enum PointTag Rtag;

    //左孩子和右孩子指针
    struct BitNode * Lchild;
    struct BitNode * Rchild;
    bool tag; //用于后序线索二叉树遍历的标记
}BitNode,*BiTree;


//初始化二叉树
void init_BiThrTree(BiTree *);
//创建二叉树
void CreateBiThreTree(BiTree *);
//全局二叉树，用于保存前驱
BiTree pre;


//通过中序遍历进行中序线索化
void InThreading(BiTree);
//中序遍历二叉树T,并将其中序线索化
void InOrderThreading(BiTree *,BiTree);
//中序遍历二叉树
void InOrderTraverse1(BiTree T);


//通过先序遍历进行先序线索化
void PreThreading(BiTree);
//先序遍历二叉树T,并将其先序线索化
void PreOrderThreading(BiTree *,BiTree);
//先序遍历二叉树
void PreOrderTraverse1(BiTree T);


//通过后序遍历进行先序线索化
void PostThreading(BiTree);
//后序遍历二叉树T,将将其后序线索化
void PostOrderThreading(BiTree *,BiTree);
//后续遍历线索二叉树
void PostOrderTraverse1(BiTree T);

//清空二叉树
void DestroyBiTree(BiTree * T);
//清空线索二叉树
void DestroyBiThTree(BiTree * Th);

int main(void)
{

    BiTree T;
    BiTree Th;
    init_BiThrTree(&Th);
    init_BiThrTree(&T);
    CreateBiThreTree(&T); 
    InOrderThreading(&Th,T);
    //InOrderTraverse1(Th); 
    //PreOrderThreading(&Th,T);
    //PreOrderTraverse1(Th);
    //PostOrderThreading(&Th,T);

    return 0;

}



void init_BiThrTree(BiTree * T)
{
    T = NULL;
}




void CreateBiThreTree(BiTree * T)
{
    int data;
    printf("Please input tree node value:");
    scanf("%d",&data);
    
    if(0 == data)
    {
       *T = NULL;
    }
    else
    {
         *T = (BiTree)malloc(sizeof(struct BitNode));
         if(NULL == *T)
        {
            printf("Can not assign the space for *T");
            exit(1);
        }
    
        (*T)->data = data;
        (*T)->tag = false;
        CreateBiThreTree(&(*T)->Lchild);
        if((*T)->Lchild)
            (*T)->Ltag = Link;

  
        CreateBiThreTree(&(*T)->Rchild);
        if((*T)->Rchild)
            (*T)->Rtag = Link;
    }
}



void InOrderTraverse(BiTree T)
{
    if(T)
    {
        InOrderTraverse(T->Lchild);
        printf("%d",T->data);
        InOrderTraverse(T->Rchild);
    }
}



void InOrderThreading(BiTree * ThHead,BiTree T)
{
    //ThHead为线索二叉树的头结点
    *ThHead = (BiTree)malloc(sizeof(struct BitNode));
    if(NULL == *ThHead)
    {
        printf("Can not assign the space for *ThHead");
        exit(1);

    }
    
    (*ThHead)->Ltag = Link;      //根结点的左标记配置为link 
    (*ThHead)->Rtag = Thread;    //根结点的右标记配置为Thread;
    
    (*ThHead)->Rchild = (*ThHead); //将有子树指向自己
    
    if(NULL == T)                  //要是二叉树不存在，将左子树结点也指向自己
        (*ThHead)->Lchild = (*ThHead);
    else
    {
        pre = (*ThHead);          //将头结点配置为前驱
        (*ThHead)->Lchild = T;
        InThreading(T);           //找到二叉树中最后一个结点
        pre->Rtag = Thread;
        pre->Rchild = (*ThHead);
        (*ThHead)->Rchild = pre;
    }
    
}

void InThreading(BiTree T)
{
    if(T)
    {
        InThreading(T->Lchild);  //递归发现最后一个左子树
        if(!T->Lchild)
        {
            T->Ltag = Thread;
            T->Lchild = pre;
        }
        if(!pre->Rchild)
        {
            pre->Rtag = Thread;
            pre->Rchild = T;

        }

        pre = T;
        InThreading(T->Rchild);
    }
}

void InOrderTraverse1(BiTree T)
{
    BiTree temp;
    temp = T->Lchild;
    
    while(temp != T)
    {
        while(temp->Ltag == Link)
            temp = temp->Lchild;
        
         printf("%d",temp->data);
        
        while(temp->Rtag == Thread && temp->Rchild != T)
        {

            temp = temp->Rchild;
            printf("%d",temp->data);
        }
        temp = temp->Rchild;

    }


}



void PreOrderThreading(BiTree * ThH,BiTree T)
{
    *ThH =(BiTree)malloc(sizeof(struct BitNode));
    if(NULL == *ThH)
    {
        printf("Can not assign the space for *ThH");
        exit(1);
    }
    
    (*ThH)->Ltag = Link;
    (*ThH)->Rtag = Thread;
    (*ThH)->Rchild = *ThH;
    if(!T)
        (*ThH)->Lchild = *ThH;
    else
    {
        (*ThH)->Lchild = T;
        pre = *ThH;
        PreThreading(T);
        pre->Rtag = Thread;
        pre->Rchild = *ThH;
        (*ThH)->Rchild = pre;
    }

}

void PreThreading(BiTree T)
{
    if(!pre->Rchild)
    {
        pre->Rtag = Thread;
        pre->Rchild = T;
    }
    if(!T->Lchild)
    {
        T->Ltag = Thread;
        T->Lchild = pre;
    }
    pre = T;
    if(NULL != T->Lchild)
        PreThreading(T->Lchild);
    if(NULL != T->Rchild)
        PreThreading(T->Rchild);


}


void PreOrderTraverse1(BiTree T)
{
    BiTree temp;
    temp = T->Lchild;
    while(temp != T)
    {
        printf("%d",temp->data);
        if(temp->Ltag == Link)
            temp = temp->Lchild;
        else
            temp = temp->Rchild;

    }

}

void PostOrderThreading(BiTree * PthH,BiTree T)
{
    *PthH = (BiTree)malloc(sizeof(struct BitNode));
    if(NULL == *PthH)
    {
        printf("Can not assign the space for *PthH");
        exit(1);

    }

    (*PthH)->Ltag = Link;
    (*PthH)->Rtag = Thread;
    if(!T)
    {
        (*PthH)->Lchild = (*PthH);
        (*PthH)->Rchild = (*PthH);
    
    }
    else
    {
        (*PthH)->Rchild = T;
        (*PthH)->Lchild = T;
        pre = (*PthH);
        PostThreading(T);
        if(pre->Rtag != Link)
        {
            pre->Rtag = Thread;
            pre->Rchild = *PthH;
        }

    }

}

void PostThreading(BiTree T)
{
    if(T)
    {
        PostThreading(T->Lchild);
        PostThreading(T->Rchild);
        if(!T->Lchild)
        {
            T->Ltag = Thread;
            T->Lchild = pre;
        }
        if(!pre->Rchild)
        {
            pre->Rtag = Thread;
            pre->Rchild = T;
        }

        pre = T;

    }

}


void DestroyBiTree(BiTree * T)
{
    if(*T)
    {
        if((*T)->Ltag == Link)
            DestroyBiTree(&(*T)->Lchild);
        if((*T)->Rtag == Link)
            DestroyBiTree(&(*T)->Rchild);
        
        free(*T);
        *T = NULL;
    }
}
    
void DestroyBiThTree(BiTree * T)
{
    if(*T)
    {
        if((*T)->Lchild)
            DestroyBiTree(&(*T)->Lchild);

        free(*T);
        *T = NULL;
    }

}





