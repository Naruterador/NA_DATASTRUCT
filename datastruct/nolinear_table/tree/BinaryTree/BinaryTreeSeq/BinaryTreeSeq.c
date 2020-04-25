/*

在顺序存储结构中,第 i 层结点的序号从 2^(i-1)-1～2^(i)-2；
序号为 i 的结点，其双亲序号为(i+1)/2-1，其左右孩子序号分别为 2i+1 和 2i+2；除了根结点
序号为奇数的结点是其双亲的左孩子，它的右兄弟的序号是它的序号+1；序号为偶数的结点是其
双亲的右孩子，它的左兄弟的序号是它的序号-1；i 层的满二叉树，其结点总数为 2i-1。

*/

#include "queue2.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <math.h>



#define MAX_TREE_SIZE 100 //二叉树的最大节点数
//#define CHAR 1 //代表字符型
#define CHAR 0 //代表数字型

#if CHAR
    typedef char TElemType;
    TElemType Nil = ' ';  //字符串以空格为空
#else
    typedef int TElemType;
    TElemType Nil = 0;   //数字以0为空
#endif






typedef TElemType SqBiTree[MAX_TREE_SIZE];  //二叉树的存储空间

struct position
{

    int level; //结点的层
    int order; //本层的序号(按照满二叉树计算)

};


void InitTree(SqBiTree);  //构造一棵空树
void DestoryTree(SqBiTree); //销毁一棵树
void CreateTree(SqBiTree); //创建一棵树
void ClearTree(SqBiTree);    //清空一棵树
bool IsTreeEmpty(SqBiTree);  //判断树是否为空
int TreeDepth(SqBiTree);     //如果树存在返回树的深度
TElemType Root(SqBiTree);    //如果树存在，返回树的根
TElemType Value(SqBiTree,struct position); //如果e是树中的某个结点，返回节点的值
void Assign(SqBiTree,struct position,int value); //如果e是树中的某个结点，将结点e赋值为value

TElemType Parent(SqBiTree T,TElemType e); //如果e是树中的某个非根结点，返回这个非根结点的双亲
TElemType LeftChild(SqBiTree T,TElemType e); //如果e是树中某个非叶子结点，则返回这个结点的左孩子
TElemType RightChild(SqBiTree T,TElemType e); //如果e是树中某个非叶子结点，则返回这个结点的右孩子
TElemType LeftSibling(SqBiTree T,TElemType e); //如果e是树中某个结点，返回e的兄弟若e是T的左孩子或无左兄弟，则返回空
TElemType RightSibling(SqBiTree T,TElemType e);  //如果e是树中某个结点，返回e的右兄弟，若e是T的右孩子或者无右兄弟，则返回空





void (*VisitFunc)(TElemType);
void visit(TElemType e);
//先序遍历
void PreTraverse(SqBiTree T,int e);
void PreOrderTraverse(SqBiTree T,void(*Visit)(TElemType));


//中序遍历
void InTraverse(SqBiTree T,int e);
void InOrderTraverse(SqBiTree T,void(*Visit)(TElemType));

//后序遍历
void PostTraverse(SqBiTree T,int e);
void PostOrderTraverse(SqBiTree T,void(*Visit)(TElemType));

//层序遍历
void LevelOrderTraverse(SqBiTree T);


void Move(SqBiTree q,int j,SqBiTree T,int i); // InsertChild用到，如把从q的j结点开始的子树移为从T的i结点开始的子树
void InsertChild(SqBiTree T,TElemType p,int LR,SqBiTree c);
void DeleteChile(SqBiTree T,int LR,struct position);
void TraverseTree(SqBiTree T); //遍历整棵树
void PrintTree(SqBiTree); //逐层、按本层序号输出二叉树

int main(void)
{
    
    TElemType e;
    SqBiTree T;
    SqBiTree q;
    struct position p = {3,2};
    CreateTree(T);
    int len = TreeDepth(T);
    //CreateTree(q);
    //InsertChild(T,2,1,q);
    //DeleteChile(T,0,p);
    //PrintTree(T);
    printf("%d",len);
    return 0;
}


