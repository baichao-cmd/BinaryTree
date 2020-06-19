#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#define Maxsize 100
#include <stack>
#include <queue>
#include <list>

template<typename DataType>
class BTNode
{
public:
	BTNode() : LChild(NULL), RChild(NULL) {};
	BTNode(DataType data_temp) : LChild(NULL), RChild(NULL),data(data_temp) {};
	DataType data;
	BTNode<DataType> *LChild, *RChild;
};

template<typename DataType>
class BinaryTree
{
public:
	void CreateBinaryTree(BTNode<DataType> *&root, DataType *ch);  //创建二叉树
	void PreOrder(BTNode<DataType> *root);	//前序非递归遍历
	void InOrder(BTNode<DataType> *root);	//中序非递归遍历
	void PostOrder(BTNode<DataType> *root); //后续非递归遍历
	void LevelOrder(BTNode<DataType> *root);//层序遍历
	BTNode<DataType>* GetBTNode(BTNode<DataType> *root, const DataType x);//查找值为x的节点
	unsigned int TreeHigh(BTNode<DataType> *root);//求二叉树高度
	void TreeOut(BTNode<DataType> *root);//输出二叉树(格式为括号匹配的字符串)
	//已知先序遍历和中序遍历，求后序遍历结果
	BTNode<DataType>* GetPost(DataType *ch1, DataType *ch2, int len);
	//已知中序遍历和后序遍历，求前序遍历结果
	BTNode<DataType>* GetPre(DataType *ch2, DataType *ch3, int len);
	//求先序递归遍历的第k个节点的值	
	void PreOrder_k(BTNode<DataType> *root, int k, DataType &data);
	//求先序非递归遍历的第k个节点的值
	DataType PreOrder1_k(BTNode<DataType> *root, int k);
	//求中序递归遍历的第k个节点的值
	void InOrder_k(BTNode<DataType> *root, int k, DataType &data);
	//求中序非递归遍历的第k个节点的值
	DataType InOrder1_k(BTNode<DataType> *root, int k);
	//求后序递归遍历的第k个节点的值
	void PostOrder_k(BTNode<DataType> *root, int k, DataType &data);
	//求后序非递归遍历的第k个节点的值	
	DataType PostOrder1_k(BTNode<DataType> *root, int k);
	//求二叉树的所有节点数（即求总数）
	int AllNodeNum(BTNode<DataType> *root);
	//求二叉树的所有叶子节点个数
	int AllLeafNodeNum(BTNode<DataType> *root);
	//求二叉树的所有双分支节点个数
	int ALLTwoNodeNum(BTNode<DataType> *root);
	//求其中最小值的节点值
	DataType MinNode(BTNode<DataType> *root);
	//删除二叉树，并释放所有节点
	void DeleteBinaryTree(BTNode<DataType> *&root);
	//将二叉树的左右子树进行交换，不能破坏原二叉树
	void ExchangeChildTree(BTNode<DataType> *&root);
	//求二叉树中值为x的结点层号
	int GetDataXLevel(BTNode<DataType> *root, DataType x, int h = 1);
	//求二叉树的宽度并输出各节点的层次
	int GetBinaryTreeWidth(BTNode<DataType> *root);
	//求指定的某一层的叶子节点个数
	int GetLevelLeafNodeNum(BTNode<DataType> *root, int level_num);
	//判断二叉树是否完全二叉树
	bool IsCompleteBinaryTree(BTNode<DataType> *root);
	//输出每个叶子节点到根节点的逆路径
	void OutLeafNode_Root(BTNode<DataType> *root, DataType x);
	//输出二叉树中第一条最长的路径长度，并输出此路径上各节点的值
	void FirstLongRoute(BTNode<DataType> *root);
	//求包含r和s两个节点的最小子树
	BTNode<DataType> *IncludeRSTree(BTNode<DataType>* root, BTNode<DataType> *r, BTNode<DataType> *s);
	//输出从根节点到p所指节点之间的路径
	void Putroot_pRoute(BTNode<DataType> *root, BTNode<DataType> *q);
};
#if 1
template<typename DataType>
void BinaryTree<DataType>::CreateBinaryTree(BTNode<DataType> *&root, DataType *ch)
{
	BTNode<DataType> *sta[Maxsize];
	int top = -1;
	int i = 0, m = 0;
	BTNode<DataType> *temp = NULL;
	root = NULL;
	while (*(ch + i) != '\0')
	{
		switch (*(ch + i))
		{
		case'(':
			m = 1;
			break;
		case',':
			top--;
			m = 2;
			break;
		case')':
			top--;
			break;
		default:
			temp = new BTNode<DataType>;
			temp->data = *(ch + i);
			if (root == NULL)
			{
				root = temp;
				top++;
				sta[top] = temp;
			}
			else
			{
				if (m == 1)
				{
					sta[top]->LChild = temp;
					top++;
					sta[top] = temp;
				}
				else if (m == 2)
				{
					sta[top]->RChild = temp;
					top++;
					sta[top] = temp;
				}
			}
		}
		i++;
	}
}

