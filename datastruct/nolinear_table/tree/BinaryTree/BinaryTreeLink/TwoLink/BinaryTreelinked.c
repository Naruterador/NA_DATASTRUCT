/*
    链式结构实现二叉树的操作
*/
#include "queue1.h"
#include "stack.h"


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
BitNode * Point(BiTree,int s);
//返回二叉树T中e结点左孩子的值
int LeftChild(BiTree T,int e);
//返回二叉树T中e结点右孩子的值
int RightChild(BiTree T,int e);
//返回二叉树T中e结点左兄弟的值，如果兄弟不存在返回0
int LeftSibling(BiTree T,int e);
//返回二叉树T中e结点右兄弟的值，如果兄弟不存在返回0
int RightSibling(BiTree T,int e);



//向二叉树T中插入某个结点
void InsertChild(BiTree p,int LR,BiTree c);
//删除二叉树中某个结点
void DeleteChild(BiTree p,int LR);

//中序遍历二叉树方法1(非递归)
void InOrderTraverse1(BiTree);
//中序遍历二叉树方法2(非递归),效率低于第一种
void InOrderTraverse2(BiTree);


//返回树的深度
int BiTreeDepth(BiTree);
//树的先序遍历
void PreOrderTraverse(BiTree);
//树的中序遍历
void InOrderTraverse(BiTree);
//树的后序遍历
void PostOrderTraverGe(BiTree);
//层序遍历
void LevelOdrderTraverse(BiTree);


//将二叉树T复制到二叉树N
void Copy(BiTree T,BiTree * N);

//递归计算二叉树结点总个数
int NodeCount(BiTree);

//递归计算二叉树叶子结点个数
int LeafCount(BiTree);



int main(void)
{
    int leftchild;
    int count;
    int leaf;
    BitNode p;
    p.data = 100;
    p.leftchild = NULL;
    p.rightchild = NULL;
    BiTree T;
    BiTree N;
    InitBiTree(&T);
    InitBiTree(&N);
    CreateBiTree(&T);
    //PreOrderTraverse(T);
    //InOrderTraverse(T);
    //PostOrderTraverse(T);
    //rightsilbing = RightSibling(T,4);
    //InsertChild(T,0,&p);
    //leftchild = LeftChild(T,1);
    //printf("%d",leftchild);
    //InOrderTraverse1(T);
    //LevelOdrderTraverse(T);
    //Copy(T,&N);
    //LevelOdrderTraverse(N);
    
    leaf = LeafCount(T);
    printf("%d",leaf);



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


BitNode * Point(BiTree T,int s)
{
    BitNode *  temp;
    struct queue2 queue;
    if(T)
    {   
       init_queue(&queue,100);
       insert_queue(&queue,T);
       while(!is_empty(&queue))
       {
            temp = delete_queue(&queue);
            if(temp->data == s)
                return temp;
            else
                {
                    if(temp->leftchild)
                        insert_queue(&queue,temp->leftchild);
                    if(temp->rightchild)
                        insert_queue(&queue,temp->rightchild);
                }

       }
    }

    return NULL;
}


    

int LeftChild(BiTree T,int e)
{
    BitNode * a;
    
    a = Point(T,e);
    
    if(a && a->data == e)
      return a->leftchild->data;  

    return 0;
}




int RightChild(BiTree T,int e)
{
    BitNode * b;
    b = Point(T,e);
    if(b && b->data == e)
        return b->rightchild->data;

    return 0;

}



int LeftSibling(BiTree T,int e)
{
   //当前结点e的父结点值
   int p; 
   //父结点指针
   BitNode * lpp = NULL;
    
   p = Parent(T,e);
   if(p != 0)
    lpp = Point(T,p);
   
   if(lpp && lpp->rightchild->data == e)
        return lpp->leftchild->data;
   
    return 0;

}


int RightSibling(BiTree T,int e)
{

   //当前结点e的父结点值
   int p; 
   //父结点指针
   BitNode * rpp = NULL;
    
   p = Parent(T,e);
   if(p != 0)
    rpp = Point(T,p);
   
   if(rpp && rpp->leftchild->data == e)
        return rpp->rightchild->data;
   
    return 0;

}



void InsertChild(BiTree p,int LR,BiTree c)
{
    if(p)
    {
        //新树c作为左儿子插入
        if(LR == 0)
        {   
            c->rightchild = p->leftchild;
            p->leftchild = c;
        }
        //新树c作为右儿子插入
        if(LR == 1)
        {
            c->rightchild = p->rightchild;
            p->rightchild = c;

        }

    }

}



void DeleteChild(BiTree p,int LR)
{
    if(p)
    {
        if(LR == 0)
            DestroyBiTree(&p->leftchild);
        else
            DestroyBiTree(&p->rightchild);

    }

}





void InOrderTraverse1(BiTree T)
{
    //创建一个栈
    struct stack sta;
    init_stack(&sta); 
    
    while(T || !is_stackempty(&sta))
    {
        if(T)
        {
            push_el(&sta,T);
            T = T->leftchild;
        }
        else
        {
            T = pop_el(&sta);
            printf("%d",T->data);
            T = T->rightchild;
        }

    }
}


void InOrderTraverse2(BiTree T)
{
    struct stack sta;
    BiTree p;
    
    init_stack(&sta);

    if(T)
     push_el(&sta,T);
    else
    {
        printf("ERROR:can not find Tree!");
        exit(1);
    }
    
    while(!is_stackempty(&sta))
    {  
       p = GetTop(&sta);
       while(p)
       {
            push_el(&sta,p->leftchild);
            p = GetTop(&sta);
       }
       pop_el(&sta); //弹出空栈
       if(!is_stackempty(&sta))
       {         
            p = pop_el(&sta);
            printf("%d",p->data);
            push_el(&sta,p->rightchild);
       }

    }
}




void LevelOdrderTraverse(BiTree T)
{
   BitNode * p;
   struct queue2 queue;
   
   init_queue(&queue,100);
   insert_queue(&queue,T);
   
   while(!is_empty(&queue))
   {
        p = delete_queue(&queue);
        printf("%d",p->data);
        
        if(p->leftchild)
            insert_queue(&queue,p->leftchild);

        if(p->rightchild)
            insert_queue(&queue,p->rightchild);

   }
}





void Copy(BiTree T,BiTree * N)
{
    if(T == NULL)
    {
        N = NULL;
    }
    else
    {
      *N = (BiTree)malloc(sizeof(BitNode));
      if(NULL == *N)
      {
        printf("ERROR:Can not assign the space for *N");
        exit(1);
      }
      (*N)->data = T->data; 
      Copy(T->leftchild,&(*N)->leftchild);
      Copy(T->rightchild,&(*N)->rightchild);
    }

}



int NodeCount(BiTree T)
{
    if(T == NULL)
        return 0;
    
    return NodeCount(T->leftchild) + NodeCount(T->rightchild) + 1;

}



int LeafCount(BiTree T)
{
    if(T == NULL)
        return 0;
    if(T->leftchild == NULL && T->rightchild == NULL)
        return 1;
    
    return LeafCount(T->leftchild) + LeafCount(T->rightchild);

}
