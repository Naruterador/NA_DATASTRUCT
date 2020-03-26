#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//事件结构体，用于记录用户开始办理业务和业务办理结束时，时间的事件
struct Event
{
    //事件开始的时间
    int occurtime;
    //事件类型(0表示业务开始，1表示从窗口1结束业务办理离开，2表示从窗口2结束业务办理离开，3表示从窗口3结束业务办理离开，4表示从窗口4结束业务办理离开)
    int enType;
};

//用户数据结构体
struct queueNode
{
    //用户到达时间
    int arrivaltime;
    //用户办理业务时长
    int duration;
};

//事件链表
struct eventlist
{
    //用户事件
    struct Event en;  
    struct eventlist * pNext;

};

//银行排队队列
struct linequeue
{
    struct queueNode * custom;
    int front;
    int rear;
    int size;
};


//初始化事件链表
struct eventlist * init_eventlist();
//链表插入
void insert_eventlist(struct eventlist *,int,int);
//链表删除
struct eventlist * delete_eventFirst(struct eventlist *);
//判断链表是否为空
bool is_lempty(struct eventlist *);
//遍历链表的测试函数
void traverse_linked(struct eventlist *);
//每删除一个事件，就将链表头向后移动
struct eventlist * eventChangeFrist(struct eventlist * enlist);

//初始化队列
void init_linequeue(struct linequeue *);
//插入队列元素
void insert_linequeue(struct linequeue *,int arrivaltime,int duratime);
//删除队列元素
struct queueNode delete_linequeue(struct linequeue *);
//判断队列是否为空
bool is_qempty(struct linequeue *);
//返回队列的长度
int length(struct linequeue *);
//获得当前队列头部
struct queueNode GetHead(struct linequeue *);


//生成多个队列函数
void init_multiplequeue(struct linequeue * qu);
//求出哪个队列元素数量最小
int Minimumqueue(struct linequeue *);



//随机生成用户到达银行的间隔时间和用户办理业务的持续时间
void random_gen(int *,int *);





//初始化一天的模拟
void OpenForDay(struct eventlist * enlist,struct linequeue *,int * Totaltime);
//模拟用户到达事件
void CustomerArrived(int * countcustom,struct eventlist * ,struct eventlist *,struct linequeue *,int *,int *,int *);
//模拟用户离开事件
void CustomerDeparture(struct eventlist * ,struct linequeue *,struct eventlist *,int * Totaltime);
//模拟银行的事务
void Blank_Simulation(struct eventlist *,struct linequeue *,int *,int *,int *,int *,int *);



int main(void)
{
    struct eventlist * pHead = NULL;
    pHead = init_eventlist();
    struct linequeue queue[4];
    //总时间
    int Totaltime = 0;
    //总人数;
    int countCustom = 0;
    //持续时间
    int durtime;
    //每个用户到达的间隔时间
    int intertime;
    //关门时间(单位分钟)
    int closetime = 480;
    Blank_Simulation(pHead,queue,&Totaltime,&durtime,&intertime,&closetime,&countCustom);
    return 0;

}


//初始化事件链表
struct eventlist * init_eventlist()
{
    struct eventlist * pHead = (struct eventlist *)malloc(sizeof(struct eventlist));
    if(NULL == pHead)
    {
        printf("Can not assign space for the pHead");
        exit(1);
    }   
    pHead->pNext = NULL;
    return pHead;
}