template<typename DataType>
void BinaryTree<DataType>::PreOrder(BTNode<DataType> *root)
{
	stack<BTNode<DataType> *> sta;
	BTNode<DataType> *p = root;
	while (p != NULL || !sta.empty())
	{
		while (p != NULL)
		{
			cout << p->data << " ";
			sta.push(p);
			p = p->LChild;
		}
		if (!sta.empty())
		{
			p = sta.top();
			sta.pop();
			p = p->RChild;
		}
	}
	cout << endl;
}

template<typename DataType>
void BinaryTree<DataType>::InOrder(BTNode<DataType> *root)
{
	stack<BTNode<DataType> *> sta;
	BTNode<DataType> *p = root;
	while (p != NULL || !sta.empty())
	{
		while (p != NULL)
		{
			sta.push(p);
			p = p->LChild;
		}
		if (!sta.empty())
		{
			p = sta.top();
			cout << p->data << " ";
			sta.pop();
			p = p->RChild;
		}
	}
	cout << endl;
}

template<typename DataType>
void BinaryTree<DataType>::PostOrder(BTNode<DataType> *root)
{
	/*先把当前节点入栈，然后要判断当前节点是否可以弹栈，
	若当前节点无子树或者子树已经遍历完毕，则可弹栈*/
	stack<BTNode<DataType>*> sta;
	BTNode<DataType> *p, *old = NULL;
	sta.push(root);
	while (!sta.empty())
	{
		p = sta.top();
		if ((p->LChild == NULL && p->RChild == NULL) ||
			(old != NULL && (old == p->LChild || old == p->RChild)))
		{
			cout << p->data << " ";
			old = p;
			sta.pop();
		}
		else
		{
			if (p->RChild)
			{
				sta.push(p->RChild);
			}
			if (p->LChild)
			{
				sta.push(p->LChild);
			}
		}
	}
	cout << endl;
}

template<typename DataType>
inline void BinaryTree<DataType>::LevelOrder(BTNode<DataType>* root)
{
	queue<BTNode<DataType> *> que;
	BTNode<DataType> *p;
	que.push(root);
	while (!que.empty())
	{
		p = que.front();
		cout << p->data << " ";
		que.pop();
		if (p->LChild)
		{
			que.push(p->LChild);
		}
		if (p->RChild)
		{
			que.push(p->RChild);
		}
	}
	cout << endl;
}

template<typename DataType>
BTNode<DataType>* BinaryTree<DataType>::GetBTNode(BTNode<DataType> *root, DataType x)
{
	stack<BTNode<DataType>*> sta;
	BTNode<DataType> *p = root;
	while (p || !sta.empty())
	{
		while (p)
		{
			if (p->data == x)
			{
				return p;
			}
			sta.push(p);
			p = p->LChild;
		}
		if (!sta.empty())
		{
			p = sta.top();
			sta.pop();
			p = p->RChild;
		}
	}
	return NULL;
}

