//图的邻接表实现

#include "queue.h"

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
bool equalvex(struct ElemType v1,struct ElemType v2);

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
//线性表L存在，compare()是数据元素判定函数(满足为1，否则为0)，返回L中满足关系compare()的数据元素位序，若数据不存在则返回值为0
int LocateElem(struct ArcNode * Arc,struct ElemType e,bool(*compare)(struct ElemType,struct ElemType));
//查找表中满足条件的结点，如果找到则返回指针
struct ArcNode * Point(struct ArcNode * Arc,struct ElemType,bool(*compare)(struct ElemType,struct ElemType));
//返回该顶点的前驱结点
struct ArcNode * Perpoint(struct ArcNode * Arc,struct ElemType e,bool(*compare)(struct ElemType,struct ElemType));
//删除顶点元素
struct ArcNode * DeleteElem(struct ArcNode ** Arc,struct ElemType e,bool(*compare)(struct ElemType,struct ElemType));




//返回链表的长度
int ListLength(struct ArcNode * Arc);
//删除链表的第一个结点
struct ElemType ListDelete(struct ArcNode ** Arc);






//图遍历的标记数组
int visited[MVNum];
//深度优先遍历
void DFS(struct ALGraph * G,int v);
void DFSTraverse(struct ALGraph * G);
void DFS1(struct ALGraph * G,int v);
void DFSTraverse1(struct ALGraph * G);
//广度优先遍历
void BFSTraverse(struct ALGraph * G);
void BFSTraverse1(struct ALGraph * G);


//插入一个新的顶点
void InsertVex(struct ALGraph * G,VRType V);
//删除一个顶点
void DeleteVex(struct ALGraph * G,VRType V);
//在图G中增加弧<v,w>,若G是无向图则还需要添加对称弧<w,v>
void InsertArc(struct ALGraph * G,VRType v,VRType w);
//在图G中删除弧度<v,w>,若G是无向的,则还需要删除对称弧<w,v>
void DeleteArc(struct ALGraph * G,VRType v,VRType w);




