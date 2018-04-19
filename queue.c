#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum {
	ERROR = 0,
	OK = 1
}Status;

#define USE_SqQueue

#ifndef USE_SqQueue

/*--------单链队列-----------*/
typedef int QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;		//队头指针
	QueuePtr rear;		//队尾指针
}LinkQueue;


Status InitQueue(LinkQueue *Q)
/* 构造一个空队列Q */
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q) exit(OVERFLOW);	//存储分配失败
	Q->rear->next = NULL;
	return OK;
}//InitQueue


Status DestroyQueue(LinkQueue *Q)
/* 销毁队列Q */
{
	while (Q->front)	//队列非空
	{
		Q->rear = Q->front->next;
		free(Q->front);	//删除
		Q->front = Q->rear;
	}
	return OK;
}//DestroyQueue


Status EnQueue(LinkQueue *Q, QElemType e)
/* 插入元素e到队列Q */
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);		//存储分配失败
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}


Status DeQueue(LinkQueue *Q, QElemType *e)
/* 若队列非空，删除队头的元素并用e返回
	成功返回OK，否则返回ERROR	*/
{
	QueuePtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;			//p指向队列头元素
	*e = p->data;
	Q->front->next = p->next;
	if (p == Q->rear)			//队列空
		Q->front = Q->rear;		
	free(p);					//删除队列头元素
	return OK;
}



#else
/*--------循环队列-----------*/
#define MAXQSIZE 100	//最大队列长度

typedef int QElemType;

typedef struct {
	QElemType *base;	//初始化动态分配存储空间
	int front;			//头指针，若队列不空，指向队列头元素
	int rear;			//尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;


Status InitQueue(SqQueue *Q)
/* 构造一个空循环队列 */
{
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base) exit(OVERFLOW);	//存储分配失败
	Q->front = Q->rear = 0;
	return OK;
}


int QueueLength(SqQueue Q)
/* 返回Q的元素个数，即队列长度 */
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}


Status EnQueue(SqQueue *Q, QElemType e)
/* 插入元素e为Q的新的队尾元素 */
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return ERROR;		//队列满
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}


Status DeQueue(SqQueue *Q, QElemType *e)
/* 若队列非空，则删除Q的队头元素，用e返回其值
	若成功 返回OK，否则返回ERROR */
{
	if (Q->front == Q->rear)
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

#endif

/* 测试 */
int main(void)
{
	int i;
	QElemType a;
	SqQueue Q;
	InitQueue(&Q);
	for (i = 0;i < 100;i++)
	{
		EnQueue(&Q, i);
	}
	i = QueueLength(Q);
	printf("队列长度=%d\n", i);
	for ( i = 0; i < 100; i++)
	{
		DeQueue(&Q, &a);
		printf("元素%d=%d\n",i, a);
	}
	i = QueueLength(Q);
	printf("队列长度=%d\n", i);

	system("pause");
}