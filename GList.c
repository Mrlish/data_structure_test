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

typedef int AtimType;

typedef enum { ATOM, LIST }ElemTag;		//ATOM=0:原子，LIST=1：子表

typedef struct{
	ElemTag	tag;			//公共部分，用于区分原子结点和表结点
	union {
		AtimType atom;		//原子结点和表结点的联合部分
		GLNode *hp;			//表结点的表头指针
	};
	GLNode *tp;				//相当于线性链表的next，指向下一个元素结点
}GLNode,*GList;


int GListDepth(GList L)
/* 采用头尾链表存储结构，求广义表L的深度 */
{
	GList pp;
	int max, dep;
	if (!L)
		return 1;					//空表深度为1
	if (L->tag == ATOM)				//原子深度为0
		return 0;
	for (max = 0, pp = L;pp;pp = pp->tp)
	{
		dep = GListDepth(pp->hp);	//求以pp->hp为头指针的子表深度
		if (dep > max)
			max = dep;
	}
	return max + 1;					//非空表的深度是各元素的深度最大值加一
}//GListDepth


Status CopyGList(GList T, GList L)
/* 采用头尾链表存储结构，由广义表L复制得到广义表T */
{
	if (!L)
		T = NULL;				//复制空表
	else
	{
		if (!(T = (GList)malloc(sizeof(GLNode))))
			exit(OVERFLOW);				//建表结点
		T->tag = L->tag;
		if (L->tag == ATOM)
			T->atom = L->atom;			//复制单原子
		else
		{
			CopyGList(T->hp, L->hp);	//复制广义表L->hp的一个副本T->hp
			CopyGList(T->tp, L->tp);	//复制广义表L->tp的一个副本T->tp
		}
	}
	return OK;
}//CopyGList