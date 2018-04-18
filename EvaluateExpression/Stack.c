﻿#include "Stack.h"


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
/* 若栈不空则用e返回S的栈顶元素 */
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
		S->base = (SElemType*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
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