int mHigh = 0, nHigh = 0;
template<typename DataType>
unsigned int BinaryTree<DataType>::TreeHigh(BTNode<DataType> *root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->LChild)
	{
		mHigh++;
		TreeHigh(root->LChild);
	}
	if (root->RChild)
	{
		nHigh++;
		TreeHigh(root->RChild);
	}
	return mHigh > nHigh ? mHigh : nHigh;
}

template<typename DataType>
void BinaryTree<DataType>::TreeOut(BTNode<DataType> *root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		cout << root->data;
		if (root->LChild)
		{
			cout << "(";
			TreeOut(root->LChild);
			cout << ",";
		}
		if (root->RChild)
		{
			TreeOut(root->RChild);
			cout << ")";
		}
	}
}

template<typename DataType>
BTNode<DataType> *BinaryTree<DataType>::GetPost(DataType *ch1, DataType *ch2, int len)
{
	BTNode<DataType> *root = NULL, *temp = NULL;
	int i = 0;
	if (len <= 0)
	{
		return NULL;
	}
	temp = new BTNode<DataType>;
	temp->data = *(ch1 + 0);
	root = temp;
	temp = NULL;
	for (; i < len; ++i)
	{
		if (*(ch1 + 0) == *(ch2 + i))
		{
			break;
		}
	}
	root->LChild = GetPost(ch1 + 1, ch2, i);
	root->RChild = GetPost(ch1 + i + 1, ch2 + i + 1, len - i - 1);
	return root;
}

template<typename DataType>
BTNode<DataType> *BinaryTree<DataType>::GetPre(DataType *ch2, DataType *ch3, int len)
{
	BTNode<DataType> *root = NULL, *temp = NULL;
	int i = 0;
	if (len <= 0)
	{
		return NULL;
	}
	temp = new BTNode<DataType>;
	temp->data = *(ch3 + len - 1);
	root = temp;
	temp = NULL;
	for (; i < len; ++i)
	{
		if (*(ch3 + len - 1) == *(ch2 + i))
		{
			break;
		}
	}
	root->LChild = GetPre(ch2, ch3, i);
	root->RChild = GetPre(ch2 + i + 1, ch3 + i, len - i - 1);
	return root;
}

int pk = 0;
template<typename DataType>
void BinaryTree<DataType>::PreOrder_k(BTNode<DataType> *root, int k, DataType &data)
{
	pk++;
	if (pk == k)
	{
		data = root->data;
		return;
	}
	if (root->LChild)
	{
		PreOrder_k(root->LChild, k, data);
	}
	if (root->RChild)
	{
		PreOrder_k(root->RChild, k, data);
	}
	return;
}

template<typename DataType>
DataType BinaryTree<DataType>::PreOrder1_k(BTNode<DataType> *root, int k)
{
	BTNode<DataType> *p = root;
	int m = 0;
	stack<BTNode<DataType> *> sta;
	sta.push(p);
	while (p || sta.empty())
	{
		m++;
		p = sta.top();
		if (m == k)
		{
			return p->data;
		}
		sta.pop();
		if (p->RChild)
		{
			sta.push(p->RChild);
		}
		if (p->LChild)
		{
			sta.push(p->LChild);
		}
	}
	return NULL;
}

int ik = 0;
template<typename DataType>
void BinaryTree<DataType>::InOrder_k(BTNode<DataType> *root, int k, DataType &data)
{
	if (root->LChild)
	{
		InOrder_k(root->LChild, k, data);
	}
	ik++;
	if (ik == k)
	{
		data = root->data;
	}
	if (root->RChild)
	{
		InOrder_k(root->RChild, k, data);
	}
}

