#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int ElemType;

typedef enum {
	ERROR = 0,
	OK = 1
}Status;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;


LinkList CreateList_L(int n)
/* ������n��Ԫ�صĴ�ͷ���ĵ������Ա����� */
{
	int i = 0;
	LinkList p, q;
	q = p = (LinkList)malloc(sizeof(LNode));			//����һ������ͷ�ĵ������Ա�
	do
	{
		i++;
		p = p->next = (LinkList)malloc(sizeof(LNode));	//����һ���µĽ��
		printf("�����%d��Ԫ�ص�ֵ:\n", i);
		scanf("%d", &p->data);							//����Ԫ��ֵ
	} while (i < n);
	p->next = NULL;										//��β
	return q;											//���ر�ͷ
}//CreateList_L


Status GetElem_L(const LinkList L, int i ,ElemType *e)
/* LΪ��ͷ���ĵ������ͷָ��
	����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR */
{
	LinkList p = L->next;			//��ʼ��pָ���һ���ڵ�
	int j = 1;						//jΪ������
	while (p && j < i)				//������ֱ��pָ���i��Ԫ�ػ�p��
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)				//��i��Ԫ�ز����ڻ�iΪ0
		return ERROR;
	*e = p->data;					//ȡ��i��Ԫ��
	return OK;
}//GetElem


Status ListInser_L(LinkList L, int i, ElemType e)
/* �ڴ�ͷ���ĵ������Ա�L�е�i��λ�ò���Ԫ��e */
{
	LinkList p = L;
	LinkList s;
	int j = 0;

	while (p && j < i - 1)					//Ѱ�ҵ�i-1�����
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)					//iС��1����ڱ�+1
		return ERROR;
	s = (LinkList)malloc(sizeof(LNode));	//�����½��
	s->data = e;							//����L��
	s->next = p->next;
	p->next = s;
	return OK;
}//ListInser_L


Status ListDelete_L(LinkList L, int i, ElemType *e)
/* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ */
{
	LinkList p = L;
	LinkList q;
	int j = 0;

	while (p->next && j < i - 1)				//Ѱ�ҵ�i���ڵ㣬����pָ����ǰ��
	{
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1)					//ɾ��λ�ò�����
		return ERROR;
	q = p->next;								//qָ��Ҫɾ���Ľ��
	p->next = q->next;
	*e = q->data;								//����ɾ����Ԫ��
	free(q);									//�ͷŽ��
	return OK;
}//ListDelete_L


void MergeList_L(LinkList La, LinkList Lb)
/*	��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
	�鲢La��Lb�õ��µĵ������Ա�La */
{
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = La;				//La��ͷ�ڵ���ΪLc��ͷ�ڵ�
	while (pa && pb)				//�鲢
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
	free(Lb);				//�ͷ�Lbͷ���
}//MergeList_L


/**********************************************************
					  ����
***********************************************************/
#define LIST_CREATE_LENGTH 3

void PrintList(LinkList L)
/*  ��֪LΪ��ͷ��ͷ���ĵ������Ա�
	  ��ӡ�б�ȫ��data           */
{
	LinkList p;
	int i = 0;

	p = L->next;
	while (p != NULL)
	{
		++i;
		printf("Ԫ��%d=%d\n", i, p->data);
		p = p->next;
	}
}//PrintList

int main(void)
{
	LinkList La, Lb;
	ElemType e;
	//����
	La = CreateList_L(LIST_CREATE_LENGTH);
	puts("����\n");
	PrintList(La);
	GetElem_L(La, 3, &e);
	printf("��3��Ԫ��=%d", e);
	//����
	ListInser_L(La, 2, 12);
	puts("����\n");
	PrintList(La);
	//ɾ��
	ListDelete_L(La, 1, &e);
	printf("ɾ������%d\n", e);
	PrintList(La);
	//����
	free(La);
	puts("����,������������õ���\n");
	La = CreateList_L(LIST_CREATE_LENGTH);
	Lb = CreateList_L(LIST_CREATE_LENGTH);
	MergeList_L(La, Lb);
	PrintList(La);

	puts("����������˳�");
	while (!kbhit());
	return 0;
}

/***********************************************************/