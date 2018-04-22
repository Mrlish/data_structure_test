#include "HString.h"


Status StrAssign(HString *T, char *chars)
/* 生成一个其值等于串常量chars的串T */
{
	int i,j;
	char *c;
	if (T->ch)								//释放T原有的空间
		free(T->ch);
	for (i = 0, c = chars; *c; ++i, ++c);	//求chars的长度i
	if (!i)
	{
		T->ch = NULL;
		T->length = 0;
	}
	else
	{
		if (!(T->ch = (char *)malloc(i * sizeof(char))))
			exit(OVERFLOW);
		for ( j = 0; j < i; j++)
			T->ch[j] = chars[j];
		T->length = i;
	}
	return OK;
}//StrAssign


int StrLength(HString S)
/* 返回S的元素个数（串的长度） */
{
	return S.length;
}//StrLength


int StrCompare(HString S, HString T)
/* 若S>T,则返回值>0;若S=T，则返回值=0；若S<T，则返回值<0 */
{
	int i;
	for ( i = 0; i < S.length && i < T.length; ++i)
	{
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}//StrCompare


Status ClearString(HString *S)
/* 将S清为空串 */
{
	if (S->ch)
	{
		free(S->ch);
		S->ch = NULL;
	}
	S->length = 0;
	return OK;
}//ClearString


Status Concat(HString *T, HString S1, HString S2)
/* 用T返回由S1和S2联接而成的新串 */
{
	int i,j;
	if (T->ch)			//释放旧空间
		free(T->ch);
	if (!(T->ch = (char *)malloc((S1.length + S2.length) * sizeof(char))))
		exit(OVERFLOW);
	for ( i = 0; i < S1.length; i++)
		T->ch[i] = S1.ch[i];
	T->length = S1.length + S2.length;
	for (i = S1.length, j = 0; i < T->length; i++, j++)
		T->ch[i] = S2.ch[j];
	return OK;
}//Concat


Status SubString(HString *Sub, HString S, int pos, int len)
/* 用Sub返回串S的第pos个字符起长度为len的字符串 */
{
	int i, j;
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;			//输入错误
	if (Sub->ch)
		free(Sub->ch);			//释放旧空间
	if (!len)					//空子串
	{
		Sub->ch = NULL;
		Sub->length = 0;
	}
	else						//完整子串
	{
		Sub->ch = (char *)malloc(len * sizeof(char));
		for (i = 0, j = pos - 1; i < len; i++, j++)
		{
			Sub->ch[i] = S.ch[j];
		}
		Sub->length = len;
	}
	return OK;
}//SubString





void get_next(HString T, int next[NEXT_SIZE])
/* 求模式串T的next值并存入数组next */
{
	int i = 1, j = 0;
	while (i < T.length)
	{
		if (j == 0 || T.ch[i - 1] && T.ch[j - 1])
		{
			++i;
			++j;
			if (T.ch[i - 1] != T.ch[j - 1])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}
}//get_next


int Index_KMP(HString S, HString T, int pos)
/* 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法 */
{
	int i = pos, j = 1;
	while (i <= S.length && j <= T.length)
	{
		if (j == 0 || S.ch[i - 1] == T.ch[j - 1])
		{
			++i;			//继续比较后继字符
			++j;
		}
		else
			j = next[j];	//模式串向右移动
	}
	if (j > T.length)		//匹配成功
		return i - T.length;
	else
		return 0;
}//Index_KMP
