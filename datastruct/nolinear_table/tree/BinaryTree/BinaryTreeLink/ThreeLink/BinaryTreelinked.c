/*
二叉树的三叉链表实现


*/
#include "queue1.h"
#include "stack.h"


void InitBiTree(BiTree *);
void DestroyBitTree(BiTree *);
void CreateBiTree(BiTree *);
bool BiTreeEmpty(BiTree);
int BiTreeDepth(BiTree);
int Value(BiTree);
void Assign(BiTree,int);
BiTree Point(BiTree,int);


//使用队列实现
int Parent1(BiTree,int);
//使用递归实现
int Parent2(BiTree,int);

int LeftChild(BiTree,int);
int RightChild(BiTree,int);
int LeftSibling(BiTree,int);
int RightSibling(BiTree,int);


void InsertChild(BiTree T,int LR,BiTree c);
void DeleteChild(BiTree,int LR);

void PreOrderTraverse(BiTree);
void InOrderTraverse(BiTree);
void PostTraverse(BiTree);
void LevelOrderTraverse(BiTree);


void InOrderTraverse1(BiTree);
void InOrderTraverse2(BiTree);

void Copy(BiTree T,BiTree * N);
int NodeCount(BiTree);
int  LeafCount(BiTree);





int main(void)
{
    int i;
    BiTree T;
    BiTree N;
    InitBiTree(&T);
    InitBiTree(&N);
    CreateBiTree(&T);
    //LevelOrderTraverse(T);
    //PostTraverse(T);
    //InOrderTraverse(T);
    Copy(T,&N);
    //PreOrderTraverse(N);
    //i = LeftSibling(T,2);
    


    return 0;
}


void InitBiTree(BiTree * T)
{

    T = NULL;
}

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
        *T = (BiTree)malloc(sizeof(struct BitNode));
        if(NULL == *T)
        {
            printf("Can not assign the space for *T");
            exit(1);

        }
        (*T)->data = data;
        (*T)->parent = NULL;
        CreateBiTree(&(*T)->lchild);
        if((*T)->lchild)
            (*T)->lchild->parent = *T;
        CreateBiTree(&(*T)->rchild);
        if((*T)->rchild)
            (*T)->rchild->parent = *T;
    }

}


void DestroyBitTree(BiTree * T)
{
    if((*T)->lchild)
        DestroyBitTree(&(*T)->lchild);

    if((*T)->rchild)
        DestroyBitTree(&(*T)->rchild);
    
    free(*T);
    *T = NULL;
        
}

bool BiTreeEmpty(BiTree T)
{

    if(NULL == T)
        return true;
    return false;

}


int BiTreeDepth(BiTree T)
{
    int i;
    int j;
    
    if(NULL != T->lchild)
        i = BiTreeDepth(T->lchild);
    else
        i = 0;

    if(NULL != T->rchild)
        j = BiTreeDepth(T->rchild);
    else
        j = 0;

    return i > j? i + 1:j + 1;
}


int Value(BiTree T)
{

    return T->data;
}

void Assign(BiTree T,int c)
{
    

    T->data = c;
}

//Method 1
int Parent1(BiTree T,int e)
{
    BiTree temp;
    struct queue2 queue;
    init_queue(&queue,100);
    insert_queue(&queue,T); 
    
    while(!is_empty(&queue))
    {
        temp = delete_queue(&queue);
        if(temp->data == e)
            return temp->parent->data;
        else
        {
            if(NULL != temp->lchild)
                insert_queue(&queue,temp->lchild);
            
            if(NULL != temp->rchild)
                insert_queue(&queue,temp->rchild);
        }
    }
    return 0;
}


BiTree Point(BiTree T,int e)
{
    BiTree temp;
    struct queue2 queue;
    init_queue(&queue,100);
    insert_queue(&queue,T);
    
    while(!is_empty(&queue))
    {
        temp = delete_queue(&queue);
        
        if(temp->data == e)
            return temp;

        else
        {
            if(NULL != temp->lchild)
                insert_queue(&queue,temp->lchild);

            if(NULL != temp->rchild)
                insert_queue(&queue,temp->rchild);
        }

    }

    return NULL;
}

int LeftChild(BiTree T,int e)
{
   
    BiTree Left;
    
    Left = Point(T,e);

    if(NULL != Left->lchild)
        return Left->lchild->data;

    return 0;
}