//初始化一棵树
void InitTree(SqBiTree T)
{
    int i = 0;
    for(i = 0;i < MAX_TREE_SIZE;i++)
        T[i] = Nil;

}

void CreateTree(SqBiTree T)
{
    int i = 0;
    InitTree(T);
    
#if CHAR
   int len;
   char s[MAX_TREE_SIZE];
   printf("请按层序输入结点的值(字符),空格表示空结点，结点数量不能大于%d",MAX_TREE_SIZE);
   get(s);
   len = strlen(s);
   for(i = 0;i < len;i++)
     T[i] = s[i];
#else
   while(1)
   {
      
      printf("请按层次输入结点的值(数字)，0表示空结点，结点数量不能大于%d,输入值为999代表输入结束",MAX_TREE_SIZE);
      scanf("%d",&T[i]);
      if(T[i] == 999)
      {
        T[i] = Nil;
        break;
      }
      i++;
   }
#endif
   
   //判断树中是否存在无双亲的非根结点
   for(i = 1;i < MAX_TREE_SIZE;i++)
   {
        if(i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil)
        {
            printf("出现非根结点无双亲%d",i);
            exit(1);
        }
   }
        
}


void LevelOrderTraverse(SqBiTree T)
{
    int i = 0;
    int length;
    
    //获取当前树的结点数量，包含空结点
    for(i = MAX_TREE_SIZE - 1;i >= 0;i--)
        if(T[i] != Nil)
        {   
            length = i + 1;
            break;
        }
    for(i = 0;i < length;i++)
        printf("%d ",T[i]);    
}



bool IsTreeEmpty(SqBiTree T)
{
    //判断树根是否为空
    if(T[0] == Nil)
        return true;
    else
        return false;
}


int TreeDepth(SqBiTree T)
{
    int i;
    int j = 0;
    
    for(i = MAX_TREE_SIZE - 1;i >= 0; i--)
        if(T[i] != Nil)
            break;
    i++;
    
    
    while(i >= pow(2,j))
        j++;

    return j;
}



TElemType Root(SqBiTree T)
{
    if(IsTreeEmpty(T))
    {
        printf("这棵树为空树");
        exit(1);
    }

    return T[0];
}




TElemType Value(SqBiTree T,struct position p)
{

    return T[(int)(pow(2,p.level - 1) + p.order - 2)];

}

void Assign(SqBiTree T,struct position p,int value)
{
    int i;
    i = (int)(pow(2,p.level - 1) + p.order - 2);

    //给叶子结点赋值，但是双亲为空
    if(value != Nil && T[(i + 1) / 2 - 1] == Nil)
    {
        printf("此节点没有双亲！");
        exit(1);
    }

    //给双亲赋空值，但这个双亲不含左子树或右子树
    if(value == Nil && (T[2 * i + 1] != Nil || T[2 * i + 2] != Nil))
    {
        printf("双亲为空的结点不会存在左子数或者右子数！");
        exit(1);
    }

    T[i] = value;
}

TElemType Parent(SqBiTree T,TElemType e)
{
    if(IsTreeEmpty(T))
    {
        printf("树为空！");
        exit(1);
    }
    
    int i;
    for(i = 1;i < MAX_TREE_SIZE;i++)
        if(T[i] == e)
            return T[(i + 1) / 2 - 1];
    
    return Nil;

}





TElemType LeftChild(SqBiTree T, TElemType e)
{
    if(IsTreeEmpty(T))
    {
        printf("树为空！");
        exit(1);
    }
    
    int i;
    for(i = 1;i < MAX_TREE_SIZE;i++)
        if(T[i] == e)
            return T[2 * i + 1];
    
    return Nil;
}


TElemType RightChild(SqBiTree T,TElemType e)
{
    if(IsTreeEmpty(T))
    {
        printf("树为空！");
        exit(1);
    }

    int i;
    for(i = 1;i < MAX_TREE_SIZE;i++)
        if(T[i] == e)
            return T[2 * i + 2];
    
    return Nil;
}



