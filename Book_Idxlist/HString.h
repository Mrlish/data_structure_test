#ifndef _HString_h_
#define _HString_h_

#include <stdlib.h>
#include <stdio.h>

/* 状态码 */
typedef int Status;
#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef struct {
	char *ch;		//若是非空串，则按串长分配存储区，否则ch为NULL
	int length;		//串长度
}HString;


#define NEXT_SIZE 100
int next[NEXT_SIZE];

Status StrAssign(HString *T, char *chars);
int StrLength(HString S);
int StrCompare(HString S, HString T);
Status ClearString(HString *S);
Status Concat(HString *T, HString S1, HString S2);
Status SubString(HString *Sub, HString S, int pos, int len);
void get_next(HString T, int next[NEXT_SIZE]);
int Index_KMP(HString S, HString T, int pos);

#endif // !_HString_h_