int RightChild(BiTree T,int e)
{


    BiTree Right;
    
    Right = Point(T,e);

    if(NULL != Right->lchild)
        return Right->lchild->data;

    return 0;
}



int LeftSibling(BiTree T,int e)
{
    BiTree p;
    
    if(NULL != T)
    {    
        p = Point(T,e);
        
        if(NULL != p->parent && NULL != p->parent->rchild)
            return p->parent->rchild->data;
    
    }
    return 0;
}


int RightSibling(BiTree T,int e)
{

    BiTree p;
    
    if(NULL != T)
    {    
        p = Point(T,e);
        
        if(NULL != p->parent && NULL != p->parent->lchild)
            return p->parent->lchild->data;
    
    }
    return 0;

}


void PreOrderTraverse(BiTree T)
{
    
    printf("%d",T->data);
    if(NULL != T->lchild)
        PreOrderTraverse(T->lchild);
    if(NULL != T->rchild)
        PreOrderTraverse(T->rchild);
}


void InOrderTraverse(BiTree T)
{
    if(NULL != T->lchild)
        InOrderTraverse(T->lchild);
    printf("%d",T->data);

    if(NULL != T->rchild)
        InOrderTraverse(T->rchild);
    
}


void PostTraverse(BiTree T)
{
    if(NULL != T->lchild)
        PostTraverse(T->lchild);
    if(NULL != T->rchild)
        PostTraverse(T->rchild);
    printf("%d",T->data);

}


void LevelOrderTraverse(BiTree T)
{
    BiTree p;
    struct queue2 queue;
    //最好使用循环队列
    init_queue(&queue,100);
    insert_queue(&queue,T);
    
    while(!is_empty(&queue))
    {
        p = delete_queue(&queue);
        if(p)
            printf("%d",p->data);
        
        if(p->lchild)
        {
            insert_queue(&queue,p->lchild);
        }

        if(p->rchild)
        {
            insert_queue(&queue,p->rchild);
        }

    }
}

//使用栈实现中序遍历方法1
void InOrderTraverse1(BiTree T)
{
    struct stack st1;
    init_stack(&st1);

    while(T || !is_stackempty(&st1))
    {
        
        if(T)
        {
            push_el(&st1,T);
            T = T->lchild; 

        }
        else
        {
            T = pop_el(&st1);
            printf("%d",T->data);
            T = T->rchild;

        }

    }
}

//T为原二叉树，C为新的树
void InsertChild(BiTree T,int LR,BiTree C)
{    
    //如果T存在
    if(T)
    {
        //新二叉树C作为T的左子树插入LR = 0
        if(LR == 0)
        {
            //将原树的左子树，放到新树的右子树上
            C->rchild = T->lchild;
            if(C->rchild)
                //如果新树C的右子树存在,将插入新树c的右子树的双亲域改成c
                C->rchild->parent = C;
            //将新树c链接到老树T的左儿子域
            T->lchild = C;
            //修改C的双亲结点,指向原树T
            C->parent = T;
        }
        
        //作为右子树插入
        if(LR == 1)
        {
            C->rchild = T->rchild;
            if(C->rchild)
                C->rchild->parent = C;
            T->rchild = C;
            C->parent = T;

        }

    }
}



void DeleteChild(BiTree T,int LR)
{
    if(LR == 0)
        DestroyBitTree(&T->lchild);

    if(LR == 1)
        DestroyBitTree(&T->rchild);
}



void Copy(BiTree T,BiTree * N)
{
    if(T == NULL)
        *N = NULL;
    else
    {
        *N = (BiTree)malloc(sizeof(BitNode));
        if(*N == NULL)
        {
            printf("Can not assign the space for the *N");
            exit(1);
        }
        (*N)->data = T->data;  
        (*N)->parent = NULL;
        
        Copy(T->lchild,&(*N)->lchild);
        
        if((*N)->lchild)
            (*N)->lchild->parent = *N;
        
        Copy(T->rchild,&(*N)->rchild);
        
        if((*N)->rchild)
            (*N)->rchild->parent = *N;

    }

}



int NodeCount(BiTree T)
{
    if(T == NULL)
        return 0;
    else
        return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

int  LeafCount(BiTree T)
{
    if(T == NULL)
        return 0;
    
    if(T->lchild == NULL && T->rchild == NULL)
        return 1;
    else
        return LeafCount(T->lchild) + LeafCount(T->rchild);
}
