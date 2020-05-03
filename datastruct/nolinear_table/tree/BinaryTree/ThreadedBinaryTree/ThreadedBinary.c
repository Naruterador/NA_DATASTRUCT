/*
线索二叉树的实现

线索二叉树用于解决在某种遍历序列中找到某个结点的前驱或后继

*/

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

int main(void)
{






    return 0;

}
