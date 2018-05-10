#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;//哈夫曼树结点的定义
typedef char* *HuffmanCode;//定义字符型二维间址


int b_max(int *buf, int n)
{
	int max = buf[0];
	for (int inx = 0; inx != n; ++inx) 
	{
		if (buf[inx]> max) 
			max = buf[inx];
	}
	return max;
}


void CreatHuffmanTree(HuffmanTree HT, int *w, int n)
/* 构造哈夫曼树 w中存放的是n个叶子结点的权值*/
{
	int i, j, min1, min2, minl, minr;
	HT = (HuffmanTree)malloc((2 * n - 1) * sizeof(HTNode));
	if (!HT)
		exit(1);
	for (i = 0;i<n;i++)
		HT[i].weight = w[i];		//HT前n个结点为叶子结点
	for (i = n;i<2 * n - 1;i++)
		HT[i].weight = 0;			//初始化剩余结点
	for (i = 0;i<2 * n - 1;i++)		//初始化
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
	}
	for (i = n;i<2 * n - 1;i++)
	{
		min1 = min2 = b_max(w, n);
		for (j = 0;j<i;j++)			//找到第一个最小的数
		{
			if (HT[j].parent == -1)
			{
				if (HT[j].weight<min1) { min1 = HT[j].weight;minl = j; }
			}
		}
		HT[minl].parent = i;
		for (j = 0;j<i;j++)			//找到第二个最小的数
		{
			if (HT[j].parent == -1)
			{
				if (HT[j].weight<min2) { min2 = HT[j].weight;  minr = j; }
			}
		}
		HT[minr].parent = i;
		HT[i].weight = HT[minl].weight + HT[minr].weight;
		HT[i].lchild = minl;
		HT[i].rchild = minr;		//建立树关系
	}
}//CreatHuffmanTree


void HuffmanTreeCode(HuffmanTree HT, HuffmanCode HC, int n)
/* 从叶子结点到根结点逆向求哈夫曼编码 */
{
	char *cd;int i, j, start, f;
	cd = (char *)malloc(n * sizeof(char));			//分配n个字符编码的头指针向量
	HC = (HuffmanCode)malloc(n * sizeof(char*));	//分配求编码的工作空间
		cd[n - 1] = '\0';							//编码结束符
	for (i = 0;i<n;i++)								//住个字符求哈夫曼编码
	{
		start = n - 1;								//编码接受符位置
		for (j = i, f = HT[j].parent;f != -1;j = f, f = HT[f].parent)
		{											//叶子到跟逆向求编码
			if (HT[f].lchild == j)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char *)malloc((n - start) * sizeof(char));//为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);					//从cd复制编码到HC
	}
	free(cd);										//释放操作空间
}//HuffmanTreeCode

