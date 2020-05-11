//孩子兄弟表示法构造

typedef struct CSNode
{
    int data;
    struct CSNode * firstChild;
    struct CSNode * nextSibling;
}CSNode,*CSTree;



