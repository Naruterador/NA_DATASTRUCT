/*

字符串存在于字符串数组中。无论数组多大，都用数值'\0'表示结束。

*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>

//字符串的最大长度
#define MAX_STRING_LENGTH 40
//字符串超过最大长度错误

typedef char SString[MAX_STRING_LENGTH + 1];

//生成一个字符串
void  StrAssign(SString T,char *);

//复制字符串S到T字符串
void StrCopy(SString T,SString S);


//判断传入字符串是否为空
bool StrEmpty(SString);


//判断字符串T和字符串S的大小
//若S > T,则返回大于0,若S = T，则返回0，若S < T,则返回负数
int StrCompare(SString,SString);


//返回字符串的长度
int StrLength(SString);


//清空当前的字符串
void ClearString(SString);


//将S1，S2字符串连接成为新串
void Concat(SString,SString,SString);


//用Sub返回串S的第pos个字符起长度为len的子串
void SubString(SString,SString,int pos,int len);



//若主串S中存在和串T值相同的子串，则返回它在主串中第pos个字符之后第一次出现的位置;否则返回函数为0
int Index(SString,SString,int pos);


//用V替换主串中出现的所有与T相等的不重叠的子串。
void Replace(SString,SString,SString);


//在串S的第pos个字符之前插入串T
void StrInsert(SString,SString,int);


//在串S的第pos个字符之前插入串T
void StrDelete(SString,int pos,int len);


//销毁字符串S
void DestoryString(SString);

//其它字符串匹配算法（不回溯主串的方式）KMP算法
//每次平移的数组next获取函数
int * get_next(SString T);
//MKP算法的实现
int KMP_go(SString,SString,int,int *);
int * get_nextval(SString T);
/*
int main(void)
{
    int i = 1;
    SString S;
    SString T;
    SString V;
    SString U;
    SString X;
    StrAssign(S,"(a,b,c)");
    StrAssign(T,"(");
    StrAssign(U,")");
    StrAssign(X,",");
    int k = 0;
    SubString(V,S,1,1);
    for(i = 1,k = 0;i <= S[0]&&(StrCompare(V,X)||k != 0);++i)
    {
        SubString(V,S,i,1);
        if(!StrCompare(V,T))
            ++k;
        else if(!StrCompare(V,U))
            --k;
    }
    printf("%d",i);

    
    //int * next;
    //next = get_next(T);
    //for(int i = 0; i < 10;i++)
       // printf("%d\n",next[i]);
    //i = KMP_go(S,T,1,next);

    //printf("%d\n",i);
    
    

    return 0;
}
*/
void StrAssign(SString T,char * strings)
{
    int i = 1;
    int length = strlen(strings);
    if(length > MAX_STRING_LENGTH)
    {
        printf("Can not Create this T");
        exit(1);
    } 
    T[0] = length;
    
    for(i = 1;i <= T[0];i++)
    {
        T[i] = strings[i-1];
        //非糖罐语法
        //T[i] = *(strings + i - 1);
    }

}


void StrCopy(SString T,SString S)
{
    int i = 1;
    T[0] = S[0];
    for(i = 1;i <= S[0];i++)
    {
        T[i] = S[i];
    }
}


bool StrEmpty(SString S)
{
    if(S[0] == 0)
        return true;
    return false;
}


int StrCompare(SString T,SString S)
{
    int i = 1;
    for(i = 1;i <= S[0] && i <=T[0];i++)
        if(S[i] != T[i])
            return S[i] - T[i];
        return 0;
}


int StrLength(SString T)
{
    if(StrEmpty(T))
        return 0;
    return T[0];
}


void ClearString(SString T)
{
    if(StrEmpty(T))
    {
        printf("The String is empty!");
        exit(1);
    }
    int len = T[0];
    for(int i = 1;i <= len;i++)
        T[i] = '\0';
    T[0] = 0;
}


void Concat(SString S3,SString S1,SString S2)
{
    int i = 1;
    int j = 1;
    int k = 1;
    S3[0] = S1[0] + S2[0];
    
    if(S3[0] > MAX_STRING_LENGTH)
    {
        printf("The string out of range!");
        exit(1);
    }
    
    for(i = 1;i <= S3[0];i++)
        if(i > S1[0])
        {
            S3[i] = S2[k];
            k++;
        }
        else
            S3[i] = S1[i];
}


void SubString(SString Sub,SString S,int pos,int len)
{
    
    if(pos < 1 || pos > S[0] || len > S[0] || len < 0 || pos + len > S[0] + 1)
    //pos+len的值不能大于原字符串的长度+1
    {
        printf("Can not find the Substrings!");
        exit(1);
    }
    
    Sub[0] = len;
    
    for(int i = 1;i <= len;i++)
    {   
        Sub[i] = S[pos];
        pos++;
    }
}