//事件插入（插入事件链表）要求，每次插入时按照时间先后顺序插入
void insert_eventlist(struct eventlist * enlist,int oct,int type)
{   
   
    struct eventlist * pTail = enlist;
    struct eventlist * temp;
    if(is_lempty(pTail))
    {
        struct eventlist * pNew = (struct eventlist *)malloc(sizeof(struct eventlist));
        if(NULL == pNew)
        {
            printf("Can not assign the space for the pNew");
            exit(1);

        }
        pNew->en.enType = type;
        pNew->en.occurtime = oct; 
        pTail->pNext = pNew;
        pNew->pNext = NULL;
    }
    else{
        int i = 0;
        struct eventlist * p = pTail->pNext;
        struct eventlist * temp;
        struct eventlist * pNew = (struct eventlist *)malloc(sizeof(struct eventlist));
        if(NULL == pNew)
        {
            printf("Can not assign the space for the pNew");
            exit(1);

        }
        //通过判断链表的occurtime大小，进行插入
        while(oct > p->en.occurtime && NULL != p->pNext)
        {
            temp = p;
            p = p->pNext;
            i++;
        }
        //当链表只有一个节点时，对插入的操作
        if(0 == i && NULL == p->pNext)
        {
            if(oct >= p->en.occurtime)
            {
                pNew->en.enType = type;
                pNew->en.occurtime = oct;
                pNew->pNext = NULL;
                p->pNext = pNew;
            }
            if(oct < p->en.occurtime)
            {
                pNew->en.enType = type;
                pNew->en.occurtime = oct;
                pNew->pNext = p;
                pTail->pNext = pNew;
            }
        }
        //如果插入的节点比首节点小而且节点数大于1，就按照一下方式处理
        else if(0 == i && NULL != p->pNext)
        {
             if(oct >= p->en.occurtime)
            {
                pNew->en.enType = type;
                pNew->en.occurtime = oct;
                pNew->pNext = p->pNext;
                p->pNext = pNew;
            }
            if(oct < p->en.occurtime)
            {
                pNew->en.enType = type;
                pNew->en.occurtime = oct;
                pNew->pNext = p;
                pTail->pNext = pNew;
            }

        }
        //如果链表节点数大于1,对插入的处理
        else if(0 != i && NULL == p->pNext)
        {
                if(oct >= p->en.occurtime)
                {
                    pNew->en.enType = type;
                    pNew->en.occurtime = oct;
                    pNew->pNext  = NULL;
                    p->pNext = pNew;
                }
                if(oct < p->en.occurtime)
                {
                    pNew->en.enType = type;
                    pNew->en.occurtime = oct;
                    pNew->pNext = p;
                    temp->pNext = pNew;
                }
        }else{
                    pNew->en.enType = type;
                    pNew->en.occurtime = oct;
                    pNew->pNext = p;
                    temp->pNext = pNew;
        }
        
    }
}

//取出当前事件链表的第一个节点
struct eventlist * delete_eventFirst(struct eventlist * enlist)
{
    if(is_lempty(enlist))
    {
        printf("ERROR LINKED LIST IS EMPTY!");
        exit(1);
    }
    
    struct eventlist * pHead;
    struct eventlist * pFirst;
    pHead = enlist;
    pFirst = pHead->pNext;
    pHead->pNext = pHead->pNext->pNext;        
    return pFirst;
}


//检查链表是否为空
bool is_lempty(struct eventlist * enlist)
{
    if(NULL == enlist->pNext)
        return true;
    return false;
}

//遍历链表函数
void traverse_linked(struct eventlist * enlist)
{
    struct eventlist * p = enlist;
    while( NULL != p->pNext)
    {
        
        p = p->pNext;
        printf("%d,%d\n",p->en.occurtime,p->en.enType);
    }
}


//初始化队列
void init_linequeue(struct linequeue * qu)
{
    qu->custom = (struct queueNode *)malloc(sizeof(struct queueNode));
    if(NULL == qu->custom)
    {
        printf("Can not assign the space for queue");
        exit(1);
    }
    qu->rear = 0;
    qu->front = 0;
    qu->size = 0;
}

//插入队列元素
void insert_linequeue(struct linequeue * qu,int arrivaltime,int duratime)
{
    qu->size++;
    qu->custom = (struct queueNode *)realloc(qu->custom,sizeof(struct queueNode) * qu->size);
    if(NULL == qu->custom)
    {
        printf("Can not assign the space for the queue Node");
        exit(1);
    }
    qu->custom[qu->rear].arrivaltime = arrivaltime;
    qu->custom[qu->rear].duration = duratime;
    qu->rear++;
}

//删除队列元素
struct queueNode delete_linequeue(struct linequeue * qu)
{
    if(is_qempty(qu))
    {
        printf("ERROR QUEUE IS EMPTY!");
        exit(1);
    }
    struct queueNode delNode;
    delNode.arrivaltime = qu->custom[qu->front].arrivaltime;
    delNode.duration = qu->custom[qu->front].duration;
    qu->front++;
    return delNode;
}

//检查队列是否为空
bool is_qempty(struct linequeue * qu)
{
    if(qu->front == qu->rear)
        return true;
    return false;
}

//获取队列头
struct queueNode GetHead(struct linequeue * qu)
{
    struct queueNode qHead;
    qHead.arrivaltime = qu->custom[qu->front].arrivaltime;
    qHead.duration = qu->custom[qu->front].duration;

    return qHead;
}