int main(void)
{
    int temp;
    struct ALGraph G;
    struct ElemType e;
    CreateGraph(&G);
    InsertArc(&G,'A','D');
    DeleteArc(&G,'C','D');
    //temp = NextAdjVex(&G,'D','B');
    //printf("%d",e.temp);
    //DestroyGraph(&G);
    //DFSTraverse1(&G);
    //BFSTraverse(&G);
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
    return false;
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

bool equalvex(struct ElemType v1,struct ElemType v2)
{
    if(v1.adjvex == v2.adjvex)
        return true;
    return false;
}


int LocateElem(struct ArcNode * Arc,struct ElemType e,bool(*compare)(struct ElemType,struct ElemType))
{
     
    int i = 0;
    
    struct ArcNode * p = Arc;
    
    while(p)
    {
        i++;
        if(compare(p->data,e))
            return i;
        p = p->nextarc;
    }
    return 0;
}

struct ArcNode * Point(struct ArcNode * Arc,struct ElemType e,bool(*compare)(struct ElemType,struct ElemType))
{
    int i;
    int j;
    i = LocateElem(Arc,e,equalvex);

    struct ArcNode * p;
    
    if(i)
    {
        if(i == 1)
        {
            p = NULL;
            return Arc;
        }
        
        p = Arc;
        
        for(j = 2;j < i;j++)
            p = p->nextarc;
            
            return p->nextarc;
    }
    return NULL;
}

struct ArcNode * Perpoint(struct ArcNode * Arc,struct ElemType e,bool(*compare)(struct ElemType,struct ElemType))
{
    int i;
    int j;
    i = LocateElem(Arc,e,equalvex);

    struct ArcNode * p;
    
    if(i)
    {
        if(i == 1)
        {
            p = NULL;
            return Arc;
        }
        
        p = Arc;
        
        for(j = 2;j < i;j++)
            p = p->nextarc;
            
            return p;
    }
    return NULL;
}



int NextAdjVex(struct ALGraph * G,VRType v,VRType w)
{
   struct ArcNode * p;
   struct ElemType e;
   
   int v1;
   v1 = LocateVex(G,v);
   e.adjvex = LocateVex(G,w);

   p = Point(G->vertices[v1].firstarc,e,equalvex);
   
   if(NULL == p || NULL == p->nextarc)
        return -1;
   
   return p->nextarc->data.adjvex;
}

void DFS(struct ALGraph * G,int v)
{
    int w;
    visited[v] = 1;
    printf("%c",G->vertices[v].data);
    
    for(w = FirstAdjVex(G,G->vertices[v].data);w >= 0;w = NextAdjVex(G,G->vertices[v].data,G->vertices[w].data))
        if(0 == visited[w])
            DFS(G,w);
            
}

void DFSTraverse(struct ALGraph * G)
{
   int i = 0;
    for(i = 0;i < G->vexnum;i++)
        visited[i] = 0;
    
    for(i = 0;i < G->vexnum;i++)
        if(0 == visited[i])
            DFS(G,i);
    
}


void DFS1(struct ALGraph * G,int v)
{
    struct ArcNode * p;
    visited[v] = 1;
    printf("%c",G->vertices[v].data);
    for(p = G->vertices[v].firstarc;p;p = p->nextarc)
        if(0 == visited[p->data.adjvex])
            DFS(G,p->data.adjvex);
}

void DFSTraverse1(struct ALGraph * G)
{
    int i;
    for(i = 0;i < G->vexnum;i++)
        visited[i] = 0;
    
    for(i = 0;i < G->vexnum;i++)
        if(0 == visited[i])
            DFS1(G,i);
}


void BFSTraverse(struct ALGraph * G)
{
    int v;
    int u;
    int w;
    struct queuelist queue;
    
    init_queue(&queue,1);

    for(v = 0;v < G->vexnum;v++)
        visited[w] = 0;

    for(v = 0;v < G->vexnum;v++)
        if(0 == visited[v])
        {
            visited[v] = 1;
            printf("%c",G->vertices[v].data);
            insert_queue(&queue,v);
            while(!is_queue_empty(&queue))
            {
                u = delete_queue(&queue);
                for(w = FirstAdjVex(G,G->vertices[u].data);w >=0;w = NextAdjVex(G,G->vertices[u].data,G->vertices[w].data))
                    if(0 == visited[w])
                    {
                        visited[w] = 1;
                        printf("%c",G->vertices[w].data);
                        insert_queue(&queue,w);
                    }
            }

        }   
}

void InsertVex(struct ALGraph * G,VRType V)
{
    strcpy(&G->vertices[G->vexnum].data,&V);
    G->vertices[G->vexnum].firstarc = NULL;
    G->vexnum++;
}


int ListLength(struct ArcNode * Arc)
{
    struct ArcNode * p = Arc;
    int i = 0;
    while(p != NULL)
    {
        i++;
        p = p->nextarc;
    }
    return i;
}


struct ElemType ListDelete(struct ArcNode ** Arc)
{
    struct ArcNode * p;
    struct ArcNode * q;
    q = *Arc;
    p = q->nextarc;
    *Arc = p;
    if(p)
    {
        free(p);
        p = NULL;
    }
    return q->data;
}





void DeleteVex(struct ALGraph * G,VRType V)
{
    int i;
    int j;
    int k;
    
    struct ElemType e;
    struct ArcNode * p;
    struct ArcNode * p1;
    struct ArcNode * q;

    //找到顶点j的序号
    j = LocateVex(G,V);
    if(j < 0)
    {
        printf("找不到这个顶点!");
        exit(1);
    }
    //返回j顶点的弧数量
    i = ListLength(G->vertices[j].firstarc);
    G->arcnum = G->arcnum - i; //删除顶点对应的边的数量
    
    //删除需要删除顶点的弧
    while(G->vertices[j].firstarc)
    {
        e = ListDelete(&G->vertices[j].firstarc);
    }
    
    G->vexnum--; //减去一个顶点个数
    
    //其余顶点前移
    for(i = j;i < G->vexnum; i++)
        G->vertices[i] = G->vertices[i + 1];
    
    //删除已删除的顶点和其他顶点的弧
    for(i = 0;i < G->vexnum; i++)
    {
        e.adjvex = j;
        p = Point(G->vertices[i].firstarc,e,equalvex);

        if(p)
        {
            if(p == G->vertices[i].firstarc)
            {
                G->vertices[i].firstarc = p->nextarc;
            }
            else
            {
                e.adjvex = p->data.adjvex;
                p1 = Perpoint(G->vertices[i].firstarc,e,equalvex);
                p1->nextarc = p->nextarc;
            }

            if(G->kind < 2) //有向图
                G->arcnum--;
        }
        free(p);
        
        //修改adjvex域>j的顶点，其序号-1
        for(k = j + 1;k <= G->vexnum;k++)
        {
            e.adjvex = k;
            p = Point(G->vertices[i].firstarc,e,equalvex);
            if(p)
                p->data.adjvex--;
        } 
    }
}


void InsertArc(struct ALGraph * G,VRType v,VRType w)
{
     struct ElemType e;
     int i;
     int j;
     
     i = LocateVex(G,v);
     j = LocateVex(G,w);
     
     if(i < 0 || j < 0)
     {
        printf("ERROR:不能找到这2个顶点");
        exit(1);
     }
     e.adjvex = j;
     insert_ce(&G->vertices[i].firstarc,e,1);
     if(G->kind >= 2)
    {
            e.adjvex = i;
            insert_ce(&G->vertices[j].firstarc,e,1);
    }
    G->arcnum++;
}



struct ArcNode * DeleteElem(struct ArcNode ** Arc,struct ElemType e,bool(*compare)(struct ElemType,struct ElemType))
{
        
    int i;
    int j;
    i = LocateElem(*Arc,e,equalvex);

    struct ArcNode * p;
    struct ArcNode * q;
    struct ArcNode * p1;
    p = *Arc;
    if(i)
    {
        if(i == 1)
        {
            q = p;
            *Arc = p->nextarc;
            free(p);
            return q;
        }
 
        for(j = 2;j < i;j++)
            p = p->nextarc;
        q = p->nextarc;
        e.adjvex = q->data.adjvex;
        p1 = Perpoint(*Arc,e,equalvex);
        p1->nextarc = p->nextarc->nextarc;
        free(p);
        p = NULL;
        return q;
    }
    return NULL;
}


void DeleteArc(struct ALGraph * G,VRType v,VRType w)
{
    int i;
    int j;
    
    struct ArcNode * k;
    
    struct ElemType e;
    i = LocateVex(G,v);
    j = LocateVex(G,w);
    
    if(i < 0 || j < 0 || i == j)
    {
        printf("ERROR:找不到该顶点!");
        exit(1);
    }
    
    e.adjvex = j;
    
    k = DeleteElem(&G->vertices[i].firstarc,e,equalvex);
    if(k)
    {
        G->arcnum--;
        
        if(G->kind >= 2)
        {
            e.adjvex = i;
            DeleteElem(&G->vertices[j].firstarc,e,equalvex);
        }

    }
}
