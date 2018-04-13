#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LIST_INIT_SIZE	100
#define LISTINCREMENT	10

typedef int ElemType;

typedef enum {
	ERROR = 0,
	OK = 1
}Status;

typedef struct {
	ElemType *elem;
	int length;
	int listsize;
}SqList;


Status InitList_Sq(SqList *L)
/* 构造一个空的线性表 */
{	
	L->elem = (ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
	if (!L->elem) exit(OVERFLOW);		//存储分配失败
	L->length = 0;						//空间长度为0
	L->listsize = LIST_INIT_SIZE;		//初始存储容量
	return OK;
}//InitList_Sq


Status ListInsert_Sq(SqList *L, int i, ElemType e)
/* 在顺序线性表L中第i个位置插入新的元素e
    i的合法值为 1 <= i <= ListLength+1 */
{
	ElemType *newbase, *p, *q;

	if (i < 1 || i > L->length + 1) return ERROR;		//i值不合法
	if (L->length >= L->listsize)						//当前空间已满，增加分配
	{
		newbase = realloc(L->elem, sizeof(ElemType)*(L->listsize + LISTINCREMENT));
		if (!newbase) exit(OVERFLOW);					//存储分配失败
		L->listsize += LISTINCREMENT;					//增加存储容量
	}
	q = &(L->elem[i - 1]);
	for (p = &(L->elem[L->length - 1]);p >= q; --p)		//插入位置及之后的元素右移
		*(p + 1) = *p;
	*q = e;												//插入e
	++L->length;										//表长+1
	return OK;
}//ListInsert_Sq


Status ListDelete_Sq(SqList *L, int i, ElemType *e)
/* 在顺序线性表L中输出第i个元素，并用e返回其值
	i的合法值为 1 <= i <= ListLength+1 */
{
	ElemType *p, *q;

	if (i < 1 || i > L->length + 1) return ERROR;		//i值不合法
	p = &L->elem[i - 1];								//p为被删除元素的位置
	*e = *p;											//被删除元素的值赋给e
	q = L->elem + L->length - 1;						//表尾元素的位置
	for (++p; p <= q; p++) *(p - 1) = *p;				//被删除元素之后的元素左移
	--L->length;
	return OK;
}//ListDelete_Sq


int LocateElem_Sq(SqList L, ElemType e, int (* compare)(ElemType, ElemType))
/* 在顺序列表L中查找第1个值与e满足compare()元素的位序
	若找到，则返回其在L中的位序，否则返回0*/
{
	ElemType *p = L.elem;;									//p的初值为第一个元素的存储位置
	int i = 1;												//i的初值为第一个元素的位序			
	while (i <= L.length && !(*compare)(*p++, e)) ++i;
	if (i <= L.length) return i;
	else return 0;
}//LocateElem_Sq


void MergeList_Sq(SqList La, SqList Lb, SqList *Lc)
/* 已知顺序线性表La和Lb的元素按值非递减排列
	归并La和Lb得到新的顺序线性表Lc，Lc的元素也按非递减排列 */
{
	ElemType *pa_last = La.elem + La.length - 1;
	ElemType *pb_last = Lb.elem + Lb.length - 1;
	ElemType *pa = La.elem;
	ElemType *pb = Lb.elem;
	ElemType *pc ;

	Lc->listsize = Lc->length = La.length + Lb.length;	//Lc初始化
	pc = Lc->elem = (ElemType*)malloc(Lc->listsize * sizeof(ElemType));
	if (!Lc->elem) exit(OVERFLOW);						//存储分配失败
	while (pa <= pa_last && pb <= pb_last)				//归并
	{
		if (*pa <= *pb)	*pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last) *pc++ = *pa++;				//插入La剩余的元素
	while (pb <= pb_last) *pc++ = *pb++;				//插入Lb剩余的元素
}//MergeList_Sq


int equal(int a, int b)
{
	return a == b ? 1 : 0;
}



/* 测试 */
int main(void)
{
	int i;
	ElemType e;
	SqList L,L1,L2;
	InitList_Sq(&L);
	// 创建和删除测试
	for(i = 0;i<123;i++)
	{
		ListInsert_Sq(&L, i + 1, i);
	}
	i = 0;
	do
	{
		printf("元素%d=%d\n", i + 1, L.elem[i]);
	} while (++i<L.length);
	printf("表长=%d\n列表长度=%d", L.length, L.listsize);
	ListDelete_Sq(&L, 2, &e);
	printf("被删除的元素=%d\n表长=%d\n列表长度=%d\n", e, L.length, L.listsize);
	i = 0;
	do
	{
		printf("元素%d=%d\n", i + 1, L.elem[i]);
	} while (++i<L.length);
	// 查询测试
	i = LocateElem_Sq(L, 50, equal);
	printf("位序=%d\n", i);

	// 排序测试
	InitList_Sq(&L1);
	for (i = 0;i<123;i++)
	{
		ListInsert_Sq(&L1, i + 1, i+3);
	}

	MergeList_Sq(L, L1, &L2);

	puts("排序：\n");
	for (i = 0; i < L2.length; i++)
	{
		printf("第%d个元素=%d\n", i, L2.elem[i]);
	}

	puts("按下任意键退出");
	while(!kbhit());
}


