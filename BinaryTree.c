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


/* 测试 */
int main(void)
{
	BiTree T1 , T2;
	int count;
	CreatBinaryTree(T1);
	PreOrderTraverse(T1, VistTree);
	CountBinaryLeaf(T1, &count);
	printf("叶子结点：%d\n", count);
	count = BinaryTreeDepth(T1);
	printf("深度：%d", count);
	T2 = CopyBinaryTree(T1);
	PreOrderTraverse(T2, VistTree);
	system("pause");
}