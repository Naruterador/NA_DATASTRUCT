/*
二叉树的三叉链表实现


*/
#include "stack.h"
#include "queue1.h"
void InitBiTree(BiTree);
void DestroyBitTree(BiTree *);
void CreateBiTree(BiTree *);
bool BiTreeEmpty(BiTree);
int BiTreeDepth(BiTree);
int Value(BiTree);
void Assign(BiTree,int);
BiTree Point(BiTree,int);
int Parent(BiTree,int);


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





int main(void)
{





    return 0;
}



void CreateBiTree(BiTree * T)
{
    int data;
    scanf("%d",data);
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
