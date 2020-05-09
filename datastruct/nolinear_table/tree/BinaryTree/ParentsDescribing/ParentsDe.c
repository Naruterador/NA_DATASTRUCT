/*

树的双亲表示法实现


*/


#include "queue.h"


//构造空树T
void InitTree(BiTree * T);
//构造树T
void CreateTree(BiTree * T);
//判断树是否为空
bool isTempty(BiTree T);
//返回树的深度算法1
int TreeDepth1(BiTree T);
//返回树的深度算法2
int TreeDepth2(BiTree T);
//如果树T存在,返回T的根
char Root(BiTree);
//返回树中第i个结点的值
char Value(BiTree,int);
//改变树中某一结点的值
void Assign(BiTree,char,char);
//返回树中结点的父结点的值
char Parent(BiTree,char);
//返回二叉树中某个结点的左孩子
char LeftChild(BiTree,char);
//返回二叉树中某个结点的右兄弟
char RightSibling(BiTree,char);
//输出树
void Print(BiTree);



int main(void)
{
    int depth;
    char rs;
    BiTree T;
    InitTree(&T);
    CreateTree(&T);
    //depth = TreeDepth2(T);
    //rs = RightSibling(T,'A');
    //printf("%c",rs);
    Print(T);
    return 0;


}


void InitTree(BiTree * T)
{

    (*T)->n = 0; //结点树为0

}




void CreateTree(BiTree * T)
{
    
    int i = 1;  //顺序结构的非根结点的下标
    int j = 0;  //用于遍历树结点值的索引
    int l = 0;  //字符串的长度
    int len = MAX_TREE_SIZE;

    struct queue2 queue;
    init_queue(&queue,100);
    
    struct Qelement q1; //根结点临时结构
    struct Qelement q2; //非根结点的临时结构
    
    printf("请输入根结点的值:");
    char c[MAX_TREE_SIZE];
    scanf("%c%*c",&(*T)->nodes[0].data);

   if((*T)->nodes[0].data != ' ')
   {
        (*T)->nodes[0].parent = -1;
        (*T)->r = 0;

        q1.num = 0;
        q1.tdata = (*T)->nodes[0].data;
        
        insert_queue(&queue,q1);
        
        while(i < MAX_TREE_SIZE && !is_empty(&queue))
        {
            q1 = delete_queue(&queue);
            printf("请输入%c结点的子孙结点:",q1.tdata);
            fgets(c,len - i,stdin);
            l = strlen(c);
            for(j = 0;j < l;j++)
            {
                if(c[j] == '\n')
                    break;
                (*T)->nodes[i].data = c[j];
                (*T)->nodes[i].parent = q1.num;
                q2.num = i;
                q2.tdata = c[j];
                insert_queue(&queue,q2);
                i++;
            }

        }
        if(i > MAX_TREE_SIZE)
        {
            printf("ERROR超过最大的结点数");
            exit(1);
        }
        
        (*T)->n = i;


   }else
        (*T)->n= 0;

}

bool isTempty(BiTree T)
{

    if(0 == T->n)
        return true;
    return false;
}


int TreeDepth1(BiTree T)
{

    int j = 0;

    while(T->n >= pow(2,j))
        j++;

    return j;
}

int TreeDepth2(BiTree T)
{
    int k;
    int m;
    int def;
    int max = 0;
    
    if(T)
    {
        for(k = 0;k < T->n;k++)
        {
            def = 1;
            m = T->nodes[k].parent;
            while(m != -1)
            {
                m = T->nodes[m].parent;
                def++;
            }
            if(max < def)
                max = def;
        }

        return max;
    }
    
    return 0;

}



char Root(BiTree T)
{
    int i;
    for(i = 0;i < T->n;i++)
        if(T->nodes[i].parent < 0)
            return T->nodes[i].data;
    
    return ' ';

}


char Value(BiTree T,int i)
{
    if(i < T->n)
        return T->nodes[i].data;
    
    return ' ';
}


void Assign(BiTree T,char cur,char value)
{
    
    int i;
    for(i = 0;i < T->n;i++)
    {
        if(cur == T->nodes[i].data)
            T->nodes[i].data = value;
    }

}


char Parent(BiTree T,char cur)
{
    char p;
    int i;
    for(i = 0;i < T->n;i++)
    {
       if(cur == T->nodes[i].data) 
            return T->nodes[T->nodes[i].parent].data;
    }
    return ' ';
}


char LeftChild(BiTree T,char cur)
{
    int i;
    int j;
    for(i = 0;i < T->n;i++)
    {
        if(cur == T->nodes[i].data)
           break; 
    }

    for(j = i + 1;j < T->n;j ++)
       if(T->nodes[j].parent == i)
            return T->nodes[j].data;

    return ' ';
}

char RightSibling(BiTree T,char cur)
{
    int i;
    int j = 0;
    
    for(i = 0;i < T->n;i++)
        if(cur == T->nodes[i].data)
            break;
    for(j = i + 1;j < T->n;j++)
    {  
        if(T->nodes[j].parent == T->nodes[i].parent)
            return T->nodes[j].data;
    }
    return ' ';
}

void Print(BiTree T)
{
    printf("树的结点总数为%d",T->n);
    printf("\n");
    printf("树的根结点为:");
    int i;
    for(i = 0;i < T->n;i++)
    {
        printf("%c",Value(T,i));
        if(T->nodes[i].parent >= 0)
            printf("父节点为%c",T->nodes[T->nodes[i].parent].data);
        printf("\n");
    }
}

