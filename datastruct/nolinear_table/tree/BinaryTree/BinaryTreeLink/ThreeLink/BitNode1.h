//二叉树的三叉链表表示法结构
typedef struct BitNode
{
    int data;
    struct BitNode * lchild;
    struct BitNode * rchild;
    struct BitNode * parent;

}BitNode,*BiTree;
