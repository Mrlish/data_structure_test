#include "Stack.h"

typedef int MazeType;

/* 迷宫地图 */
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
/* 打印地图 */
{
	int x = 0, y = 0;
	printf("迷宫地图:\n ");
	while (x <= 9)				//打印x坐标
	{
		printf(" %d", x);
		x++;
	}
	printf("\n");
	while (y<=9)
	{
		printf("%d", y);		//打印y坐标
		x = 0;
		while (x<=9)			//打印地图
		{
			switch (maze[y][x])
			{
			case 0:printf("■");break;
			case 1:printf("  ");break;
			case 2:printf("→");break;
			case 3:printf("↓");break;
			case 4:printf("←");break;
			case 5:printf("↑");break;
			case 6:printf(" X");break;
			}	
			x++;
		}
		y++;
		printf("\n");
	}
}


void PrintStack(MazeType maze[10][10], SqStack S)
/* 从栈S的底部开始打印到栈顶 */
{
	SElemType *p = S.base;
	while (p != S.top)
	{
		printf("%d ：当前位置：（%d，%d） 往方向%d\n", p->ord, p->seat.x, p->seat.y, p->di);
		maze[p->seat.y][p->seat.x] = p->di + 1;  //为了在地图上显示路径，对地图做了下处理
		p++;
	}
}


SElemType ElemAss(int ord, PosType seat, int di)
/* 给栈的元素赋值并返回 */
{
	SElemType e;
	e.ord = ord;
	e.seat.x = seat.x;
	e.seat.y = seat.y;
	e.di = di;
	return e;
}


PosType NextPos(PosType pos, int di)
/* 返回点pos往方向di移动一步 */
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
/*  若迷宫maze存在从入口start走到出口end的通道
	则求得一条存放在栈S中，并返回OK，否则返回ERROR */
{
	PosType curpos;							
	SElemType e;
	int curstep = 1;						//探索第一步
	curpos.x = start.x;						//设定“当前位置”为“入口位置”
	curpos.y = start.y;
	InitStack(S);
	do
	{
		if (maze[curpos.y][curpos.x]  &&
			maze[curpos.y][curpos.x] != 6)	//当前位置可通过
		{
			maze[curpos.y][curpos.x] = 6;	//留下足迹
			e = ElemAss(curstep, curpos, 1);
			Push(S, e);
			if (curpos.x == end.x && curpos.y == end.y)
				return OK;					//到达出口
			curpos = NextPos(curpos, 1);	//探索下一步
			curstep++;
		}
		else								//当前位置不能通过
		{
			if (S->top != S->base)			//栈非空
			{
				Pop(S, &e);					//退栈
				while (S->top != S->base && e.di == 4)
				{
					maze[e.seat.y][e.seat.x] = 6;
					Pop(S, &e);				//留下不能通过标记，并退一格
				}
				if (e.di < 4)
				{
					e.di++;					//换下一个方向探索
					Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (S->top != S->base);			//栈非空
	return ERROR;
}


int main(void)
{
	SqStack S;
	PosType start;
	PosType end;
	PrintMaze(maze);

	printf("输入起点的x值和y值\n");
	scanf("%d%d", &start.x, &start.y);
	printf("输入终点的x值和y值\n");
	scanf("%d%d", &end.x, &end.y);
	if (MazePath(&S, maze, start, end))
		printf("成功走出迷宫\n");
	else
		printf("无法找到出口\n");
	PrintStack(maze, S);
	PrintMaze(maze);
	system("pause");
	return 0;
}