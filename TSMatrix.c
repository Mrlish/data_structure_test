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

#define MAXRC	MAXSIZE

typedef struct {
	Triple data[MAXSIZE + 1];	//非零元三元组表
	int rpos[MAXRC + 1];		//各行第一个非零元的位置表
	int mu;						//矩阵的行数
	int nu;						//矩阵的列数
	int tu;						//矩阵的非零元素
}RLSMatrix;


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


Status FastTransposeSMaxrix(TSMatrix M, TSMatrix *T)
/* 采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵（快速转置） */
{
	int col,t,p,q;
	int num[MAXRC+1],cpot[MAXRC+1];
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;
	if (T->mu)
	{
		for (col = 1;col <= M.nu;++col)
			num[col] = 0;
		for (t = 1;t <= M.tu;++t)
			++num[M.data[t].j];			//求M中每一列含非零元个数
		cpot[1] = 1;
		for (col = 2;col <= M.nu;++col)
			cpot[col] = cpot[col - 1] + num[col - 1];
		for (p = 1;p <= M.tu;++p)
		{
			col = M.data[p].j;
			q = cpot[col];
			T->data[q].i = M.data[p].j;
			T->data[q].j = M.data[p].i;
			T->data[q].e = M.data[p].e;
			++cpot[col];
		}
	}
	return OK;
}//FastTransposeSMaxrix


Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q)
/* 求矩阵乘积Q=MXN，采用行逻辑链接存储表示 */
{
	int arow,tp,p,brow,t,q,ccol;
	int ctemp[MAXRC];
	if (M.nu != N.mu)
		return ERROR;
	Q->mu = M.mu;
	Q->nu = N.nu;
	Q->tu = 0;				//Q初始化
	if (M.tu*N.tu != 0)
	{
		for(arow = 1;arow<=M.mu;++arow)
		{
			memset(ctemp, 0, sizeof(ctemp));	//当前行各元素累加器清0
			Q->rpos[arow] = Q->tu + 1;
			if (arow < M.mu)
				tp = M.rpos[arow + 1];
			else
				tp = M.tu + 1;
			for (p = M.rpos[arow];p < tp;++p)
			{
				brow = M.data[p].j;				//对当前行中每一个非零元找到对应元在N中的行号
				if (brow < N.mu)
					t = N.rpos[brow + 1];
				else
					t = N.tu + 1;
				for (q = N.rpos[brow];q < t;++q)
				{
					ccol = N.data[q].j;			//乘积元素在Q中列号
					ctemp[ccol] += M.data[p].e*N.data[q].e;
				}
				//求得Q中第crpw（=arow）行的非零元
				for(ccol = 1;ccol<=Q->nu;++ccol)	//压缩存储该行非零元
					if (ctemp[ccol])
					{
						if (++Q->tu > MAXSIZE)
							return ERROR;
						Q->data[Q->tu].i = arow;
						Q->data[Q->tu].j = ccol;
						Q->data[Q->tu].e = ctemp[ccol];
					}
			}
		}
	}
	return OK;
}//MultSMatrix