#include "Stack.h"


int InOP(char c)
/* 如果c为运算符则返回1，否则返回0 */
{
	if (c == '+' ||
		c == '-' ||
		c == '*' ||
		c == '/' ||
		c == '(' ||
		c == ')' ||
		c == '#')
		return 1;
	else
		return 0;
}


char Precede(char a, char b)
/* 返回优先权 */
{
	switch (a)
	{
	case '+':
		switch (b)
		{
		case '+':return '>';
		case '-':return '>';
		case '*':return '<';
		case '/':return '<';
		case '(':return '<';
		case ')':return '>';
		case '#':return '>';
		}
	case '-':
		switch (b)
		{
		case '+':return '>';
		case '-':return '>';
		case '*':return '<';
		case '/':return '<';
		case '(':return '<';
		case ')':return '>';
		case '#':return '>';
		}
	case '*':
		switch (b)
		{
		case '+':return '>';
		case '-':return '>';
		case '*':return '>';
		case '/':return '>';
		case '(':return '<';
		case ')':return '>';
		case '#':return '>';
		}
	case '/':
		switch (b)
		{
		case '+':return '>';
		case '-':return '>';
		case '*':return '>';
		case '/':return '>';
		case '(':return '<';
		case ')':return '>';
		case '#':return '>';
		}
	case '(':
		switch (b)
		{
		case '+':return '<';
		case '-':return '<';
		case '*':return '<';
		case '/':return '<';
		case '(':return '<';
		case ')':return '=';
		case '#':return ' ';
		}
	case ')':
		switch (b)
		{
		case '+':return '>';
		case '-':return '>';
		case '*':return '>';
		case '/':return '>';
		case '(':return ' ';
		case ')':return '>';
		case '#':return '>';
		}
	case '#':
		switch (b)
		{
		case '+':return '<';
		case '-':return '<';
		case '*':return '<';
		case '/':return '<';
		case '(':return '<';
		case ')':return ' ';
		case '#':return '=';
		}
	}
}


char Operate(char a, char theta, char b)
/* 运算 */
{
	b -= 0x30;		
	a -= 0x30;
	switch (theta)
	{
	case '+':return (a + b) + 0x30;
	case '-':return (a - b) + 0x30;
	case '*':return (a * b) + 0x30;
	case '/':return (a / b) + 0x30;
	}
}


char EvaluateExpression()
/* 算术表达式求值的算符优先算法 */
{
	SElemType c, x, a, b, s, theta;
	SqStack OPTR, OPND;
	InitStack(&OPTR);
	InitStack(&OPND);
	Push(&OPTR, '#');
	c = getchar();
	GetTop(OPTR, &x);
	while (c != '#' || x != '#')
	{
		if (InOP(c) == 0)		//非运算符
		{
			Push(&OPND, c);		//进栈
			c = getchar();
		}
		else
		{
			GetTop(OPTR, &x);
			switch (Precede(x, c))
			{
			case '<':			//栈顶元素优先级低
				Push(&OPTR, c);	//进栈
				c = getchar();
				break;
			case '=':			//脱括号并接收下一个字符
				Pop(&OPTR, &s);	//括号出栈
				c = getchar();
				break;
			case '>':			//退栈并将运算结果入栈
				Pop(&OPTR, &theta);
				Pop(&OPND, &b);
				Pop(&OPND, &a);
				Push(&OPND, Operate(a, theta, b));
				break;
			}
		}
	}
	GetTop(OPND, &x);
	return x;
}


int main(void)
{
	char a;
	a = EvaluateExpression();
	printf("运算结果=%i", a-0x30);
	system("pause");
}