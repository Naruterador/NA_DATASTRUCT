/*
    孩子兄弟表示法实现树的存储

*/


#include "loop_queue_unlimited.h"

//构造空树T
void Init(CSTree *);
//构造树T
void CreateTree(CSTree *);
//销毁树T
void DestroyTree(CSTree *);

//递归先序遍历树
void PreOrderTraverse(CSTree);
//后序遍历
void PostOrderTraverse(CSTree);
//层序遍历
void LevelOrderTraverse(CSTree);





//判断树是否为
bool TreeEmpty(CSTree);
//返回树的深度算法
int TreeDepth(CSTree);
//返回树中某节点的值
char Value(CSTree);
//返回树的根节点
char Root(CSTree);
//返回二叉链表中结点为s的指针
CSTree Point(CSTree T,char s);
//修改树T中cur结点的值为value
void Assign(CSTree T,char cur,char value);
//返回树T中cur结点的双亲
char Parent(CSTree T,char cur);
//返回树T中cur结点的左孩子
char LeftChild(CSTree T,char cur);
//返回树T中cur结点的右兄弟
char RightSilbing(CSTree T,char cur);

//向树T的p结点的第i个位置插入子树c
void InserChild(CSTree * T,CSTree p,int i,CSTree c);
//删除树T中p结点的第i棵子树
void DeleteChild(CSTree * T,CSTree p,int i);




int main(void)
{
    CSTree inpoint;
    CSTree T;
    CSTree P;
    Init(&T);
    Init(&P);
    CreateTree(&T);
    CreateTree(&P);
    inpoint = Point(T,'B');
    InserChild(&T,inpoint,1,P);
    DeleteChild(&T,inpoint,1);
    LevelOrderTraverse(T); 
    return 0;
}

void Init(CSTree * T)
{

    T = NULL;

}



void CreateTree(CSTree * T)
{
    int i;
    int l;
    char c[20];
    
    CSTree p1;
    CSTree p2;
    
    struct queuelist queue;
    init_queue(&queue,1);
    
    printf("请输入树的根结点:");
    scanf("%c%*c",c);
    
    if(c[0] != ' ')
    {
        (*T) = (CSTree)malloc(sizeof(struct CSNode));
        if(NULL == *T)
        {
            printf("Can not assign the space for the *T");
            exit(1);

        }
        
        (*T)->data = c[0];
        (*T)->nextSibling = NULL;
        insert_queue(&queue,(*T));
        while(!is_empty(&queue))
        {
            p1 = delete_queue(&queue);
            printf("请输入%c结点的子结点",p1->data);
            fgets(c,100,stdin);
            l = strlen(c);
            if(c[0] == '\n')
                l = 0;
            
            if(l > 0)
            {
                p1->firstChild = (CSTree)malloc(sizeof(struct CSNode));
                p1->firstChild->data = c[0];
                p2 = p1->firstChild;
                
                for(i = 1;i < l;i++)
                {
                    if(c[i] == '\n')
                        break;
                    p2->nextSibling = (CSTree)malloc(sizeof(struct CSNode));
                    insert_queue(&queue,p2);
                    p2 = p2->nextSibling;
                    p2->data = c[i];

                }
                p2->nextSibling = NULL;
                insert_queue(&queue,p2);

            }
            else
                p1->firstChild = NULL;

        }

    }
    else
        (*T) = NULL;
}


void PreOrderTraverse(CSTree T)
{
    if(T)
    {
        printf("%c",T->data);
        PreOrderTraverse(T->firstChild);
        PreOrderTraverse(T->nextSibling);
    }
}



void DestroyTree(CSTree * T)
{
    if((*T)->firstChild)
        DestroyTree(&(*T)->firstChild);
    
    if((*T)->nextSibling)
        DestroyTree(&(*T)->nextSibling);

    free(*T);
    *T = NULL;
}



bool TreeEmpty(CSTree T)
{
    if(NULL == T)
        return true;
    return false;
}


int TreeDepth(CSTree T)
{
    CSTree p;
    int depth;
    int max = 0;
    
    if(NULL == T)
        return 0;

    if(NULL == T->firstChild)
        return 1;

    for(p = T->firstChild;p;p = p->nextSibling)
    {
        depth = TreeDepth(p);
        if(max < depth)
            max = depth;
    }
        return max + 1;
}


char Value(CSTree p)
{

    return p->data;

}

char Root(CSTree T)
{

    if(T)
        return T->data;
    return ' ';
}

