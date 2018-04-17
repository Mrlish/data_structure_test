#ifndef _Stack_h_
#define _Stack_h_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
	int x;
	int y;
}PosType;

typedef struct {
	int ord;		//ͨ����·���ϵġ���š�		
	PosType seat;	//ͨ�����Թ��еġ�����λ�á�
	int di;			//�Ӵ�ͨ������һͨ���ġ�����
}SElemType;

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


Status InitStack(SqStack *S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);

#endif // !_Stack_h_
