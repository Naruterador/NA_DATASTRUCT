/*

树的双亲表示法实现


*/


#define MAX_TREE_SIZE 100



typedef struct PtNode
{
    char data;
    int parent;
}PtNode;

typedef struct Tree
{
    PtNode nodes[MAX_TREE_SIZE];
    int n; //总结点数
    int r; //根结点的下标
} *BiTree;

typedef struct Qelement
{
    int num;    //树中当前结点的下标值
    char tdata; //树中结点值


}QuElement;


