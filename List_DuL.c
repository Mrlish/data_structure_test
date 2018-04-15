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
/* ����һ����n��Ԫ�صĴ�ͷ����˫��ѭ�����Ա�s������,ͷ����ű� */
{
	int i = 0;
	DuLinkList p, q, s;
	s = p = (DuLinkList)malloc(sizeof(DuLNode));			//����һ������ͷ�ĵ������Ա�
	do
	{
		i++;
		q = p;
		p = p->next = (DuLinkList)malloc(sizeof(DuLNode));	//����һ���µĽ��
		p->prior = q;										//ǰ��
		printf("�����%d��Ԫ�ص�ֵ:\n", i);
		scanf("%d", &p->data);								//����Ԫ��ֵ
	} while (i < n);
	p->next = s;											//��β
	s->prior = p;
	s->data = i;											//ͷ����ű�
	return s;												//���ر�ͷ
}//CreateList_DuL


DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
	DuLinkList p = L->next;			//��ʼ��pָ���һ���ڵ�
	int j = 1;						//jΪ������
	if (i > L->data)				//���ڱ�
		return NULL;

	while (p!=L && j < i)			//������ֱ��pָ���i��Ԫ�ػ�p��
	{
		p = p->next;
		j++;
	}
	if (p == L || j > i)			//��i��Ԫ�ز����ڻ�iΪ0
		return NULL;
	return p;
}


Status ListInsert_Dul(DuLinkList L, int i, ElemType e)
/* �ڴ�ͷ����˫��ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e */
{
	DuLinkList p, s;
	if (!(p = GetElemP_DuL(L, i)))			//��L��ȷ�ϲ���λ��
		return ERROR;

	if (!(s = (DuLinkList)malloc(sizeof(DuLNode))))
		return ERROR;

	s->data = e;
	s->prior = p->prior;
	s->next = p;
	p->prior->next = s;
	p->prior = s;
	L->data++;								//����һ
	return OK;
}


Status ListDelete_DuL(DuLinkList L, int i, ElemType *e)
/* ɾ����ͷ����˫ѭ�����Ա�L�ĵ�i��Ԫ�� */
{
	DuLinkList p;
	if (!(p = GetElemP_DuL(L, i)))
		return ERROR;
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	L->data--;			//����һ
	return OK;
}



/* ���� */
void PrintList(DuLinkList L)
/* ��ӡ�б�ȫ��data */
{
	DuLinkList p;
	int i = 0;

	p = L->next;
	while (p != L)
	{
		++i;
		printf("Ԫ��%d=%d\n", i, p->data);
		p = p->next;
	}
}//PrintList


int main(void)
{
	ElemType e;
	DuLinkList L, p;
	//��������
	puts("������\n");
	L = CreateList_DuL(3);
	PrintList(L);
	//�������
	puts("�ڵڶ���Ԫ��ǰ����1\n");
	ListInsert_Dul(L, 2, 1);
	PrintList(L);
	//ɾ������
	ListDelete_DuL(L, 1, &e);
	printf("ɾ����һ��Ԫ��%d\n", e);
	PrintList(L);
	////֤������ѭ��˫������
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

	puts("����������˳�");
	while (!kbhit());
	return 0;
}