//获取队列长度
int length(struct linequeue * qu)
{
    int length;
    length = qu->rear - qu->front;
    return length;
}


//初始化多个队列
void init_multiplequeue(struct linequeue * qu)
{
    int i = 0;
    for(i = 0;i < 4;i++)
        init_linequeue(&qu[i]);
}

//找到最小的读列，并返回队列编号
int Minimumqueue(struct linequeue * qu)
{
    int least = length(&qu[0]);
    int queuenum = 0;
    int i;

    for(i = 0;i < 4;i++)
       if(length(&qu[i]) < least)
       {
            least = length(&qu[i]);
            queuenum = i;
       }
    return queuenum;
}


//生成业务办理时间和用户到达银行间隔时间的随机数(其中用户间隔时间为0-5分钟,业务员办理时间是0-30分钟)
void random_gen(int * durtime,int * intertime)
{
    srand(time(NULL));
    *durtime = rand() % 30;
    *intertime = rand() % 5;
}


//初始化一天的银行事件
void OpenForDay(struct eventlist * enlist,struct linequeue * qu ,int * Totaltime)
{
    //模拟当天的第一个客户进入银行
    insert_eventlist(enlist,0,0);

    //初始化4个队列
    init_multiplequeue(qu);
}


//处理增加客户的函数
void CustomerArrived(int * countcustom,struct eventlist * enlist,struct eventlist * Node,struct linequeue *qu,int * durtime,int * intertime,int * Closetime)
{
    int t = 0;
    //找到最小的队列
    int i = 0;
    //随机生成上一个用户办理业务持续时间和下一个用户到达的间隔时间
    random_gen(durtime,intertime);
    //下一个用户的到达时间为上一用户的到家时间+间隔时间    
    t = Node->en.occurtime + *intertime;
    //每多一个用户增加1
    *countcustom = *countcustom + 1;
    //假设银行还在营业,就让用户进入事件
    if(t < *Closetime)
        insert_eventlist(enlist,t,0);
    //找到最小的队列并将上个用户开始业务的时间和持续时间放进队列，开始排队
    i = Minimumqueue(qu);
    //将上一个用户放入人数最少的队列
    insert_linequeue(&qu[i],Node->en.occurtime,*durtime);    
    printf("第%d用户进入银行队列%d排队，排队开始时间为%d\n",*countcustom,i + 1,t);
    //当前队列如果只有1个人排队，那就直接生成上一个用户的出队列事件，并压入事件链表
    if(length(&qu[i]) == 1)
    {
        insert_eventlist(enlist,Node->en.occurtime + *durtime,i);
    }
}


void CustomerDeparture(struct eventlist * enlist ,struct linequeue * qu,struct eventlist * Node,int * Totaltime)
{
    struct queueNode leaveclient;
    struct queueNode lineNextclient;
    int i = 0;
    //获取当前离开事件的队列
    i = Node->en.enType;
    //用户离开队列
    leaveclient = delete_linequeue(&qu[i]);
    //计算这个用户在银行中逗留的时间
    *Totaltime = *Totaltime + (Node->en.occurtime - leaveclient.arrivaltime);
    //printf("第%d分钟到银行的用户办理业务完成离开银行，离开时间为时间为%d\n",leaveclient.arrivaltime,Node->en.occurtime);
    //如果这个队列不为空，则把现在队列头部的用户添加离开事件
    if(!is_qempty(&qu[i]))
    {   
        //获得队列i的新排头
       lineNextclient =  GetHead(&qu[i]);
       //这个用户的离开事件插入链表
       insert_eventlist(enlist,Node->en.occurtime + lineNextclient.duration,i);

    }
}

void Blank_Simulation(struct eventlist * enlist,struct linequeue * qu,int * Totaltime,int * durtime,int * intertime,int * Closetime,int * countcustom)
{
    double averagetime;
    struct  eventlist * p;
    //初始化这一天
    OpenForDay(enlist,qu,Totaltime);
    while(!is_lempty(enlist))
    {
       p = delete_eventFirst(enlist);
       if(p->en.enType == 0)
            CustomerArrived(countcustom,enlist,p,qu,durtime,intertime,Closetime);
        else
            CustomerDeparture(enlist,qu,p,Totaltime);
    }
    printf("用户总共逗留的时间为%d,一共接待了%d个用户\n",*Totaltime,*countcustom);
    averagetime = *Totaltime / *countcustom;
    printf("用户平均逗留时间为%f",averagetime);
}