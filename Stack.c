#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int SElemType;

typedef enum {
	ERROR = 0,
	OK = 1
}Status;


#define STACK_INIT_SIZE 100		//存储空间初始分配量
#define STACKINCREMENT  10		//存储空间分配增量

typedef struct {
	SElemType *base;			//在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;				//栈顶指针
	int stacksize;				//当前已分配的存储空间，以元素问单位
}SqStack;


Status InitStack(SqStack *S)
/* 构造一个空栈 */
{
	S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S->base)				//存储分配失败
		exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStack


Status GetTop(SqStack S, SElemType *e)
/* 插入元素e为新的栈顶元素 */
{
	if (S.top == S.base)
		return ERROR;
	*e = *(S.top - 1);
	return OK;
}//InitStack


Status Push(SqStack *S, SElemType e)
/* 插入元素e为新的栈顶元素 */
{
	if (S->top - S->base >= S->stacksize)	//栈满，追加存储空间
	{
		S->base = (SElemType*)relloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S->base)
			exit(OVERFLOW);					//存储分配失败
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return OK;
}//Push


Status Pop(SqStack *S, SElemType *e)
/* 若栈不空，则删除S的栈顶元素，用e返回其值
   成功返回OK；否则返回ERROR	*/
{
	if (S->top == S->base)
		return ERROR;
	*e = *--S->top;
	return OK;
}//Pop
