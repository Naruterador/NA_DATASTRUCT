//图的邻接表实现

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//该函数返回顶点下标
int LocateVex(struct ALGraph * G,VRType v);

//邻接表创建图
void CreateGraph(struct ALGraph * G);

//销毁邻接表
void DestroyGraph(struct ALGraph * G);

//图G存在，v是G中某个顶点的序号，返回v的值
VRType GetVex(struct ALGraph * G,int v);

//图G存在,v是G中某个顶点，函数对v赋新值
void PutVex(struct ALGraph * G,VRType v,VRType value);

//图G存在，v是图G中的某个顶点，返回v的第一个邻接顶点序号。如果顶点在G中没有邻接顶点，则返回-1
int FirstAdjVex(struct ALGraph * G,VRType v);

//DelectArc()、DeleteVex()、NextAdjVex()要调用的函数
void equalvex(struct ElemType v1,struct ElemType v2);

//图G存在,v是G中某个顶点，w是v的邻接顶点，返回v的(相对与w的)下一个邻接顶点的序号。若w是v的最后一个邻接点，则返回-1
int NextAdjVex(struct ALGraph * G,VRType v,VRType w);

//链表插入
bool insert_ce(struct ArcNode * Arc,struct ElemType val,int position);

int main(void)
{





    return 0;
}

int LocateVex(struct ALGraph * G,VRType v)
{
    int i = 0;
    for(i = 0;i < G->vexnum;i++)
    {
        if(G->vertices[i].data == v)
            return i;
    } 
    return -1;

}



bool insert_ce(struct ArcNode * Arc,struct ElemType val,int position)
{

    int i = 0;
    struct ArcNode * pNew = (struct ArcNode *)malloc(sizeof(struct ArcNode));
    if(NULL == pNew && position < 1)
    {
        return false;
    }
    if(NULL == Arc)
    {
        pNew->data = val;
        pNew->nextarc = NULL;
        Arc = pNew;
    }
    else
    {
        struct ArcNode * CurNode = Arc;
        for(i = 0;i < position - 1;i++)
        {
            CurNode = CurNode->nextarc;
        }

        pNew->data =  val;
        pNew->nextarc = CurNode;
        CurNode = pNew;
        return true;
    }
}

void CreateGraph(struct ALGraph * G)
{
    int i;
    int j;
    int k;
    int w;
    VRType va;
    VRType vb;
    
    struct ElemType e;
    
    printf("请输出图的类型:(有向图:0,有向网:1,无向图:2,无向网:3)");
    scanf("%d%*c",&G->kind);
    
    printf("输入的图的顶点数与边数，格式为:顶点数,边数");
    scanf("%d,%d%*c",&G->vexnum,&G->arcnum);
    
    printf("输入%d个顶点的值",G->vexnum);
    for(i = 0;i < G->vexnum;i++)
    {
        scanf("%c%*c",&G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }

    if(G->kind%2) //如果是网
        printf("请输入每条弧的权值、弧尾、和弧头");
    else //如果是图
        printf("请输入每条弧的弧尾、弧头");
    
    for(k = 0;k < G->arcnum;k++)
    {
        if(G->kind%2)
            scanf("%d,%c,%c%*c",&w,&va,&vb);
        else
            scanf("%c,%c%*c",&va,&vb);
        
        i = LocateVex(G,va);
        j = LocateVex(G,vb);
        
        e.adjvex = j;
        
        if(G->kind%2)
            e.weight = w;
        else
            e.weight = 0;
        insert_ce(G->vertices[i].firstarc,e,1);
        
        if(G->kind >= 2)
        {
            e.adjvex = i;
            insert_ce(G->vertices[j].firstarc,e,1);
        }

    }

}
