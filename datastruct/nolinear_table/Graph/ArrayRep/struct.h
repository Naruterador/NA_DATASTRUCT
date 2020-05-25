/*
    邻接矩阵表示图的结构体结构


*/


#define MAX_VERTEX_NUM 26 //图的最大顶点数量
#define INFINITY INT_MAX //整型的最大值

enum Graphkind{DG,DN,UDG,UDN};   //图的类型(有向图，有向网，无向图，无向网)
typedef int VRType;

typedef struct
{
    VRType adj; //顶点关系类型,在有向图中为0和1，在网中为权值或者无穷大    
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


struct MGraph
{
    char vex[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    enum Graphkind kind;
    int vexnum; //图的总顶点树
    int arcnum; //图的总边数

};

//深度优先算法与广度优先算法顶点访问标志数组
int visited[MAX_VERTEX_NUM];

