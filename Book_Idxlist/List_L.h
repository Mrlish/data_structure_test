#ifndef _List_L_h_
#define _List_L_h_

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


typedef int ElemType;

/* 单链表 */
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

LinkList CreateList_L(int n);
Status GetElem_L(const LinkList L, int i, ElemType *e);
Status ListInser_L(LinkList L, int i, ElemType e);
Status ListDelete_L(LinkList L, int i, ElemType *e);
void MergeList_L(LinkList La, LinkList Lb);

#endif // !_List_L_h_