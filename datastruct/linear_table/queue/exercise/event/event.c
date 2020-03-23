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
    int trigger;

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
void OpenForDay();
//模拟用户到达事件
void CustomerArrived();
//模拟用户离开事件
void CustomerDeparture();
//模拟银行的事务
void Blank_Simulation();



int main(void)
{
    struct eventlist * pHead = NULL;
    struct eventlist * getp;
    
    struct linequeue queue[4];
    struct queueNode test;
    int length;

    int a;
    int b;
    random_gen(&a,&b);
    printf("%d,%d\n",a,b);
    
   
    //test = delete_linequeue(&queue);
    //test = delete_linequeue(&queue);
    /*
    pHead = init_eventlist();
    insert_eventlist(pHead,0,0);
    insert_eventlist(pHead,1,1);
    insert_eventlist(pHead,5,3);
    insert_eventlist(pHead,6,10);
    traverse_linked(pHead);
    getp= delete_eventFirst(pHead);
    printf("%d,%d\n",getp->en.enType,getp->en.occurtime);
    pHead = eventChangeFrist(pHead);
    getp = delete_eventFirst(pHead);
    printf("%d,%d\n",getp->en.enType,getp->en.occurtime);     
    pHead = eventChangeFrist(pHead);
    getp = delete_eventFirst(pHead);
    printf("%d,%d\n",getp->en.enType,getp->en.occurtime);   
    
    struct queueNode test;
    init_linequeue(&queue);
    insert_linequeue(&queue,0,0);
    insert_linequeue(&queue,1,1);
    insert_linequeue(&queue,2,2);
    insert_linequeue(&queue,3,3);
    test = delete_linequeue(&queue);
    test = delete_linequeue(&queue);
    test = delete_linequeue(&queue);
    printf("%d,%d\n",test.arrivaltime,test.duration);
    */

    

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
    pHead->trigger = -1;

    return pHead;
}

//事件插入（插入事件链表）
void insert_eventlist(struct eventlist * enlist,int oct,int type)
{   
    
    struct eventlist * pTail = enlist;
    struct eventlist * pNew = (struct eventlist *)malloc(sizeof(struct eventlist));
    if(-1 == pTail->trigger)
    {
        pTail->en.enType = type;
        pTail->en.occurtime = oct;
        pTail->trigger = 1;
    }
    else{
        if(NULL == pNew)
        {
            printf("Can not assign the space for the pNew");
            exit(1);

        }
        while(NULL != pTail->pNext)
        {
            pTail = pTail->pNext;
        }
        
        pNew->en.enType = type;
        pNew->en.occurtime = oct;
        pTail->pNext = pNew;
        pNew->pNext = NULL;
        pTail = pNew;
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
    pHead = enlist;    
    return pHead;
}
//删除原来链表元素的第一个节点，并将头节点向后移动
struct eventlist * eventChangeFrist(struct eventlist * enlist)
{
    struct eventlist * nPhead;
    nPhead = enlist->pNext;
    free(enlist);
    enlist = NULL;
    return nPhead;
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
        printf("%d,%d\n",p->en.enType,p->en.occurtime);
        p = p->pNext;
    }
    printf("%d,%d\n",p->en.enType,p->en.occurtime);
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
    return length - 1;
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