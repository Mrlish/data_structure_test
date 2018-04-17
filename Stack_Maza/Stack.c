#include "Stack.h"


Status InitStack(SqStack *S)
/* ����һ����ջ */
{
	S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S->base)				//�洢����ʧ��
		exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStack


Status GetTop(SqStack S, SElemType *e)
/* ��ջ��������e����S��ջ��Ԫ�� */
{
	if (S.top == S.base)
		return ERROR;
	*e = *(S.top - 1);
	return OK;
}//InitStack


Status Push(SqStack *S, SElemType e)
/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
{
	if (S->top - S->base >= S->stacksize)	//ջ����׷�Ӵ洢�ռ�
	{
		S->base = (SElemType*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S->base)
			exit(OVERFLOW);					//�洢����ʧ��
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return OK;
}//Push


Status Pop(SqStack *S, SElemType *e)
/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ
   �ɹ�����OK�����򷵻�ERROR	*/
{
	if (S->top == S->base)
		return ERROR;
	*e = *--S->top;
	return OK;
}//Pop

