#include <stdio.h>
#include <stdlib.h>

/*
用结构体来表示一个链表
*/
struct Node
{
    int data;
    struct Node * pNext;
};




int main(void)
{
  
  struct Node *node1;
  struct Node *node2;

  node1->data = 1;
  node1->pNext = node2;

  node2->data = 2;
  node2->pNext = NULL;

    

  return 0;
}