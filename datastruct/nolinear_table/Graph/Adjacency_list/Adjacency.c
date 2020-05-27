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

//链表插入(头插法)
bool insert_ce(struct ArcNode ** Arc,struct ElemType val,int position);
//链表删除
struct ElemType delete_ce(struct ArcNode ** Arc,int position);
//判断链表是否为空
bool is_empty(struct ArcNode * Arc);
//销毁链表
void DestroyList(struct ArcNode ** Arc);



int main(void)
{
    int temp;
    struct ALGraph G;
    CreateGraph(&G);
    temp = FirstAdjVex(&G,'B');
    printf("%d",temp);
    //DestroyGraph(&G);

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

bool is_empty(struct ArcNode * Arc)
{
    
    if(NULL ==  Arc)
        return true;
    return false;
}

bool insert_ce(struct ArcNode ** Arc,struct ElemType val,int position)
{

    int i = 0;
    if(NULL == *Arc)
    {    
        *Arc = (struct ArcNode *)malloc(sizeof(struct ArcNode));
        if(NULL == *Arc && position < 1)
        {
            return false;
        }
        (*Arc)->data = val;
        (*Arc)->nextarc = NULL;    
    }
    else
    {
        struct ArcNode * pNew = (struct ArcNode *)malloc(sizeof(struct ArcNode));
        if(NULL == pNew && position < 1)
        {
            return false;
        }

        pNew->data =  val;
        pNew->nextarc = *Arc;
        *Arc = pNew;
        return true;
    }
}


struct ElemType delete_ce(struct ArcNode ** Arc,int position)
{   


    if(is_empty(*Arc))
    {
        printf("链表已空，退出");
        exit(1);
    }
    
    *Arc = (*Arc)->nextarc;

    return (*Arc)->data;

}

void DestroyList(struct ArcNode ** Arc)
{
    *Arc = NULL;
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
    
    printf("输入%d个顶点的值:\n",G->vexnum);
    for(i = 0;i < G->vexnum;i++)
    {
        printf("请输入第%d个顶点值:",i + 1);
        scanf("%c%*c",&G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }

    if(G->kind%2) //如果是网
        printf("请输入每条弧的权值、弧尾、和弧头,格式为权值,顶点１顶点２:\n");
    else //如果是图
        printf("请输入每条弧的弧尾、弧头格式为顶点1顶点2:\n");
    
    for(k = 0;k < G->arcnum;k++)
    {
        if(G->kind%2)
            scanf("%d,%c%c%*c",&w,&va,&vb);
        else
            scanf("%c%c%*c",&va,&vb);
        
        i = LocateVex(G,va);
        j = LocateVex(G,vb);
        
        e.adjvex = j;
        
        if(G->kind%2)
            e.weight = w;
        else
            e.weight = 0;

        insert_ce(&G->vertices[i].firstarc,e,1);
        
        if(G->kind >= 2)
        {
            e.adjvex = i;
            insert_ce(&G->vertices[j].firstarc,e,1);
        }

    }

}

void DestroyGraph(struct ALGraph * G)
{
    int i;
    for(i = 0;i < G->arcnum;i++)
    {
        DestroyList(&G->vertices[i].firstarc);
    }
    G->arcnum = 0;
    G->vexnum = 0;
}




VRType GetVex(struct ALGraph * G,int v)
{
    if(v >= G->vexnum || v < 0)
    {
        printf("找不到这个顶点!");
        exit(1);
    }
    return G->vertices[v].data;
}


//图G存在,v是G中某个顶点，函数对v赋新值
void PutVex(struct ALGraph * G,VRType v,VRType value)
{
    int i;
    i = LocateVex(G,v);
    if(i > -1)
        G->vertices[i].data = value;
}

//图G存在，v是图G中的某个顶点，返回v的第一个邻接顶点序号。如果顶点在G中没有邻接顶点，则返回-1
int FirstAdjVex(struct ALGraph * G,VRType v)
{
    int v1;
    v1 = LocateVex(G,v);
    if(v1 >= G->vexnum || v1 < 0)
        return -1;
    return G->vertices[v1].firstarc->data.adjvex;

}


