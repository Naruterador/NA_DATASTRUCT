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


int main(void)
{

    CSTree T;
    Init(&T);
    CreateTree(&T);
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
