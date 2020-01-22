#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct arr 
{
    int * pBase;
    int length;
    int ce;
};

void init_arr(struct arr * ,int length);
bool is_arr_empty(struct arr *);
bool is_arr_full(struct arr * );
void show_arr(struct arr *);
bool append_arr(struct arr *,int value);
bool insert_ce(struct arr *,int position,int insert_value);
bool delete_ce(struct arr* ,int position);
bool get_value(struct arr *,int postion);
bool reverse_arr(struct arr *);
bool sort_arr(struct arr *);

int main(void)
{   
    int i = 0;
    struct arr arr1;
    init_arr(&arr1,8);
    append_arr(&arr1,4);
    append_arr(&arr1,3);
    append_arr(&arr1,1);
    append_arr(&arr1,2);
    append_arr(&arr1,50);
    append_arr(&arr1,8);
    append_arr(&arr1,5);
    append_arr(&arr1,2);

    sort_arr(&arr1);
    //reverse_arr(&arr1);
    //insert_ce(&arr1,2,10);
    //delete_ce(&arr1,3);
    show_arr(&arr1);
    //get_value(&arr1,1);
    return 0;
}


void init_arr(struct arr * pArr,int len)
{
    pArr->pBase =(int *)malloc(sizeof(int) * len);
    if (pArr->pBase == NULL)
    {
        printf("Can not create space!");
        exit(-1);
    }
    pArr->length = len;
    pArr->ce = 0;
}

bool is_arr_empty(struct arr * pArr)
{
    if (pArr->ce == 0)
        return true;
    else
        return false;
    
}

bool is_arr_full(struct arr * pArr)
{
    if(pArr->ce == pArr->length)
        return true;
    else
        return false;
}


bool append_arr(struct arr * pArr,int value)
{   
    if (is_arr_full(pArr))
        return false;

    pArr->pBase[pArr->ce] = value;
    (pArr->ce)++;
    return true;
}


bool insert_ce(struct arr * pArr,int position,int value)
{
    if (position < 0 || position > pArr->ce + 1)
        return false;

    if (is_arr_full(pArr))
        return false;
    
    int i;
    int j;
    for (i = pArr->ce,j = pArr->ce - 1;i > position;i--,j--)
        pArr->pBase[i] = pArr->pBase[j];
    
    pArr->pBase[position] = value;
    (pArr->ce)++;
    return true;
}

bool delete_ce(struct arr* pArr,int position)
{
    if (position < 0 || position > pArr->ce + 1)
        return false;
    
    if (is_arr_empty(pArr))
        return false;

    int i = position;
    int j = position + 1;

    for (i,j;i < pArr->ce - 1;i++,j++)
        pArr->pBase[i] = pArr->pBase[j];
    
    (pArr->ce)--;

}

bool reverse_arr(struct arr * pArr)
{
    int times = pArr->ce / 2;
    int i = 0;
    int j = pArr->ce - 1;
    int temp = 0;
    for (i,j;i < times;i++,j--)
    {
        temp = pArr->pBase[i];
        pArr->pBase[i] = pArr->pBase[j];
        pArr->pBase[j] = temp;
    }
}

bool sort_arr(struct arr * pArr)
{   
    int temp = 0;
    int i = 0;
    int j = 0;

    for(i;i < pArr->ce;i++)
        for(j = i;j < pArr->ce - 1;j++)
            {
                if(pArr->pBase[i] > pArr->pBase[j + 1])
                    {   
                        temp = pArr->pBase[i];
                        pArr->pBase[i] = pArr->pBase[j + 1];
                        pArr->pBase[j + 1] = temp;
                    }

            }
    


}


void show_arr(struct arr * pArr)
{   
    int len = pArr->ce;
    int i = 0;
    for(i;i < len;i++)
        printf("%d\n",pArr->pBase[i]);
}

bool get_value(struct arr * pArr,int position)
{
    if (position < 0 || position > pArr->ce + 1)
        return false;

    printf("%d",pArr->pBase[position - 1]);
}