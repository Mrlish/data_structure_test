#include "Stack.h"

typedef int MazeType;

/* �Թ���ͼ */
MazeType maze[10][10] =
{ 
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,1,1,1,0,1,0},
	{0,1,1,0,1,1,1,0,1,0},
	{0,1,1,1,1,0,0,1,1,0},
	{0,1,0,0,0,1,1,1,1,0},
	{0,1,1,1,0,1,1,1,1,0},
	{0,1,0,1,1,1,0,1,1,0},
	{0,1,0,0,0,1,0,0,1,0},
	{0,0,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0}
};


void PrintMaze(MazeType maze[10][10])
/* ��ӡ��ͼ */
{
	int x = 0, y = 0;
	printf("�Թ���ͼ:\n ");
	while (x <= 9)				//��ӡx����
	{
		printf(" %d", x);
		x++;
	}
	printf("\n");
	while (y<=9)
	{
		printf("%d", y);		//��ӡy����
		x = 0;
		while (x<=9)			//��ӡ��ͼ
		{
			if (maze[y][x])
				printf(" 0");
			else
				printf(" \1");
			x++;
		}
		y++;
		printf("\n");
	}
}


void PrintStack(SqStack S)
/* ��ջS�ĵײ���ʼ��ӡ��ջ�� */
{
	SElemType *p = S.base;
	while (p != S.top)
	{
		printf("%d ����ǰλ�ã���%d��%d�� ������%d\n", p->ord, p->seat.x, p->seat.y, p->di);
		p++;
	}
}


SElemType ElemAss(int ord, PosType seat, int di)
/* ��ջ��Ԫ�ظ�ֵ������ */
{
	SElemType e;
	e.ord = ord;
	e.seat.x = seat.x;
	e.seat.y = seat.y;
	e.di = di;
	return e;
}


PosType NextPos(PosType pos, int di)
/* ���ص�pos������di�ƶ�һ�� */
{
	switch (di)
	{
		case 1:pos.x++;break;
		case 2:pos.y++;break;
		case 3:pos.x--;break;
		case 4:pos.y--;break;
	}
	return pos;
}


Status MazePath(SqStack *S, MazeType maze[10][10], PosType start, PosType end)
/*  ���Թ�maze���ڴ����start�ߵ�����end��ͨ��
	�����һ�������ջS�У�������OK�����򷵻�ERROR */
{
	PosType curpos;							//�趨����ǰλ�á�Ϊ�����λ�á�
	SElemType e;
	int curstep = 1;						//̽����һ��
	curpos.x = start.x;
	curpos.y = start.y;
	InitStack(S);
	do
	{
		if (maze[curpos.y][curpos.x])		//��ǰλ�ÿ�ͨ��
		{
			maze[curpos.y][curpos.x] = 0;	//�����㼣
			e = ElemAss(curstep, curpos, 1);
			Push(S, e);
			if (curpos.x == end.x && curpos.y == end.y)
				return OK;					//�������
			curpos = NextPos(curpos, 1);	//̽����һ��
			curstep++;
		}
		else								//��ǰλ�ò���ͨ��
		{
			if (S->top != S->base)			//ջ�ǿ�
			{
				Pop(S, &e);					//��ջ
				while (S->top != S->base && e.di == 4)
				{
					maze[e.seat.y][e.seat.x] = 0;
					Pop(S, &e);				//���²���ͨ����ǣ�����һ��
				}
				if (e.di < 4)
				{
					e.di++;					//����һ������̽��
					Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (S->top != S->base);			//ջ�ǿ�
	return ERROR;
}


int main(void)
{
	SqStack S;
	PosType start = { 1,1 };
	PosType end = { 8,8 };
	PrintMaze(maze);

	printf("��������xֵ��yֵ\n");
	scanf("%d%d", &start.x, &start.y);
	printf("�����յ��xֵ��yֵ\n");
	scanf("%d%d", &end.x, &end.y);
	if (MazePath(&S, maze, start, end))
		printf("�ɹ��߳��Թ�\n");
	else
		printf("�޷��ҵ�����\n");
	PrintStack(S);
	PrintMaze(maze);
	system("pause");
	return 0;
}