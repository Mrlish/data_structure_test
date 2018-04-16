#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int SElemType;

typedef enum {
	ERROR = 0,
	OK = 1
}Status;


#define STACK_INIT_SIZE 100		//�洢�ռ��ʼ������
#define STACKINCREMENT  10		//�洢�ռ��������

typedef struct {
	SElemType *base;			//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;				//ջ��ָ��
	int stacksize;				//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ���ʵ�λ
}SqStack;


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
/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
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
		S->base = (SElemType*)relloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
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