CSTree Point(CSTree T,char s)
{
    CSTree temp;
    struct queuelist queue;
    
    if(T)
    {
        init_queue(&queue,1);
        insert_queue(&queue,T);
        
        while(!is_empty(&queue))
        {
            temp = delete_queue(&queue);
            if(temp->data == s)
                return temp;
            else
            {
                if(temp->firstChild)
                    insert_queue(&queue,temp->firstChild);
                if(temp->nextSibling)
                    insert_queue(&queue,temp->nextSibling);
            }

        }
    }
    return NULL;
}

void Assign(CSTree T,char cur,char value)
{
    CSTree temp;
    
    if(T)
    {
        temp = Point(T,cur);
        if(temp)
            temp->data = value;
    }

}

char Parent(CSTree T,char cur)
{
    CSTree temp1;
    CSTree temp2;
    struct queuelist queue;
    

    if(T)
    {
        //如果是根结点，则直接返回cur
        if (Root(T) == cur)
            return cur;
        
        init_queue(&queue,1);
        insert_queue(&queue,T);
        
        while(!is_empty(&queue))
        {
           temp1 = delete_queue(&queue);
           
           if(temp1->firstChild)
           {
                if(temp1->firstChild->data == cur)
                    return temp1->data;

                temp2 = temp1;
                temp1 = temp1->firstChild;
                insert_queue(&queue,temp1);
                while(temp1->nextSibling)
                {
                    
                    temp1 = temp1->nextSibling;
                    if(temp1->data == cur)
                        return temp2->data;
                    insert_queue(&queue,temp1);


                }

           }
        }
    }    
    return ' ';
}



char LeftChild(CSTree T,char cur)
{
    CSTree temp;
    temp = Point(T,cur);
    
    if(temp&&temp->firstChild)
        return temp->firstChild->data;
    return ' ';
}

char RightSilbing(CSTree T,char cur)
{
    CSTree temp;
    temp = Point(T,cur);

    if(temp&&temp->nextSibling)
        return temp->nextSibling->data;
    return ' ';
}



void PostOrderTraverse(CSTree T)
{
    CSTree temp;
    
    if(T)
    {
        if(T->firstChild)
        {
            PostOrderTraverse(T->firstChild);
            temp = T->firstChild->nextSibling;
            while(temp)
            {
                PostOrderTraverse(temp);
                temp = temp->nextSibling;
            }

        }
        printf("%c",T->data);
    }
    
}

void LevelOrderTraverse(CSTree T)
{
    CSTree temp;
    struct queuelist queue;
    init_queue(&queue,1); 
    if(T)
    {
        printf("%c",T->data);
        insert_queue(&queue,T);
        
        while(!is_empty(&queue))
        {
            temp = delete_queue(&queue);    
            if(temp->firstChild)
            {
                
                temp = temp->firstChild;
                printf("%c",temp->data);
                insert_queue(&queue,temp);
                while(temp->nextSibling)
                {
                    temp = temp->nextSibling;
                    printf("%c",temp->data);
                    insert_queue(&queue,temp);
                }
            }
        }
        
    }
}

//p是T中的某个结点
void InserChild(CSTree * T,CSTree p,int i,CSTree c)
{
    int j;
    
    if(T)
    {
        if(i == 1)  //表示插入为长子
        {
            c->nextSibling = p->firstChild;
            p->firstChild = c;

        }
        else
        {
            p = p->firstChild;
            j = 2;
            while(p&&j < i)
            {
                p = p->nextSibling;
                j++;
            }
            if(j == i)
            {
                c->nextSibling = p->nextSibling;
                p->nextSibling = c;

            }else{
                printf("不能找到插入点");
                exit(1);
            }
        }
    }else{
        printf("树为空");
    }
}

void DeleteChild(CSTree * T,CSTree p,int i)
{
    CSTree temp;
    int j;
    if(T)
    {
        if(i == 1) //删长子
        {
            temp = p->firstChild;
            p->firstChild = temp->nextSibling;
            temp->nextSibling = NULL;
            DestroyTree(&temp);
        }
        else
        {
           p = p->firstChild;
           j = 2;
           while(p&&j < i)
           {
             p = p->nextSibling;
             j++;
           }
           if(j == i)
           {
               temp = p->nextSibling;
               p->nextSibling = temp->nextSibling;
               temp->nextSibling = NULL;
               DestroyTree(&temp);
           }
        }

    }
}
