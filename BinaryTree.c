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

typedef int TElemType;

typedef struct BTree {
	TElemType data;
	struct BTree *lchild, *rchild;
}BiTNode, *BiTree;


Status CreatBinaryTree(BiTree T)
/* 构造一个二叉树（递归定义） */
{
	TElemType ch;
	printf("输入结点");
	scanf("%d", &ch);
	if (ch == 0)
		T = NULL;
	else
	{
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch;			//生成根结点
		CreatBinaryTree(T->lchild);	//构造左子树
		CreatBinaryTree(T->rchild);	//构造右子树
	}
	return OK;
}//CreatBinaryTree


Status VistTree(TElemType e)
/* 输出结点 */
{
	printf("%d \n", e);
	return OK;
}


Status PreOrderTraverse(BiTree T, Status (*Visit)(TElemType e))
/* 先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit */
{
	if (T)
	{
		if (Visit(T->data))
			if (PreOrderTraverse(T->lchild, Visit))
				if (PreOrderTraverse(T->rchild, Visit))
					return OK;
		return ERROR;
	}
	else
		return OK;
}//PreOrderTraverse


Status CountBinaryLeaf(BiTree T, int *count)
/* 计算二叉树的叶子结点数<先序遍历> */
{
	if (T)
	{
		if ((T->lchild == NULL) && (T->rchild == NULL))
			*count++;//叶子结点数加1
		CountBinaryLeaf(T->lchild, count);
		CountBinaryLeaf(T->rchild, count);
		return OK;
	}
	else
		return ERROR;
}//CountBinaryLeaf


int BinaryTreeDepth(BiTree T)
/* 计算二叉树的深度<后序遍历> */
{
	int depth, depthleft, depthright;
	if (T == NULL)
		depth = 0;
	else
	{
		depthleft = BinaryTreeDepth(T->lchild);//计算左子树深度
		depthright = BinaryTreeDepth(T->rchild);//计算右子树深度
		depth = (depthleft >= depthright ? depthleft : depthright) + 1;
		//树的深度为左右子树中深度较大的加上1
	}
	return depth;
}


BiTree CopyBinaryTree(BiTree T)
/* 复制二叉树<后序遍历> */
{
	BiTree leftlink, rightlink, p;
	if (T == NULL)
		return NULL;
	if (T->lchild != NULL)
		leftlink = CopyBinaryTree(T->lchild);
	else
		leftlink = NULL;//得到左子树指针
	if (T->rchild != NULL)
		rightlink = CopyBinaryTree(T->rchild);
	else
		rightlink = NULL;//得到右子树指针
	p = (BiTree)malloc(sizeof(BiTNode));
	if (!p)
		exit(1);
	p->data = T->data;
	p->lchild = leftlink;
	p->rchild = rightlink;//复制结点
	return p;
}


typedef BiTree SElemType;

#define STACK_INIT_SIZE 100		//存储空间初始分配量
#define STACKINCREMENT  10		//存储空间分配增量

typedef struct {
	SElemType *base;			//在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;				//栈顶指针
	int stacksize;				//当前已分配的存储空间，以元素问单位
}SqStack;


Status InitStack(SqStack *S)
/* 构造一个空栈 */
{
	S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S->base)				//存储分配失败
		exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStack


int StackEmpty(SqStack s)
/* 判断栈是否为空 */
{
	if (s.stacksize == 0 || s.base == NULL)
		return 0;
	else
		return  1;
}



Status Push(SqStack *S, SElemType e)
/* 插入元素e为新的栈顶元素 */
{
	if (S->top - S->base >= S->stacksize)	//栈满，追加存储空间
	{
		S->base = (SElemType*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S->base)
			exit(OVERFLOW);					//存储分配失败
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return OK;
}//Push


Status Pop(SqStack *S, SElemType *e)
/* 若栈不空，则删除S的栈顶元素，用e返回其值
成功返回OK；否则返回ERROR	*/
{
	if (S->top == S->base)
		return ERROR;
	*e = *--S->top;
	return OK;
}//Pop


Status GetTop(SqStack S, SElemType *e)
/* 若栈不空则用e返回S的栈顶元素 */
{
	if (S.top == S.base)
		return ERROR;
	*e = *(S.top - 1);
	return OK;
}//InitStack


Status PreOrderTraverse1(BiTree T)
/* 先序遍历非递归实现 */
{
	SqStack S;BiTree p;
	InitStack(&S);p = T;
	while (p != NULL || StackEmpty(S))
	{
		if (p != NULL)
		{
			VistTree(p->data);
			Push(&S, p);
			p = p->lchild;
		}
		else
		{
			Pop(&S, &p);p = p->rchild;
		}
	}
	return OK;
}//PreOrderTraverse


Status MiddleTree(BiTree T)
/* 中序遍历二叉树非递归实现 */
{
	SqStack S;BiTree p;
	InitStack(&S);p = T;
	while (p != NULL || StackEmpty(S))
	{
		if (p != NULL)
		{
			Push(&S, p);
			p = p->lchild;
		}
		else
		{
			Pop(&S, &p);
			VistTree(p->data);
			p = p->rchild;
		}
	}
	return OK;
}//MiddleTree


#define MAXSIZE 100


Status LastOrderTraverse(BiTree T)
/* 非递归后序遍历 */
{
 //用tag数组标记对应的结点是否被访问过
	int sign = -1, tag[MAXSIZE];
	SqStack S;
	BiTree p, p1;
	p = T;
	InitStack(&S);
	while (p != NULL || StackEmpty(S))
	{
		if (p != NULL)
		{
			Push(&S, p);
			tag[++sign] = 0;
			p = p->lchild;
		}
		else
		{
			if (tag[sign] == 0)
			{//如果结点未被访问则取出栈顶元素，访问栈顶结点的右子树
				GetTop(S, &p);
				tag[sign] = 1;
				p = p->rchild;
			}
			else
			{//如果该结点被访问过则元素出栈输出
				Pop(&S, &p1);
				sign--;
				VistTree(p1->data);
			}
		}
	}
	return OK;
}//LastOrderTraverse



/* 测试 */
int main(void)
{
	BiTree T1 = NULL,T2;
	int count;
	CreatBinaryTree(T1);
	PreOrderTraverse(T1, VistTree);
	CountBinaryLeaf(T1, &count);
	printf("叶子结点：%d\n", count);
	count = BinaryTreeDepth(T1);
	printf("深度：%d", count);
	T2 = CopyBinaryTree(T1);
	PreOrderTraverse(T2, VistTree);
	MiddleTree(T1);
	LastOrderTraverse(T1);
	system("pause");
}