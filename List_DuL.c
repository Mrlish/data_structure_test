#include <stdlib.h>
#include <stdio.h>

typedef int ElemType;

typedef enum {
	ERROR = 0,
	OK = 1
}Status;

typedef struct DuLNode {
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode, *DuLinkList;


DuLinkList CreateList_DuL(int n)
/* 建立一个有n个元素的带头结点的双链循环线性表s并返回,头结点存放表长 */
{
	int i = 0;
	DuLinkList p, q, s;
	s = p = (DuLinkList)malloc(sizeof(DuLNode));			//建立一个带表头的单链线性表
	do
	{
		i++;
		q = p;
		p = p->next = (DuLinkList)malloc(sizeof(DuLNode));	//建立一个新的结点
		p->prior = q;										//前驱
		printf("输入第%d个元素的值:\n", i);
		scanf("%d", &p->data);								//输入元素值
	} while (i < n);
	p->next = s;											//表尾
	s->prior = p;
	s->data = i;											//头结点存放表长
	return s;												//返回表头
}//CreateList_DuL


DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
	DuLinkList p = L->next;			//初始化p指向第一个节点
	int j = 1;						//j为计数器
	if (i > L->data)				//大于表长
		return NULL;

	while (p!=L && j < i)			//向后查找直到p指向第i个元素或p空
	{
		p = p->next;
		j++;
	}
	if (p == L || j > i)			//第i个元素不存在或i为0
		return NULL;
	return p;
}


Status ListInsert_Dul(DuLinkList L, int i, ElemType e)
/* 在带头结点的双链循环线性表L中第i个位置之前插入元素e */
{
	DuLinkList p, s;
	if (!(p = GetElemP_DuL(L, i)))			//在L中确认插入位置
		return ERROR;

	if (!(s = (DuLinkList)malloc(sizeof(DuLNode))))
		return ERROR;

	s->data = e;
	s->prior = p->prior;
	s->next = p;
	p->prior->next = s;
	p->prior = s;
	L->data++;								//表长加一
	return OK;
}


Status ListDelete_DuL(DuLinkList L, int i, ElemType *e)
/* 删除带头结点的双循环线性表L的第i个元素 */
{
	DuLinkList p;
	if (!(p = GetElemP_DuL(L, i)))
		return ERROR;
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	L->data--;			//表长减一
	return OK;
}



/* 测试 */
void PrintList(DuLinkList L)
/* 打印列表全部data */
{
	DuLinkList p;
	int i = 0;

	p = L->next;
	while (p != L)
	{
		++i;
		printf("元素%d=%d\n", i, p->data);
		p = p->next;
	}
}//PrintList


int main(void)
{
	ElemType e;
	DuLinkList L, p;
	//创建测试
	puts("创建表\n");
	L = CreateList_DuL(3);
	PrintList(L);
	//插入测试
	puts("在第二个元素前插入1\n");
	ListInsert_Dul(L, 2, 1);
	PrintList(L);
	//删除测试
	ListDelete_DuL(L, 1, &e);
	printf("删除第一个元素%d\n", e);
	PrintList(L);
	////证明它是循环双向链表
	//p = L;
	//while (1)
	//{
	//	printf("%d\n", p->data);
	//	p = p->next;
	//}
	//p = L;
	//while (1)
	//{
	//	printf("%d\n", p->data);
	//	p = p->prior;
	//}

	puts("按下任意键退出");
	while (!kbhit());
	return 0;
}