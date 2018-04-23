#include <stdarg.h>
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
#define UNDERFLOW	-3


#define MAX_ARRAY_DIM	8	//数组维数最大值为8

typedef int ElemType;

typedef struct {
	ElemType *base;		//数组元素基址
	int dim;			//数组维数
	int *bounds;		//数组维界基地址
	int *constants;		//数组映像函数常量基地址
}Array;


Status InitArray(Array *A, int dim, ...)
/* 若维数dim和随后的各维长度合法，则构造相应的数组A，并返回OK */
{
	int elemtotal, i;
	va_list ap;
	if (dim<1 || dim>MAX_ARRAY_DIM)
		return ERROR;
	A->dim = dim;
	A->bounds = (int*)malloc(dim * sizeof(int));
	if (!A->bounds)
		exit(OVERFLOW);
	//若各维长度合法，则存入A.bounds,并求出A的元素总数elemtotal
	elemtotal = 1;
	va_start(ap, dim);		//ap是存放变长参数表信息的数组
	for (i = 0;i < dim;++i)
	{
		A->bounds[i] = va_arg(ap, int);
		if (A->bounds[i] < 0)
			return UNDERFLOW;
		elemtotal *= A->bounds[i];
	}
	va_end(ap);
	A->base = (ElemType*)malloc(elemtotal * sizeof(ElemType));
	if (!A->base)
		exit(OVERFLOW);
	//求映像函数的常数ci并存入A.constants[i-1],i=1....dim
	A->constants = (int*)malloc(dim * sizeof(int));
	if (!A->constants)
		exit(OVERFLOW);
	A->constants[dim - 1] = 1;		//L=1,指针的增减以元素大小为单位
	for (i = dim - 1;i >= 0;--i)
		A->constants[i] = A->bounds[i + 1] * A->constants[i + 1];
	return OK;
}//InitArray


Status DestroyArray(Array *A)
/* 销毁数组A */
{
	if (!A->base)
		return ERROR;
	free(A->base);
	A->base = NULL;
	if(!A->bounds)
		return ERROR;
	free(A->bounds);
	A->base = NULL;
	if (!A->constants)
		return ERROR;
	free(A->constants);
	A->constants = NULL;
	return OK;
}


Status Locate(Array A, va_list ap, int *off)
/* 若ap指示的各下标值合法，则求出该元素在A中相对地址off */
{
	int i, ind;
	*off = 0;
	for ( i = 0; i < A.dim; i++)
	{
		ind = va_arg(ap, int);
		if (ind < 0 || ind >= A.bounds[i])
			return OVERFLOW;
		*off += A.constants[i]*ind;
	}
	return OK;
}


Status Value(Array A, ElemType *e, ...)
/* A是n维数组，e为元素变量，随后是n个下标值
	若下标不超界，则e赋值为所指定的A的元素值并返回OK */
{
	int off;
	Status result;
	va_list ap;
	va_start(ap, *e);
	if ((result = Locate(A, ap, &off)) <=0)
		return result;
	*e = *(A.base + off);
	return OK;
}


int main(void)
{
	Array a1;
	int off;
	ElemType a;
	InitArray(&a1, 3, 3, 3, 3);
	Value(a1, &a, 1, 1, 1);
	printf("%d", a);
	system("pause");
}