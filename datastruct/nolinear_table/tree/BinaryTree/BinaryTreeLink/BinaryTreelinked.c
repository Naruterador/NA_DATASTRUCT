/*
    链式结构实现二叉树的操作
*/

#include "queue1.h"




//构造一棵空树
void InitBiTree(BiTree *);
//销毁二叉树
void DestroyBiTree(BiTree *);
//创建一棵二叉树
void CreateBiTree(BiTree *);
//判断二叉树是否为空
bool IsTreeEmpty(BiTree);

//返回树的根
int Root(BiTree);
//返回树中某个结点的值
int Value(BiTree);
//为树中某个节点赋值
void Assign(BiTree,int value);


//返回树中某个结点的双亲结点
int Parent(BiTree,int);
//返回二叉树T中指向元素值为s的结点指针
BitNode Point(BiTree,int s);

//返回树的深度
int BiTreeDepth(BiTree);
//树的先序遍历
void PreOrderTraverse(BiTree);
//树的中序遍历
void InOrderTraverse(BiTree);
//树的后序遍历
void PostOrderTraverGe(BiTree);



int main(void)
{
    int parent;
    BitNode root;
    BiTree T;
    InitBiTree(&T);
    CreateBiTree(&T);
    parent = BiTreeDepth(T);
    //PreOrderTraverse(T);
    //InOrderTraverse(T);
    //PostOrderTraverse(T);
    parent = Parent(T,6);
    printf("%d",parent);
    



    return 0;
}


void InitBiTree(BiTree * T)
{
    *T = NULL;
}


//先序创建二叉树
void CreateBiTree(BiTree * T)
{
 int data;
 
 scanf("%d",&data);
 if(0 == data)
 {
    T = NULL;
 }
 else
 {
    *T = (BitNode *)malloc(sizeof(BitNode));
    if(NULL == *T)
    {
        printf("Can not assign the space for T");
        exit(1);
    }
    (*T)->data = data;
    CreateBiTree(&(*T)->leftchild);
    CreateBiTree(&(*T)->rightchild);
 }
}


bool IsTreeEmpty(BiTree T)
{
    if(NULL == T)
        return true;
    return false;
}

void DestroyBiTree(BiTree * T)
{
    if((*T)->leftchild != NULL)
        DestroyBiTree(&(*T)->leftchild);
    if((*T)->rightchild != NULL)
        DestroyBiTree(&(*T)->rightchild);
    free(T);
    T = NULL;
}



int BiTreeDepth(BiTree T)
{
    int i;
    int j;

    if(T->leftchild != NULL)
        i = BiTreeDepth(T->leftchild);
    else
        i = 0;

    if(T->rightchild != NULL)
        j = BiTreeDepth(T->rightchild);
    else
        j = 0;
    
    return i > j?i + 1: j + 1;
}



void PreOrderTraverse(BiTree T)
{
    if(NULL != T)
    {
        printf("%d",T->data);
        PreOrderTraverse(T->leftchild);
        PreOrderTraverse(T->rightchild);
    }

}



void InOrderTraverse(BiTree T)
{
    if(NULL != T)
    {
        InOrderTraverse(T->leftchild);
        printf("%d",T->data);
        InOrderTraverse(T->rightchild);

    }
}


void PostOrderTraverse(BiTree T)
{
    if(NULL != T)
    {
        PostOrderTraverse(T->leftchild);
        PostOrderTraverse(T->rightchild);
        printf("%d",T->data);
    }
}


int Root(BiTree T)
{
    if(NULL == T)
        return 0;
    
    return T->data;
}

int Value(BiTree T)
{
    return T->data;
}

void Assign(BiTree T,int value)
{
    T->data = value;
}

int Parent(BiTree T,int e)
{
   BitNode * temp;
   struct queue2 queue;
   //初始化队列用于存放树中的结点
   init_queue(&queue,100);
   insert_queue(&queue,T);
   
   while(!is_empty(&queue))
   {
        temp = delete_queue(&queue);
        if((temp->leftchild && temp->leftchild->data == e) || (temp->rightchild && temp->rightchild->data == e))
            return temp->data;
        else
            {
                if(temp->leftchild)
                    insert_queue(&queue,temp->leftchild);

                if(temp->rightchild)
                    insert_queue(&queue,temp->rightchild);
            }
   }
   //返回0表示没有找到双亲结点
   return 0;
}


BitNode Point(BiTree T,int s)
{
    BitNode * temp;
    struct queue2 queue;
    if(T)
    {   
       init_queue(&queue,100);
       insert_queue(&queue,T);
       while(!is_empty(&queue))
       {
            temp = delete_queue(&queue);
            if(temp->data == s)
                return *temp;
            else
                {
                    if(temp->leftchild)
                        insert_queue(&queue,temp);
                    if(temp->rightchild)
                        insert_queue(&queue,temp);



                }





       }
    }

    temp == NULL;
    return *temp;
}


