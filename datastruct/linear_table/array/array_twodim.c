/*
二维数组的C语言实现
*/


#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	double **mat;
	int m;
	int n;
}Matrix;

void InitialMatrix(Matrix *T,int m,int n)
{
	int i;
	T->mat=(double**)malloc(m*sizeof(double*));

	for(i=0;i<m;i++)
		T->mat[i]=(double*)malloc(n*sizeof(double));

	T->m=m;				// m行
	T->n=n;				// n列
}

void FreeMatrix(Matrix *T)
{
	int i;
	for(i=0;i<(T->m);i++)
		free(T->mat[i]);
	free(T->mat);
}

void SetMatrix(Matrix *T,int m,int n)
{
	int i,j;
	for(i=0;i<(T->m);i++)
	{
		for(j=0;j<(T->n);j++)
			T->mat[i][j]=i+j;
	}
}

void PrintMatrix(Matrix *T)
{
	int i,j;
	for(i=0;i<(T->m);i++)
	{
		for(j=0;j<(T->n);j++)
			printf(" %3.0f",T->mat[i][j]);
		printf("\n");
	}
}

int returnsingledata(Matrix * T,int i,int j)
{
    return T->mat[i][j];
}


int main()
{
	Matrix p;
    Matrix * q = &p; 
    int a = 4;
    int b = 4;
    int c = 0;
	InitialMatrix(&p,a,b);
	SetMatrix(&p,a,b);
    PrintMatrix(&p);
	return 0;
}