template<typename DataType>
DataType BinaryTree<DataType>::InOrder1_k(BTNode<DataType> *root, int k)
{
	BTNode<DataType> *p = root;
	stack<BTNode<DataType> *> sta;
	int m = 0;
	while (p || !sta.empty())
	{
		while (p)
		{
			sta.push(p);
			p = p->LChild;
		}
		p = sta.top();
		m++;
		if (m == k)
		{
			return p->data;
		}
		sta.pop();
		if (p->RChild)
		{
			p = p->RChild;
		}
		else
		{
			p = NULL;
		}
	}
	return NULL;
}

int pok = 0;
template<typename DataType>
void BinaryTree<DataType>::PostOrder_k(BTNode<DataType> *root, int k, DataType &data)
{
	if (root->LChild)
	{
		PostOrder_k(root->LChild, k, data);
	}
	if (root->RChild)
	{
		PostOrder_k(root->RChild, k, data);
	}
	pok++;
	if (pok == k)
	{
		data = root->data;
	}
}

template<typename DataType>
DataType BinaryTree<DataType>::PostOrder1_k(BTNode<DataType> *root, int k)
{
	BTNode<DataType> *p = NULL, *old = NULL;
	stack<BTNode<DataType> *> sta;
	sta.push(root);
	int m = 0;
	while (!sta.empty())
	{
		p = sta.top();
		if ((p->LChild == NULL && p->RChild == NULL) ||
			(old != NULL) && (old == p->LChild || old == p->RChild))
		{
			m++;
			if (m == k)
			{
				return p->data;
			}
			old = p;
			sta.pop();
		}
		else
		{
			if (p->RChild)
			{
				sta.push(p->RChild);
			}
			if (p->LChild)
			{
				sta.push(p->LChild);
			}
		}
	}
	return NULL;
}

template<typename DataType>
int BinaryTree<DataType>::AllNodeNum(BTNode<DataType> *root)
{
	int num = 0;
	BTNode<DataType> *p = root, *old = NULL;
	stack<BTNode<DataType> *> sta;
	sta.push(root);
	while (!sta.empty())
	{
		p = sta.top();
		if (p->LChild == NULL && p->RChild == NULL || (old != NULL && (old == p->LChild || old == p->RChild)))
		{
			num++;
			sta.pop();
			old = p;
		}
		else
		{
			if (p->RChild)
			{
				sta.push(p->RChild);
			}
			if (p->LChild)
			{
				sta.push(p->LChild);
			}
		}
	}
	return num;
}

template<typename DataType>
int BinaryTree<DataType>::AllLeafNodeNum(BTNode<DataType> *root)
{
	int num = 0;
	BTNode<DataType> *p = root, *old = NULL;
	stack<BTNode<DataType> *> sta;
	sta.push(root);
	while (!sta.empty())
	{
		p = sta.top();
		if (p->LChild == NULL && p->RChild == NULL || old != NULL && (p->LChild == old || p->RChild == old))
		{
			if (p->LChild == NULL && p->RChild == NULL)
			{
				num++;
			}
			sta.pop();
			old = p;
		}
		else
		{
			if (p->RChild)
			{
				sta.push(p->RChild);
			}
			if (p->LChild)
			{
				sta.push(p->LChild);
			}
		}
	}
	return num;
}

template<typename DataType>
int BinaryTree<DataType>::ALLTwoNodeNum(BTNode<DataType>* root)
{
	int num = 0;
	BTNode<DataType> *p = root;
	stack<BTNode<DataType> *> sta;
	while (p != NULL || !sta.empty())
	{
		while (p)
		{
			if (p->LChild != NULL && p->RChild != NULL)
			{
				num++;
			}
			sta.push(p);
			p = p->LChild;
		}
		p = sta.top();
		sta.pop();
		if (p->RChild)
		{
			sta.push(p->RChild);
		}
		p = NULL;
	}
	return num;
}

