/*
哈夫曼树的结构

*/


typedef struct 
{

    unsigned int weight;    //结点的权重
    unsigned int parent;    //结点的双亲序号
    unsigned int lchild;    //结点的左孩子序号
    unsigned int rchild;    //结点的右孩子序号
}HTNode,*HuffmanTree;

typedef char **HuffmanCode; //用于保存哈夫曼编码表
