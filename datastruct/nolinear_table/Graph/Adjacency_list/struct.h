//图的邻接表结构
#define MVNum 100 //最大顶点数为100
typedef char VRType;
typedef int Info; //权值
enum Graphkind{DG,DN,UDG,UDN}; //(有向图，有向网，无向图，无向网)


struct ElemType
{

    int adjvex;
    Info weight;
};


struct ArcNode
{
    struct ElemType data;
    struct ArcNode * nextarc;
};


typedef struct VNode
{
    VRType data;
    struct ArcNode * firstarc;
}VNode,AdjList[MVNum];


struct ALGraph
{
    AdjList vertices;
    int vexnum;
    int arcnum;
    enum Graphkind kind;
};


