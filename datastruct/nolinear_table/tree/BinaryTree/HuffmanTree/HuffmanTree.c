/*
哈夫曼树的结构

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "BitNode.h"

//返回i个结点中最小的树的根结点序号
int min(HuffmanTree t,int i);
//在i个结点中选择2个权值最小的树的根结点序号，其中s1为最小的那个
void select(HuffmanTree t,int i,int * s1,int * s2);

//构造一棵哈夫曼树
//其中w存放n哥字符的权值(均>0),构造哈夫曼树HT,并求出n个字符的哈夫曼编码HC
void HuffmanCoding(HuffmanTree  * HT,HuffmanCode * HC,int * w,int n);

int main(void)
{
    HuffmanTree HT;
    HuffmanCode HC;
    char code[10];
    int w[8] = {7,19,2,6,32,3,21,10};//叶子结点(字符)的权值
    int n = 8; //叶子结点(字符)的总数
    HuffmanCoding(&HT,&HC,w,n);
    //printf("%d",HT[14].weight);
    printf("%s",HC[1]);
    return 0;

}

void select(HuffmanTree t,int i,int * s1,int * s2)
{
    int j;
    *s1 = min(t,i);
    *s2 = min(t,i);
    if(*s1 > *s2)
    {
        j = *s1;
        *s1 = *s2;
        *s2 = j;
    }
}


int min(HuffmanTree t,int i)
{
   int j;
   int flag;

   int q = 0;
   unsigned k = q - 1;//无符号整数的最大值
   
   for(j = 1;j <= i;j++)
        if(t[j].weight < k&&t[j].parent == 0)
        {
           k = t[j].weight;
           flag = j;
        }
    t[flag].parent = 1; //放置重复查找
    return flag;
}







void HuffmanCoding(HuffmanTree * HT,HuffmanCode * HC,int * w,int n)
{
    //创建空的哈夫曼树
    int m; //结点总数;
    

    int s1; //最小结点1的序号  
    int s2; //最小结点2的序号
    
    int i;
    int start; //哈夫曼编码的字符初始空间大小
    
    unsigned c;
    unsigned f;
    
    HuffmanTree temp; //临时容器
    
    char * cd;  //哈夫曼编码存储空间
    
    if(n <= 1)
    {
        printf("ERROR:无法构成哈夫曼树，叶子结点数量小于2");
        exit(1);
    }

    m = 2 * n - 1;  //计算哈夫曼树的总结点数量(2n - 1);
    
    //为所有结点分配内存空间
    *HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));
    
    //初始化所有结点
    //叶子结点初始化
    for(temp = (*HT) + 1,i = 1;i <= n;temp++,w++,i++)
    {
       (*temp).weight = (*w);
       (*temp).lchild = 0;
       (*temp).rchild = 0;
       (*temp).parent = 0;
    }
    //剩余空结点初始化
    for(;i<=m;i++,temp++)
    {    
        (*temp).parent = 0;
        (*temp).lchild = 0;
        (*temp).rchild = 0;
    }
    
    //创建哈夫曼树
    for(i = n + 1;i <= m;i++)
    {
        select(*HT,i - 1,&s1,&s2);
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;

        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }

    //从叶子到根逆向求每个字符的哈夫曼编码
    
    *HC =(HuffmanCode)malloc(sizeof(char *) * (n + 1)); //所有字符的哈夫曼编码分配的空间
    
    cd =(char *)malloc(n * sizeof(char)); //每个字符的哈夫曼编码分配的临时存储空间
    
    cd[n - 1] = '\0'; //编码结束位置
    
    for(i = 1;i <= n;i++)
    {
        start = n - 1;
        for(c = i,f = (*HT)[i].parent;f != 0;c = f,f = (*HT)[f].parent)
        {
           if((*HT)[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }

       (*HC)[i] = (char *)malloc(sizeof(char) * (n - start)); //为每个字符的哈夫曼编码分配空间
       strcpy((*HC)[i],&cd[start]);  //将哈夫曼编码放入哈夫曼编码组
    }
    free(cd); //释放空间
  
}



