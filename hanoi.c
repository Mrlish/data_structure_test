#include <stdlib.h>
#include <stdio.h>

int count;

void move(char a, int n, char b)
{
	printf("%d.移动盘子%d  %c -> %c\n", ++count, n, a, b);
}


void hanoi(int n, char x, char y, char z)
{
	if (n == 1)
		move(x, 1, z);			//将编号为1的圆盘从x移动到z
	else
	{
		hanoi(n - 1, x, z, y);	//将x上编号为1到n-1的圆盘移动到y，z作辅助塔
		move(x, n, y);			//将编号为n的圆盘从x移动到z
		hanoi(n - 1, y, x, z);	//将y上编号为1至n-1的圆盘移动到z，x作辅助塔
	}
}


int main(void)
{
	hanoi(10, 'x', 'y', 'z');
	system("pause");
}