int Index(SString S,SString T,int pos)
{
    //用于跟踪主字符串的索引移动
    int indexmove = 0;
    //子字符串的索引
    int indexsub = 1;

    //主字符串的索引
    int indexmain = pos;
    int indextemp;
    
    //如果查找主字符串S的开始位置小于子字符串T的长度，直接返回假
    if(pos < 1 || pos > S[0])
        return 0;
    
    //循环结束条件为当字符串剩余长度小于子串长度时如果还没有匹配到字符串，就停止循环
    while(S[0]-indexmove >= T[0])
    {
        //如果匹配到主串S中有某个字符与子串中某字符相同，开始进入比较
        if(S[indexmain] == T[indexsub])
        {   
            //将当前子主串所在位置开始检查，并将主串位置赋给一个临时的值
            indextemp = indexmain; 
            while(indexsub <= T[0])
            {
                if(S[indextemp] == T[indexsub])
                {
                    indextemp++;
                    indexsub++;
                }
                else{
                    indexsub = 1;
                    break;
                }
            }
        }

         //判断是否找到了子串
        if(indexsub >= T[0])
            return indexmain;

        indexmain++;
        indexmove++;
    }
    return 0;
}


//这个功能可以用队列来实现，会比较简单，下面的程序没有使用队列
void Replace(SString S,SString T,SString V)
{
    //主串遍历的索引
    int indexmain = 1;
    
    int i = 0;
    
    //字符串位置索引位置
    int pos = 1;

    //子串的遍历索引
    int k = 1;

    //临时变量1用于抓取复制的目标点
    int temp1;
    //临时变量2用于抓取复制的启始点
    int temp2;

    //保存字符串原来的长度
    int originlength = S[0];
    //求出字符串的差
    int lle = T[0] - V[0];

    //判断是否能在主串S中找到匹配的子串T
    if(0 == Index(S,T,1))
    {
        printf("Can not find any substring in S!");
        exit(1);
    }
    
        //替换字符串长度V等于匹配字符串长度T的处理
        if(T[0] == V[0])
        { 

            while(indexmain <= S[0])
            {       
                pos = Index(S,T,pos);
                if(0 != pos)
                {
                    while(k <= V[0])
                    {
                        S[pos] = V[k];
                        k++;
                        pos++;
                    }
                }else{
                    k = 1;
                    break;
                }
                k = 1;
                indexmain  = pos + 1;
            }
        }


        //替换字符串长度V小于匹配字符串长度T的处理
        if(T[0] > V[0])
        {
            while(indexmain <= S[0])
            {
                pos = Index(S,T,pos);
                if(0 != pos)
                {
                    //替换字符串
                    while(k <= V[0])
                    {
                        S[pos] = V[k];
                        pos++;
                        k++;
                    }
                    //替换后重新计算字符串的长度
                    S[0] = S[0] - lle;
                    i++;
                    k = 1;
                    //移动剩余的字符串
                    
                    //找到移动启使点位置
                    temp1 = pos;
                    //后一段移动开始位置
                    temp2 = pos + 1; 
                    //当剩下的字符串长度大于总长度时，就停止循环
                    if(temp2 > S[0])
                    {
                        //设置退出时的结束点
                        S[temp1] = '\0';
                        break;
                    }
                    //开始把剩余的字符串向前移动
                    while(temp2 <= originlength)
                    {
                        S[temp1] = S[temp2];
                        temp1++;
                        temp2++;
                    }
                    //每次移动后设置字符串新的结束点
                    S[temp1] = '\0';
                }else
                    break;
                indexmain = pos;
            }

        }
        

        //用于临时存放后半段字符串的空间
        SString Stemp;
        SString Stempmain;
        SString NewS;
        int temppos;
        //主字符串增加的长度
        lle = V[0] - T[0];
        if(T[0] < V[0])
        {
            while(S[indexmain <= S[0]] && S[0] <= MAX_STRING_LENGTH)
            {
                pos = (Index(S,T,pos));
                if(0 != pos)
                {
                    //先将字符串的后半段保存到临时字符串Stemp;
                    if(pos + T[0] <= S[0])
                    {    
                        temppos = pos + T[0];
                        Stemp[0] = (S[0] - temppos) + 1;
                        while(k <= Stemp[0])
                        {   
                            Stemp[k] = S[temppos];
                            temppos++;
                            k++;
                        }
                        //将k的值重置为1
                        k = 1;
                    }
                    //将替换字符串V放入主字符串中
                    while( k <= V[0])
                    {   
                        S[pos] = V[k];
                        pos++;
                        k++;
                    }
                    k = 1;

    

                    if(0 != Stemp[0])
                    {
                        Stempmain[0] = pos - 1;
                        while(k <= Stempmain[0])
                        {
                            Stempmain[k] = S[k];
                            k++;
                        }
                        k = 1;
          
                        S[0] = Stempmain[0]  + Stemp[0];
                        
                        int i = 1;
                        while(k <= S[0])
                        {
                            
                            if(k > Stempmain[0])
                            {
                                S[k] = Stemp[i];
                                i++;
                                k++;
                            }else
                            {
                                S[k] = Stempmain[k];
                                k++;
                            }
                        if(k > MAX_STRING_LENGTH)
                        {
                            break;
                        }
                        }
                        Stemp[0] = 0;
                        Stempmain[0] = 0;
                        if(k > MAX_STRING_LENGTH)
                        {   
                           S[MAX_STRING_LENGTH + 1] = '\0';
                           S[0] = MAX_STRING_LENGTH;
                           break;
                        }
                        else 
                            k = 1;
                    }
                }else{
                    break;
                }
                indexmain = pos;
            }

        }
}

