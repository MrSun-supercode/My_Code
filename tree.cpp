//头文件
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
//宏定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 10
//ADT
typedef int TElemType;
typedef int Status;
typedef struct BiTNode              //定义二叉树节点数据类型 
{
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;           //bitree为指向bitnode这种结构的指针
//基本操作
BiTree CreateTree();//按先序次序输入二叉树中结点的值（一个字符）空格字符表示空数
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//先序递归遍历二叉树T,对每个结点调用函数VIsit一次且仅一次
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//中序递归。。。
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//后序递归。。。
Status PreOrderTraverse2(BiTree T, Status(*Visit)(TElemType e));//先序遍历非递归
Status InOrderTraverse2(BiTree T, Status(*Visit)(TElemType e));//中序遍历非递归
Status PostOrderTraverse2(BiTree T, Status(*Visit)(TElemType e));//后序遍历非递归
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//层序遍历二叉树(借助于队列)
Status LevelOrderTraverse(BiTree T);// 二叉树的层序遍历(数组实现)
Status Deepth(BiTree T);//求树的高度
Status PreorderPrintLeaves(BiTree BT);//先序输出树的结点


BiTree CreateTree()//二叉树的建立
{
	BiTree T;
	TElemType item;
	scanf("%d", &item);
	if (item == 0)              //叶节点数据标志：其后根两个0 
		T = NULL;            //若某一节点为叶子结点，则其左右子树均为NULL，0表示建空树
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = item;
		T->lchild = CreateTree();             //递归创建其左子树 
		T->rchild = CreateTree();            //递归创建其右子树 
	}
	return T;                              //返回根节点 
}

Status PrintElement(TElemType e)//应用函数具体实现
{
	printf("%d ", e);
	return OK;
}

Status PreOrderTraverse1(BiTree T, Status(*Visit)(TElemType e))//先序遍历递归
{
	if (T)
	{
		if (Visit(T->data))
			if (PreOrderTraverse1(T->lchild, Visit))
				if (PreOrderTraverse1(T->rchild, Visit))
					return OK;
		return ERROR;
	}
	else return OK;
}

Status InOrderTraverse1(BiTree T, Status(*Visit)(TElemType e))//中序遍历递归
{
	if (T)
	{
		if (PreOrderTraverse1(T->lchild, Visit))
			if (Visit(T->data))
				if (PreOrderTraverse1(T->rchild, Visit))
					return OK;
		return ERROR;
	}
	else return OK;
}

Status PostOrderTraverse1(BiTree T, Status(*Visit)(TElemType e))//后序遍历递归
{
	if (T)
	{
		if (PreOrderTraverse1(T->lchild, Visit))
			if (PreOrderTraverse1(T->rchild, Visit))
				if (Visit(T->data))
					return OK;
		return ERROR;
	}
	else return OK;
}


Status PreOrderTraverse2(BiTree T, Status(*Visit)(TElemType e))//先序遍历非递归
{	
	BiTree P = T;
	stack<BiTree>S;
	while (P!=NULL||!S.empty())
	{
		while (P!=NULL)
		{
			Visit(P->data);
			S.push(P);
			P = P->lchild;
		}	
	if (!S.empty())
	{
		P=S.top();
		S.pop();
		P = P->rchild;
	}
	}
	return OK;
}

Status InOrderTraverse2(BiTree T, Status(*Visit)(TElemType e))//中序遍历非递归
{
	stack<BiTree>S;
	BiTree P = T;
	while (P!=NULL||!S.empty())
	{
		while (P!=NULL)
		{
			S.push(P);
			P = P->lchild;			
		}
		if (!S.empty())
		{
			P = S.top();
			S.pop();
			Visit(P->data);		
			P=P->rchild;
		}
	}
	return OK;
}

Status PostOrderTraverse2(BiTree T, Status(*Visit)(TElemType e))//后序遍历非递归
{
	stack<BiTree>S;
	BiTNode *cur;//当前结点
	BiTNode *ptr=NULL;//之前访问的结点
	S.push(T);
	while (!S.empty())
	{
		cur = S.top();
		if ((cur->lchild==NULL&&cur->rchild==NULL)||(ptr!=NULL&&(ptr==cur->lchild||ptr==cur->rchild)))
		{
			Visit(cur->data);
			S.pop();
			ptr = cur;
		}
		else {
			if (cur->rchild!=NULL)
			{
				S.push(cur->rchild);
			}
			if (cur->lchild!=NULL)
			{
				S.push(cur->lchild);
			}
		}
	}
	return OK;
}

Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e))//层序遍历二叉树(借助于队列)
{
	queue<BiTree>Q;
	BiTree P = T;
	Q.push(P);
	while (!Q.empty())
	{
		BiTree temp = Q.front();
		Q.pop();
		Visit(temp->data);		
		if (temp->lchild!=NULL)
		{
			Q.push(temp->lchild);
		}
		if (temp->rchild!=NULL)
		{
			Q.push(temp->rchild);
		}
	}
	return OK;
}

Status LevelOrderTraverse(BiTree T)// 二叉树的层序遍历(数组实现)
{
	if (T == NULL) return ERROR;

	BiTree q[MAXSIZE];//树中最大的结点数为10.
	q[0] = T;

	int front = 0;
	int rear = 1;

	while (front<rear)
	{
		printf("%d ",q[front]->data);
		if (q[front]->lchild)
		{
			q[rear] = q[front]->lchild;
			rear++;
		}
		if (q[front]->rchild)
		{
			q[rear] = q[front]->rchild;
			rear++;
		}
		front++;//最后跳出循环的条件为front=rear
		//rear为除了根节点以外所有结点的总数，front为算上根节点的所有结点总数，遍历所有结点后rear=front
	}
	return OK;
}

Status Deepth(BiTree T)//求树的高度
{
	int deepthLeft = 0;
	int deepthRight = 0;
	int deepCount = 0;
	if (T == NULL) {
		deepCount = 0;
		return deepCount;
	}	
	deepthLeft = Deepth(T->lchild);
	deepthRight = Deepth(T->rchild);
	deepCount = 1 + ((deepthLeft > deepthRight) ? deepthLeft : deepthRight);//在左子树和右子树中求最高的那棵树，总树高为其加1
	return deepCount;
}

Status PreorderPrintLeaves(BiTree BT)//先序输出树的结点
{
	if (BT == NULL)
	{
		return ERROR;
	}
	else {
		if (BT->lchild == NULL&&BT->rchild == NULL) printf("%d ", BT->data);
		PreorderPrintLeaves(BT->lchild);
		PreorderPrintLeaves(BT->rchild);
	}
	return OK;
}

int main(void)
{
	BiTree T;
	printf("请输入数据先序创建一棵二叉树:(结点为空时输入0)\n");
	T = CreateTree();               //先序创建一棵二叉树 
	printf("先序遍历结果为：\n");
	PreOrderTraverse2(T, PrintElement);
	printf("\n");
	printf("中序遍历结果为：\n");
	InOrderTraverse2(T, PrintElement);
	printf("\n");
	printf("后序遍历结果为：\n");
	PostOrderTraverse2(T, PrintElement);
	printf("\n");
	printf("层序遍历结果为：\n");
	LevelOrderTraverse(T);
	printf("\n");
	LevelOrderTraverse(T, PrintElement);
	printf("\n");
	printf("此树的高度为:\n");
	printf("%d\n", Deepth(T));
	printf("其树结点为:(先序)\n");
	PreorderPrintLeaves(T);
	printf("\n");
	return 0;
}
