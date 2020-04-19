/*

在顺序存储结构中,第 i 层结点的序号从 2^(i-1)-1～2^(i)-2；
序号为 i 的结点，其双亲序号为(i+1)/2-1，其左右孩子序号分别为 2i+1 和 2i+2；除了根结点
序号为奇数的结点是其双亲的左孩子，它的右兄弟的序号是它的序号+1；序号为偶数的结点是其
双亲的右孩子，它的左兄弟的序号是它的序号-1；i 层的满二叉树，其结点总数为 2i-1。

*/


#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
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
TElemType Value(SqBiTree,int e); //如果e是树中的某个结点，返回节点的值
void Assign(SqBiTree,int e,int value); //如果e是树中的某个结点，将结点e赋值为value
TElemType Parent(SqBiTree,int e); //如果e是树中的某个非根结点，返回这个非根结点的双亲
TElemType LeftChild(SqBiTree,int e); //如果e是树中某个非叶子结点，则返回这个结点的左孩子
TElemType RightChild(SqBiTree,int e); //如果e是树中某个非叶子结点，则返回这个结点的右孩子


void InsertChild(SqBiTree T,TElemType p,int position);
void DeleteChile(SqBiTree T,TElemType p,int position);
void TraverseTree(SqBiTree T); //遍历整棵树
void PrintTree(SqBiTree);

int main(void)
{
    
    TElemType e;
    SqBiTree T;
    CreateTree(T);
    int count = TreeDepth(T);
    e = Value(T,3);
    printf("%d",e);
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



void PrintTree(SqBiTree T)
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
    int j = -1;
    
    for(i = MAX_TREE_SIZE - 1;i >= 0; i--)
        if(T[i] != Nil)
            break;
    i++;
    
    do{
        j++;
    }while(i >= pow(2,j));
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




TElemType Value(SqBiTree T,int e)
{

    int i;
    for(i = MAX_TREE_SIZE - 1;i >= 0;i--)
        if(T[i] != Nil)
            break;
    i++;

    if(e < 0 || e > i)
    {
        printf("不能找到这个结点");
        exit(1);
    }
    return T[e];
}

