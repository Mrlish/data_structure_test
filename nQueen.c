#include<stdio.h>

#define QUEEN_NUMBER 8

int count = 0;
int isCorrect(int i, int j, int(*Q)[QUEEN_NUMBER])
/* 判断布局是否合法合法返回1否则返回0 */
{
	int s, t;
	for (s = i, t = 0; t<QUEEN_NUMBER; t++)
		if (Q[s][t] == 1 && t != j)
			return 0;	//判断行
	for (t = j, s = 0; s<QUEEN_NUMBER; s++)
		if (Q[s][t] == 1 && s != i)
			return 0;	//判断列
	for (s = i - 1, t = j - 1; s >= 0 && t >= 0; s--, t--)
		if (Q[s][t] == 1)
			return 0;	//判断左上方
	for (s = i + 1, t = j + 1; s<QUEEN_NUMBER && t<QUEEN_NUMBER;s++, t++)
		if (Q[s][t] == 1)
			return 0;	//判断右下方
	for (s = i - 1, t = j + 1; s >= 0 && t<QUEEN_NUMBER; s--, t++)
		if (Q[s][t] == 1)
			return 0;	//判断右上方
	for (s = i + 1, t = j - 1; s<QUEEN_NUMBER && t >= 0; s++, t--)
		if (Q[s][t] == 1)
			return 0;	//判断左下方

	return 1;			//合法
}

void Queue(int j, int(*Q)[QUEEN_NUMBER])
/* 从j+1行起为后续棋子选择合适的位置 */
{
	int i, k;
	if (j == QUEEN_NUMBER)			//布局完成
	{
		for (i = 0; i<QUEEN_NUMBER; i++) 
		{							//输出布局
			for (k = 0; k<QUEEN_NUMBER; k++)
				printf("%d ", Q[i][k]);
			printf("\n");
		}
		printf("\n");
		count++;
		return;
	}
	for (i = 0; i<QUEEN_NUMBER; i++) {
		if (isCorrect(i, j, Q))		//如果合法
		{
			Q[i][j] = 1;			//在i行j列放置一个棋子
			Queue(j + 1, Q);		//递归深度优先搜索解空间树
			Q[i][j] = 0;			//回溯
		}
	}
}

int main()
{
	int Q[QUEEN_NUMBER][QUEEN_NUMBER];
	int i, j;
	for (i = 0; i<QUEEN_NUMBER; i++)
		for (j = 0; j<QUEEN_NUMBER; j++)
			Q[i][j] = 0;
	Queue(0, Q);
	printf("共有 %d种摆法\n", count);
	system("pause");
}