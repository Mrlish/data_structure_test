#include "List_L.h"


LinkList CreateList_L(int n)
/* 建立有n个元素的带头结点的单链线性表并返回 */
{
	int i = 0;
	LinkList p, q;
	q = p = (LinkList)malloc(sizeof(LNode));	//建立一个带表头的单链线性表
	do
	{
		i++;
		p = p->next = (LinkList)malloc(sizeof(LNode));	//建立一个新的结点
		printf("输入第%d个元素的值:\n", i);
		scanf("%d", &p->data);							//输入元素值
	} while (i < n);
	p->next = NULL;										//表尾
	return q;											//返回表头
}//CreateList_L


Status GetElem_L(const LinkList L, int i ,ElemType *e)
/* L为带头结点的单链表的头指针
	当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR */
{
	LinkList p = L->next;			//初始化p指向第一个节点
	int j = 1;						//j为计数器
	while (p && j < i)				//向后查找直到p指向第i个元素或p空
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)				//第i个元素不存在或i为0
		return ERROR;
	*e = p->data;					//取第i个元素
	return OK;
}//GetElem


Status ListInser_L(LinkList L, int i, ElemType e)
/* 在带头结点的单链线性表L中第i个位置插入元素e */
{
	LinkList p = L;
	LinkList s;
	int j = 0;

	while (p && j < i - 1)					//寻找第i-1个结点
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)					//i小于1或大于表长+1
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));	//生成新结点
	s->data = e;							//插入L中
	s->next = p->next;
	p->next = s;
	return OK;
}//ListInser_L


Status ListDelete_L(LinkList L, int i, ElemType *e)
/* 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值 */
{
	LinkList p = L;
	LinkList q;
	int j = 0;

	while (p->next && j < i - 1)				//寻找第i个节点，并令p指向其前趋
	{
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1)					//删除位置不合理
		return ERROR;
	q = p->next;								//q指向要删除的结点
	p->next = q->next;
	*e = q->data;								//返回删除的元素
	free(q);									//释放结点
	return OK;
}//ListDelete_L


void MergeList_L(LinkList La, LinkList Lb)
/*	已知单链线性表La和Lb的元素按值非递减排列
	归并La和Lb得到新的单链线性表La */
{
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = La;				//La的头节点作为Lc的头节点
	while (pa && pb)				//归并
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pb = pb->next;
		}
		pc = pc->next;
	}
	pc->next = pa ? pa : pb;
	free(Lb);				//释放Lb头结点
}//MergeList_L


