#include <stdlib.h>
#include <stdio.h>

/* 状态码 */
typedef int Status;
#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

#define MAXSIZE 12500	//假设非零元个数的最大值为12500

typedef int ElemType;

typedef struct {
	int i, j;		//行下标和列下标
	ElemType e;		
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];	//非零元三元组列表，data[0]未用
	int mu;						//矩阵的行数
	int nu;						//矩阵的列数
	int tu;						//矩阵的非零元素
}TSMatrix;


Status TransposeSMatrix(TSMatrix M, TSMatrix *T)
/* 采用三元组表存储表示，求稀疏矩阵M的转置矩阵T */
{
	int p, q, col;
	T->mu = M.nu;		//把矩阵的行列转换
	T->nu = M.mu;
	T->tu = M.tu;
	if (T->tu)
	{
		q = 1;
		for (col = 1;col <= M.mu;++col)
			for (p = 1;p <= M.tu;++p)
				if (M.data[p].j == col)
				{
					T->data[q].i = M.data[p].j;
					T->data[q].j = M.data[p].i;
					T->data[q].e = M.data[p].e;
					++q;
				}
	}
	return OK;
}//TransposeSMatrix