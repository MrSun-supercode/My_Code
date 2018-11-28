//ͷ�ļ�
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
//�궨��
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 10
//ADT
typedef int TElemType;
typedef int Status;
typedef struct BiTNode              //����������ڵ��������� 
{
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;           //bitreeΪָ��bitnode���ֽṹ��ָ��
//��������
BiTree CreateTree();//�������������������н���ֵ��һ���ַ����ո��ַ���ʾ����
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//����ݹ����������T,��ÿ�������ú���VIsitһ���ҽ�һ��
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//����ݹ顣����
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//����ݹ顣����
Status PreOrderTraverse2(BiTree T, Status(*Visit)(TElemType e));//��������ǵݹ�
Status InOrderTraverse2(BiTree T, Status(*Visit)(TElemType e));//��������ǵݹ�
Status PostOrderTraverse2(BiTree T, Status(*Visit)(TElemType e));//��������ǵݹ�
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e));//�������������(�����ڶ���)
Status LevelOrderTraverse(BiTree T);// �������Ĳ������(����ʵ��)
Status Deepth(BiTree T);//�����ĸ߶�
Status PreorderPrintLeaves(BiTree BT);//����������Ľ��


BiTree CreateTree()//�������Ľ���
{
	BiTree T;
	TElemType item;
	scanf("%d", &item);
	if (item == 0)              //Ҷ�ڵ����ݱ�־����������0 
		T = NULL;            //��ĳһ�ڵ�ΪҶ�ӽ�㣬��������������ΪNULL��0��ʾ������
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = item;
		T->lchild = CreateTree();             //�ݹ鴴���������� 
		T->rchild = CreateTree();            //�ݹ鴴���������� 
	}
	return T;                              //���ظ��ڵ� 
}

Status PrintElement(TElemType e)//Ӧ�ú�������ʵ��
{
	printf("%d ", e);
	return OK;
}

Status PreOrderTraverse1(BiTree T, Status(*Visit)(TElemType e))//��������ݹ�
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

Status InOrderTraverse1(BiTree T, Status(*Visit)(TElemType e))//��������ݹ�
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

Status PostOrderTraverse1(BiTree T, Status(*Visit)(TElemType e))//��������ݹ�
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


Status PreOrderTraverse2(BiTree T, Status(*Visit)(TElemType e))//��������ǵݹ�
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

Status InOrderTraverse2(BiTree T, Status(*Visit)(TElemType e))//��������ǵݹ�
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

Status PostOrderTraverse2(BiTree T, Status(*Visit)(TElemType e))//��������ǵݹ�
{
	stack<BiTree>S;
	BiTNode *cur;//��ǰ���
	BiTNode *ptr=NULL;//֮ǰ���ʵĽ��
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

Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e))//�������������(�����ڶ���)
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

Status LevelOrderTraverse(BiTree T)// �������Ĳ������(����ʵ��)
{
	if (T == NULL) return ERROR;

	BiTree q[MAXSIZE];//�������Ľ����Ϊ10.
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
		front++;//�������ѭ��������Ϊfront=rear
		//rearΪ���˸��ڵ��������н���������frontΪ���ϸ��ڵ�����н���������������н���rear=front
	}
	return OK;
}

Status Deepth(BiTree T)//�����ĸ߶�
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
	deepCount = 1 + ((deepthLeft > deepthRight) ? deepthLeft : deepthRight);//����������������������ߵ��ǿ�����������Ϊ���1
	return deepCount;
}

Status PreorderPrintLeaves(BiTree BT)//����������Ľ��
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
	printf("�������������򴴽�һ�ö�����:(���Ϊ��ʱ����0)\n");
	T = CreateTree();               //���򴴽�һ�ö����� 
	printf("����������Ϊ��\n");
	PreOrderTraverse2(T, PrintElement);
	printf("\n");
	printf("����������Ϊ��\n");
	InOrderTraverse2(T, PrintElement);
	printf("\n");
	printf("����������Ϊ��\n");
	PostOrderTraverse2(T, PrintElement);
	printf("\n");
	printf("����������Ϊ��\n");
	LevelOrderTraverse(T);
	printf("\n");
	LevelOrderTraverse(T, PrintElement);
	printf("\n");
	printf("�����ĸ߶�Ϊ:\n");
	printf("%d\n", Deepth(T));
	printf("�������Ϊ:(����)\n");
	PreorderPrintLeaves(T);
	printf("\n");
	return 0;
}