template<typename DataType>
DataType BinaryTree<DataType>::MinNode(BTNode<DataType> *root)
{
	DataType data = root->data;
	BTNode<DataType> *p = root;
	stack<BTNode<DataType> *> sta;
	while (p != NULL || !sta.empty())
	{
		while (p)
		{
			sta.push(p);
			p = p->LChild;
		}
		p = sta.top();
		if (p->data < data)
		{
			data = p->data;
		}
		sta.pop();
		if (p->RChild)
		{
			sta.push(p->RChild);
		}
		p = NULL;
	}
	return data;
}

template<typename DataType>
void BinaryTree<DataType>::DeleteBinaryTree(BTNode<DataType> *&root)
{
	BTNode<DataType> *p = root, *old = NULL;
	stack<BTNode<DataType> *> sta;
	sta.push(root);
	while (!sta.empty())
	{
		p = sta.top();
		if (p->LChild != NULL && p->RChild != NULL || old != NULL && (old == p->LChild || old == p->RChild))
		{
			sta.pop();
			delete p;
		}
		else
		{
			if (p->RChild != NULL)
			{
				sta.push(p->RChild);
			}
			if (p->LChild != NULL)
			{
				sta.push(p->LChild);
			}
		}
	}
	root = NULL;
}

template<typename DataType>
void BinaryTree<DataType>::ExchangeChildTree(BTNode<DataType> *&root)
{
	BTNode<DataType> *temp = root->LChild;
	root->LChild = root->RChild;
	root->RChild = temp;
}

template<typename DataType>
int BinaryTree<DataType>::GetDataXLevel(BTNode<DataType> *root, DataType x, int h = 1)
{
	int h1;
	if (root == NULL)
	{
		return 0;
	}
	if (root->data == x)
	{
		return h;
	}
	else
	{
		h1 = GetDataXLevel(root->LChild, x, h + 1);
		if (h1 == 0)
		{
			h1 = GetDataXLevel(root->RChild, x, h + 1);
		}
		else
		{
			return h1;
		}
	}
}

template<typename DataType>
int BinaryTree<DataType>::GetBinaryTreeWidth(BTNode<DataType>* root)
{
	if (!root)
	{
		return 0;
	}
	BTNode<DataType> *p = root;
	queue<BTNode<DataType>*> que;
	que.push(root);
	int level_num = 0;
	int width = 1;
	int nowwidth = 1;
	int nextwidth = 0;
	while (!que.empty())
	{
		level_num++;
		cout << endl << "第" << level_num << "层：";
		while (nowwidth != 0)
		{
			p = que.front();
			cout << " " << p->data;
			que.pop();
			nowwidth--;
			if (p->LChild)
			{
				que.push(p->LChild);
				nextwidth++;
			}
			if (p->RChild)
			{
				que.push(p->RChild);
				nextwidth++;
			}
		}
		if (width < nextwidth)
		{
			width = nextwidth;
		}
		nowwidth = nextwidth;
		nextwidth = 0;
	}
	return width;
}

template<typename DataType>
int BinaryTree<DataType>::GetLevelLeafNodeNum(BTNode<DataType> *root, int level_num)
{
	BTNode<DataType> *p = NULL;
	queue<BTNode<DataType>*> que;
	que.push(root);
	int level = 0;
	int nowwidth = 1;
	int nextwidth = 0;
	int LeafNodeNum = 0;
	while (!que.empty())
	{
		level++;
		while (nowwidth != 0)
		{
			p = que.front();
			que.pop();
			if (level == level_num)
			{
				if (!p->LChild && !p->RChild)
				{
					LeafNodeNum++;
				}
			}
			nowwidth--;
			if (p->LChild)
			{
				que.push(p->LChild);
				nextwidth++;
			}
			if (p->RChild)
			{
				que.push(p->RChild);
				nextwidth++;
			}
		}
		nowwidth = nextwidth;
		nextwidth = 0;
	}
	return LeafNodeNum;
}

