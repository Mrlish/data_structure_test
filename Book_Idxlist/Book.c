#include "HString.h"
#include "List_L.h"
#include <string.h>


#define MaxBookNum	1000	//假设只对1000本书建索引表
#define MaxKeyNum	2500	//索引表的最大容量
#define MaxLineLen	500		//书目串的最大长度
#define MaxWordNum	10		//词表的最大容量


typedef struct {
	char *item[MaxWordNum];	//字符串的数组
	int last;				//词表的长度
}WordListType;				//词表类型(顺序表)

typedef struct {
	HString key;		//关键词
	LinkList bnolist;	//存放书号索引的链表
}IdxTermType;			//索引项类型

typedef struct {
	IdxTermType item[MaxKeyNum + 1];
	int last;
}IdxListType;			//索引表类型(有序表)

char *buf ;				//书目串缓冲区
WordListType wdlist;	//词表


void GetWord(int i, HString *wd)
/* 用wd返回词表wdlist中第i个关键词 */
{
	char *p = *(wdlist.item + i);	//取词表的第i个字符串
	StrAssign(wd, p);				//生成关键字字符串
}//GetWord


int Locate(IdxListType *idxlist, HString wd, Status *b)
/* 在索引表中查询是否存在与wd相等的关键词。
	若存在，返回其在索引表中的文字，b取值TURE
	若不存在，返回插入位置，且b取值FALSE */
{
	int i,m;
	for (i = idxlist->last - 1;
		m = StrCompare(idxlist->item[i].key, wd) > 0;
		--i);
	if (m == 0)				//找到
	{
		b = TRUE;
		return i;
	}
	else
	{
		b = FALSE;
		return i + 1;
	}
}//Locate


void InsertNewKet(IdxListType *idxlist, int i, HString wd)
/* 在索引表idxlist的第i项上插入新关键词wd，并初始化书号索引的链表为空表 */
{
	int j;
	LinkList p,q;
	for (j = idxlist->last - 1; j >= i;--j)			//后移索引项
		idxlist->item[j + 1] = idxlist->item[j];
	//插入新的索引项
	StrAssign(&idxlist->item[i].key, wd.ch);		//串赋值
	
	//清空书号索引表
	p = idxlist->item[i].bnolist->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(idxlist->item[i].bnolist);
	++idxlist->last;
}//InsertNewKet


Status InserBook(IdxListType *idxlist, int i, int bno)
/* 在索引表idxlist的第i项中插入书号为bno的索引 */
{
	ListInser_L(idxlist->item[i].bnolist, 1, bno);
	return OK;
}//InserBook

Status InsIdxList(IdxListType *idxlist, ElemType bno)
/* 将书号为bno的书名关键词按词典顺序插入索引表idxlist */
{
	int i,j;
	Status b;
	HString wd;
	for (i = 0;i < wdlist.last;++i)
	{
		GetWord(i, &wd);
		j = Locate(idxlist, wd, b);
		if (!b)
			InsertNewKet(idxlist, j, wd);
		if (!InserBook(idxlist, j, bno))
			return OVERFLOW;
	}
	return OK;
}//InsIdxList


void InitIdxList(IdxListType *idxlist)
{
	idxlist->item[0].key.ch = NULL;
	idxlist->item[0].key.length = 0;
	idxlist->item[0].bnolist = (LinkList)malloc(sizeof(LNode));
	idxlist->item[0].bnolist->next = NULL;
	idxlist->last = 0;
}


int main()
{
	FILE *f, *g;
	char c,*p;
	IdxListType idxlist;
	int BookNo;
	buf = (char*)malloc(MaxLineLen);
	if(f = fopen("BookInfo.txt","r"))
		if (g = fopen("BookIdx.txt", "w"))
		{
			InitIdxList(&idxlist);
			while (!feof(f))
			{
				p = buf;
				do						//从文件f读入一个书目信息到buf
				{
					c = fgetc(f);
					*p = c;
					p++;
				} while (c != '\n');
				ExtractKeyWord(BookNo);//从buf提取关键词到词表，书号存入BookNo
				InsIdxList(&idxlist, BookNo);
			}
			PutText(g, idxlist);		//将生成的索引表idxlist输出到文件g
		}
	system("pause");
}