void visit(TElemType e)
{
    printf("%d",e);
}

//先序遍历
void (*VisitFunc)(TElemType);
void PreTraverse(SqBiTree T,int e)
{
    VisitFunc(T[e]);
    if(T[2 * e + 1] != Nil)
        PreTraverse(T,2 * e + 1);
    if(T[2 * e + 2] != Nil)
        PreTraverse(T,2 * e + 2);
}

void PreOrderTraverse(SqBiTree T,void(*Visit)(TElemType))
{
    VisitFunc = Visit;
    if(!IsTreeEmpty(T))
    {
        PreTraverse(T,0);
    }
    else
        printf("此树为空树!");
}


//中序遍历
void InTraverse(SqBiTree T,int e)
{
 
    if(T[2 * e + 1] != Nil)
        InTraverse(T,2 * e + 1);
    VisitFunc(T[e]);
    if(T[2 * e + 2] != Nil)
        InTraverse(T,2 * e + 2);
}

void InOrderTraverse(SqBiTree T,void(*Visit)(TElemType))
{
    VisitFunc = Visit;
    if(!IsTreeEmpty(T))
    {
        InTraverse(T,0);
    }
    else
        printf("此树为空树！");

}



//后序遍历
void PostTraverse(SqBiTree T,int e)
{
    if(T[2 * e + 1] != Nil)
        PostTraverse(T,2 * e + 1);
    
    if(T[2 * e + 2] != Nil)
        PostTraverse(T,2 * e + 2);
    
    VisitFunc(T[e]);
}

void PostOrderTraverse(SqBiTree T,void(*Visit)(TElemType))
{
    VisitFunc = Visit;
    if(!IsTreeEmpty(T))
    {
        PostTraverse(T,0);
    }
    else
        printf("此树为空");
}


void PrintTree(SqBiTree T)
{
    struct position p;
    //层数
    int j;
    int k;
    TElemType e;
    
    int hight = 0;
    
    hight = TreeDepth(T);
    
    for(j = 1;j <= hight;j ++)
    {

        printf("第%d层",j);
        
        for(k = 1;k <= pow(2,j - 1);k++)
        {
            p.level = j;
            p.order = k;
            e = Value(T,p);
            if(e != Nil)
                printf("%d ",e);
        }
        printf("\n");
    }

}


void Move(SqBiTree q,int j,SqBiTree T,int i) // InsertChild用到，如把从q的j结点开始的子树移为从T的i结点开始的子树
{
    if(q[2 * j + 1] != Nil)
        Move(q,2 * j + 1,T,2 * i + 1);

    if(q[2 * j + 2] != Nil)
        Move(q,2 * j + 2,T,2 * i + 2);
    
    T[i] = q[j]; //把q的结点移动到T上
    q[j] = Nil;  //移动完成后将q结点赋空
}



void InsertChild(SqBiTree T,TElemType p,int LR,SqBiTree c)
{
    int j;
    int k;
    int i = 0;
    int length = (int)(pow(2,TreeDepth(T))) - 1;
    for(j = 0;j < length;j++)
        if(T[j] == p)
            break;
     
    k = 2 * j + 1 + LR;
    if(T[k] != Nil)
        Move(T,k,T,2 * k + 2);
    Move(c,i,T,k);
}



void DeleteChile(SqBiTree T,int LR,struct position p)
{
    int i;
    struct queue2 delqueue;
    init_queue(&delqueue,MAX_TREE_SIZE);
    

    i = (int)(pow(2,p.level -1)) + p.order - 2;
    
    if(T[i] == Nil)
    {
        printf("This point is empty!");
        exit(1);
    }
    
    i = i * 2 + 1;
    if(T[i] != Nil)
        insert_queue(&delqueue,i);
    
    while(!is_empty(&delqueue))
    {
        if(T[2 * i + 1] != Nil)
            insert_queue(&delqueue,2 * i + 1);
        if(T[2 * i + 2] != Nil)
            insert_queue(&delqueue,2 * i + 2);
        
        T[i] = Nil;
        i = delete_queue(&delqueue);
    }
}