template<typename DataType>
void BinaryTree<DataType>::OutLeafNode_Root(BTNode<DataType> *root, DataType x)
{
	BTNode<DataType> *p = root, *old = NULL;
	stack<BTNode<DataType> *> sta;
	while (p || !sta.empty())
	{
		while (p)
		{
			sta.push(p);
			p = p->LChild;
		}
		if (!sta.empty())
		{
			p = sta.top();
			if (p->data == x)
			{
				cout << endl << "节点" << x << "到根节点的逆路径为：";
				while (!sta.empty())
				{
					p = sta.top();
					sta.pop();
					cout << " " << p->data;
				}
				cout << endl;
				return;
			}
			if (p->RChild && p->RChild != old)
			{
				p = p->RChild;
			}
			else
			{
				old = sta.top();
				sta.pop();
				p = NULL;
			}
		}
	}
}

template<typename DataType>
void BinaryTree<DataType>::FirstLongRoute(BTNode<DataType>* root)
{
	BTNode<DataType> *btn[Maxsize];
	unsigned int top = -1, len = 0;
	BTNode<DataType> *p = root, *old = NULL;
	stack<BTNode<DataType> *> sta;
	while (p || top != -1)
	{
		while (p)
		{
			top++;
			btn[top] = p;
			p = p->LChild;
		}
		len = top + 1;
		if (len > sta.size())
		{
			while (!sta.empty())
			{
				sta.pop();
			}
			for (unsigned int i = len; i > 0; --i)
			{
				sta.push(btn[i - 1]);
			}
		}
		if (top != -1)
		{
			p = btn[top];
			if (p->RChild && p->RChild != old)
			{
				p = p->RChild;
			}
			else
			{
				old = btn[top];
				top--;
				p = NULL;
			}
		}
	}
	cout << endl << "最长的路径为：";
	while (!sta.empty())
	{
		p = sta.top();
		cout << p->data;
		sta.pop();
	}
	cout << endl;
}

//求包含r和s两个节点的最小子树
template<typename DataType>
BTNode<DataType>* BinaryTree<DataType>::IncludeRSTree(BTNode<DataType>* root, BTNode<DataType> *r, BTNode<DataType> *s)
{
	BTNode<DataType> *p = root, *old = NULL;
	stack<BTNode<DataType> *> sta, rsta, ssta, temp;
	while (p || !sta.empty()) 
	{
		while (p) 
		{
			sta.push(p);
			p = p->LChild;
		}
		p = sta.top();
		if (p->LChild == NULL && p->RChild == NULL || old != NULL && p->RChild == old) 
		{
			old = sta.top();
			if (p == r || p == s)
			{
				int len = sta.size(), i = 0;
				BTNode<DataType> *data;
				for (; i < len; ++i)
				{
					data = sta.top();
					temp.push(data);
					sta.pop();
				}
				for (i = 0; i < len; ++i)
				{
					data = temp.top();
					if (p == r)
					{
						rsta.push(data);
					}
					if (p == s)
					{
						ssta.push(data);
					}
					sta.push(data);
					temp.pop();
				}
				if (rsta.size() && ssta.size())
				{
					return NULL;
				}
			}
			sta.pop();
		}
		else 
		{
			if (p->RChild) 
			{
				sta.push(p->RChild);
			}
			if (p->LChild && old != p->LChild) 
			{
				sta.push(p->LChild);
			}
		}
		p = NULL;
	}
	return NULL;
}

template<typename DataType>
void BinaryTree<DataType>::Putroot_pRoute(BTNode<DataType> *root, BTNode<DataType> *q) 
{
	BTNode<DataType> *p = root,*old = NULL;
	stack<BTNode<DataType>*> sta;
	while (p || !sta.empty()) 
	{
		while (p) 
		{
			sta.push(p);
			p = p->LChild;
		}
		p = sta.top();
		if (p->LChild == NULL && p->RChild == NULL || old && (old == p->RChild)) 
		{
			if (p == q) 
			{
				/*省略输出栈中路径*/
				return;
			}
			old = p;
			sta.pop();
			p = NULL;
		}
		else 
		{
			if (p->RChild) 
			{
				p = p->RChild;
			}
		}
	}
}
#endif

#endif

