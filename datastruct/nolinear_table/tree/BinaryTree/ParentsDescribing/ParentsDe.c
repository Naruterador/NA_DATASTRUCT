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


int main(void)
{
    BiTree T;
    InitTree(&T);
    CreateTree(&T);
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


