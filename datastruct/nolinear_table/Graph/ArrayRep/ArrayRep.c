//邻接矩阵实现图的操作

#include "queue.h"

//找u在G中的下标
int LocateVex(struct MGraph * G,char u);

//构造无向图G
void CreateUDG(struct MGraph * G);

//构造无向网G
void CreateUDN(struct MGraph * G);


//构造有向图G
void CreateDG(struct MGraph * G);

//构造有向网G
void CreateDN(struct MGraph * G);


//销毁图
void DestroyGraph(struct MGraph * G);

//返回途中某顶点的值
char GetVex(struct MGraph * G,int v);

//v是G中的某结点对某个结点赋新值
void PutVex(struct MGraph * G,char curv,char value);

//返回v顶点第一个邻接点的序号
int FirstAdjVex(struct MGraph * G,char v);

//返回v的相对于w的下一个邻接点的序号，若w是v的最后一个邻接点，则返回-1
int NextAdjVex(struct MGraph * G,char v,char w);

//在图G中插入新的顶点v
void InsertVex(struct MGraph * G,char v);

//在图G中删除顶点v以及相关的弧
void Delete(struct MGraph * G,char v);

//在G中为<v,w>两个顶点增加弧
void InserArc(struct MGraph * G,char v,char w);

//在G中为<v,w>两个顶点删除弧
void DeleteArc(struct MGraph * G,char v,char w);

//深度优先递归的遍历G
void DFS(struct MGraph * G,int v);

//深度优先非递归遍历图G
void DFSTraverse(struct MGraph * G);


//广度优先遍历图G
void BFSTraverse(struct MGraph * G);

//输出邻接矩阵存储结构图G
void Display(struct MGraph * G);

int main(void)
{

    struct MGraph G;
        
    CreateUDG(&G);
    DFSTraverse(&G);
    //BFSTraverse(&G);



    return 0;
}






int LocateVex(struct MGraph * G,char u)
{

    int i;
    for(i = 0;i < G->vexnum;i++)
    {
        if(u == G->vex[i])
            return i;
    }
    return -1;
}


void CreateUDG(struct MGraph * G)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char va;
    char vb;
    
    //输入顶点总数，边的总数
    printf("请输入顶点的总数和边的总数,格式为: 顶点数，边数\n");
    scanf("%d,%d%*c",&G->vexnum,&G->arcnum);
    
    //输入顶点的值
    for(i = 0; i < G->vexnum;i++)
    {   
        printf("请输入%d个顶点的值:",i + 1);
        scanf("%c%*c",&G->vex[i]);
    }
    
    //初始化图的邻接矩阵
    for(i = 0;i < G->vexnum;i++)
        for(j = 0;j < G->vexnum;j++)
        {
           G->arcs[i][j].adj = 0;
        }

    //输入无向图中边的关系
    printf("请输入无向图中%d边的关系，格式为:边1 边2\n",G->arcnum);
    for(k = 0;k < G->arcnum;k++)
    {
        scanf("%c%c%*c",&va,&vb);
        i = LocateVex(G,va);
        j = LocateVex(G,vb);
        
        if(i == -1 || j == -1)
        {
            printf("未找到图顶点!");
            exit(-1);
        }
        
        G->arcs[i][j].adj = 1;
        G->arcs[j][i].adj = 1;
    }
    G->kind = UDG;
}


char GetVex(struct MGraph * G,int v)
{
    if(v > G->vexnum)
    {
        printf("ERROR:无法找到这个顶点");
        return G->vex[v];
    }
    return ' ';
}

void PutVex(struct MGraph * G,char curv,char value)
{
    int i = 0;
    i = LocateVex(G,curv);
    G->vex[i] = value;
}

int FirstAdjVex(struct MGraph * G,char v)
{
    int i;
    int j = 0;
    int k = 0;
    k = LocateVex(G,v);
    
    for(i = 0;i < G->vexnum;i++)
    {
        if(G->arcs[k][i].adj != j)
            return i;
    }
    return -1;
}


int NextAdjVex(struct MGraph * G,char v,char w)
{
    int k1;
    int k2;
    int j = 0;
    int i = 0;
    k1 = LocateVex(G,v);
    k2 = LocateVex(G,w);

    for(i = k2 + 1;i < G->vexnum;i++)
    {
        if(G->arcs[k1][i].adj != j)
            return i;
    }
    return -1;
}

void DFS(struct MGraph * G,int v)
{
   int w;
   visited[v] = 1;
   printf("%c",G->vex[v]);
    
   for(w = FirstAdjVex(G,G->vex[v]);w >=0;w = NextAdjVex(G,G->vex[v],G->vex[w]))
   {
       if(visited[w] == 0)
            DFS(G,w);
   }

}



void DFSTraverse(struct MGraph * G)
{
    
    int i = 0;
    //初始化数组访问标志数组
    for(i = 0;i < G->vexnum;i++)
        visited[i] = 0;
    
    for(i = 0;i < G->vexnum;i++)
    {
        if(visited[i] == 0)
            DFS(G,i);
    }
}

void BFSTraverse(struct MGraph * G)
{
    int i;
    int v;
    int u;
    int w;
    
    struct queuelist queue;
    init_queue(&queue,6);

    //初始化图的访问标记数组
    for(i = 0;i < G->vexnum;i++)
        visited[i] = 0;
    
    for(v = 0;v < G->vexnum; v++)
    {
       if(visited[v] == 0)
       {
            visited[v] = 1;
            printf("%c",G->vex[v]);
            insert_queue(&queue,v);
            while(!is_empty(&queue))
            {
                u = delete_queue(&queue);
                    for(w = FirstAdjVex(G,G->vex[u]);w >= 0;w = NextAdjVex(G,G->vex[u],G->vex[w]))
                    {
                        if(visited[w] == 0)
                        {
                            visited[w] = 1;
                            printf("%c",G->vex[w]);
                            insert_queue(&queue,w);
                        }
                    }
            }
       }

    }

}