/*
高一凡Replace函数实现:
// 此函数与串的存储结构无关
Status Replace(SString S,SString T,SString V) 
{ 
//初始条件：串S，T和V存在，T是非空串
//操作结果：用V替换主串S中出现的所有与T相等的不重叠的子串

// 从串S的第一个字符起查找串T
int i=1; 
Status k;
// T是空串
if(StrEmpty(T)) 
    return ERROR;
do
    {
        //结果i为从上一个i之后找到的子串T的位置
        i=Index(S,T,i); 
        //串S中存在串T
        if(i) 
        {
            StrDelete(S,i,StrLength(T)); // 删除该串T
            k=StrInsert(S,i,V); // 在原串T的位置插入串V

            if(!k) // 不能完全插入
                return ERROR;

            i+=StrLength(V); // 在插入的串V后面继续查找串T
        }
    }while(i);
return OK;
}

*/




void StrInsert(SString S,SString T,int pos)
{
    if(pos < 1 || pos > S[0])
    {
        printf("Pos out of range!");
        exit(1);
    }
    
    //剩余主串字符串的起始索引值
    int restBpos = pos + 1;
    //临时索引值
    int k = 1;
    
    SString tempS;
    SString tempmainS;

    //当pos不等于S[0]
    if(pos < S[0])
    {
        tempS[0] = S[0] - pos;
        while( k <= tempS[0])
        {
            tempS[k] = S[restBpos];
            k++;
            restBpos++;
        }



        k = 1;
        int i = 1;
        //字符串S-POS部分+上插入T串的内容
        tempmainS[0] = pos + T[0];
        while(k <= tempmainS[0])
        {
            if(k > pos)
            {
                tempmainS[k] = T[i];
                k++;
                i++;

            }
            else{    
                tempmainS[k] = S[k];
                k++;
            }
        }
        
        k = 1;
        i = 1;
        //完成前两段的拼接
        S[0] = tempmainS[0] + tempS[0];
        while(k <= S[0])
        {

            if(k > tempmainS[0])
            {
                S[k] = tempS[i];
                k++;
                i++;
            }
            else{    
                S[k] = tempmainS[k];
                k++;
            }

            if(k > MAX_STRING_LENGTH)
            {
                S[0] = MAX_STRING_LENGTH;
                S[MAX_STRING_LENGTH + 1] = '\0';
                break;
            }

        }
       

    }
     //如果pos等于S[0]
    if(pos == S[0])
    {
        S[0] = pos + T[0];
        int addSpos = pos + 1;

        while( addSpos <= S[0])
        {
            S[addSpos] = T[k];
            addSpos++;
            k++;

        if(k > MAX_STRING_LENGTH)
        {
            S[0] = MAX_STRING_LENGTH;
            S[MAX_STRING_LENGTH + 1] = '\0';
            break;
        }
        }

    }

}


void StrDelete(SString S,int pos,int len)
{
    if(pos < 1 || pos > S[0] || len < 1 || len > S[0] || pos + len > S[0] + 1)
    {
        printf("Wrong parameter with pos or len!");
        exit(1);
    }

    //删除之后剩余部分的初始值
    int restBpos = pos + len;
    int nextBpos = pos;
    while(restBpos <= S[0])
    {
        S[nextBpos] = S[restBpos];
        nextBpos++;
        restBpos++;
    }

    S[0] = S[0] - len;
    S[S[0] + 1] = '\0';
}






//KMP算法的next实现
int * get_next(SString T)
{

    int i = 1;
    int j = 0;
    int * next = (int *)malloc(sizeof(int) * 10);
    next[1] = 0;
    while(i < T[0])
    {
        if(j == 0 || T[i] == T[j])
        {
                i++;
                j++;
                next[i] = j;
        }
        else
        {
                j = next[j];
        }
        
    }
    free(next);
    return next;
}

//next优化算法
int * get_nextval(SString T)
{

    int i = 1;
    int j = 0;
    int * next = (int *)malloc(sizeof(int) * 10);
    next[1] = 0;
    while(i < T[0])
    {
        if(j == 0 || T[i] == T[j])
        {
                i++;
                j++;
                if(T[i] != T[j])
                    next[i] = j;
                else
                    next[i] = next[j];

        }
        else
        {
                j = next[j];
        }
        
    }
    free(next);
    return next;
}

//KMP算法的实现
int KMP_go(SString S,SString T,int pos,int * next)
{
    int j = 1;
    int i = 1;
    while(i <= S[0] && j <=T[0])
    {
        if(j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }else
            j = next[j];
    }
    if(j > T[0])
    {
        return i - T[0];
    }
    return 0;
}
