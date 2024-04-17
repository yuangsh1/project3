#define	_CRT_SECURE_NO_WARNINGS 1

#include <cstdio>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
//哈希表查找
#define Nullkey -12345
//链表结点
typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, * LinkList;
//哈希表
typedef struct hashbiao
{
	LinkList list;
	int count;
}hashbiao;
//初始化哈希表
void Inithashbiao(hashbiao* H, int m)
{
	H->list = new LNode[m];
	H->count = 0;
	int i;
	for (i = 0; i < m; i++)
	{
		H->list[i].data = Nullkey;
		H->list[i].next = NULL;
	}
}
//定义哈希函数
int Hash(int key, int m)
{
	return key % m;
}
//插入关键字
void CharuKey(hashbiao* H, int key, int m)
{
	int address = Hash(key, m);
	if (H->list[address].data == Nullkey)
	{
		H->list[address].data = key;
	}
	else
	{
		LNode* s;
		s = new LNode;
		s->data = key;
		s->next= H->list[address].next;
		H->list[address].next=s;
		/*LNode* cur = H->list[address].next;
		if (cur == NULL)
		{
			H->list[address].next = s;
			s->next = NULL;
		}
		else
		{
			while (cur->next)
			{
				cur = cur->next;
			}
			s->next = cur->next;
			cur->next = s;
		}*/
	}

}
//查找关键字
LNode* ChaZhao(hashbiao H, int key, int m)
{
	int address = Hash(key, m);
	LNode* p = &H.list[address];
	while (p != NULL && p->data != key)
	{
		p = p->next;
	}
	return p;
}
//通过散列地址查找关键字
void ChazhaoKey(hashbiao H, int n, int m)
{
	LNode* p = &H.list[n];
	if (H.list[n].data == Nullkey)
		cout << -1;
	else {
		while (p != NULL)
		{
			cout << p->data << ' ';
			p = p->next;
		}
	}
}
//哈希表查找函数结束
 
//二叉排序树查找
//二叉树
typedef struct BiNode
{
	int key;
	struct BiNode* lcd, * rcd;//左右结点
}BiNode, * BiTree;
//初始化
void InitBT(BiTree& T)
{
	T = NULL;
}
//插入结点
void InsertB(BiTree& T, int key)
{
	BiTree s;
	if (T == NULL)
	{
		s = new BiNode;
		s->key = key;
		s->lcd = NULL;
		s->rcd = NULL;
		T = s;
	}
	else
	{
		if (key < T->key)
			InsertB(T->lcd, key);
		else if (key > T->key)
			InsertB(T->rcd, key);
	}
}
//创建二叉排序树
void CreatT(BiTree& T, int array[], int n)
{
	int key;
	T = NULL;
	for (int i = 0; i < n; ++i)
	{
		InsertB(T, array[i]);
	}
}
//二叉排序树的查找
BiNode* SearchT(BiTree T, int key)
{
	if (!T)
		return NULL;
	else
	{
		if (T->key == key)
			return T;
		else
		{
			if (key < T->key)
			{
				return SearchT(T->lcd, key);
			}
			else if (key > T->key)
			{
				return 	SearchT(T->rcd, key);
			}
		}
	}
}
//二叉排序树查找函数结束

//折半查找
//冒泡排序
void MaoPaopx(int n, int array[])
{
	int i = 0, j, t;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}
}
//折半查找
int Zhebanchazhao(int n, int array[], int a)
{
	int low, mid, high;
	low = 0;
	high = n - 1;
	int x = 1;
	while (low <= high)
	{
		mid = (high + low) / 2;
		if (a == array[mid])
			return mid + 1;
		else
		{
			if (a < array[mid])
			{
				high = mid - 1;
			}
			else if (a > array[mid])
			{
				low = mid + 1;
			}
		}
		x++;
	}
	return -1;
}
//折半查找函数结束

//顺序查找
int Shunxuchazhao(int array[], int n, int j)
{
	int i = 0;
	while (i < j)
	{
		if (n == array[i])
		{
			return i + 1;
		}
		else
		{
			i++;
		}
	}
	return -1;
}
//顺序查找函数结束

// 使用顺序查找，查找1万个数所用时间
int SequentialSTime1(int* a)
{
	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		Shunxuchazhao(a, i, 10000);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用折半查找，查找1万个数所用时间
int BinarySTime1(int* a)
{
	// 要进行折半查找，要先排序，排序不能算折半查找的时间
	int s[10000] = { 0 };
	for (int i = 0; i < 10000; ++i)
	{
		s[i] = a[i];
	}
	MaoPaopx(10000, s);

	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		Zhebanchazhao(10000, s, i);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用二叉排序树查找，查找1万个数所用时间
int BSTreeTime1(int* a)
{
	// 先建一个二叉排序树
	BiTree T;
	CreatT(T, a, 10000);

	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		SearchT(T, i);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用哈希查找，查找1万个数所用时间
int HashTime1(int* a)
{
	// 先建一个哈希表
	hashbiao H;
	Inithashbiao(&H, 1000);
	for (int i = 0; i <= 10000; ++i)
	{
		CharuKey(&H, a[i], 1000);
	}

	int begin = clock();
	for (int i = 1; i <= 10000; ++i)
	{
		ChaZhao(H, i, 1000);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用折半查找，查找100万个数所用时间
int BinarySTime2(int* a)
{
	// 要进行折半查找，要先排序，排序不能算折半查找的时间
	int s[10000] = { 0 };
	for (int i = 0; i < 10000; ++i)
	{
		s[i] = a[i];
	}
	MaoPaopx(10000, s);

	int begin = clock();
	for (int i = 1; i <= 1000000; ++i)
	{
		Zhebanchazhao(10000, s, i);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用二叉排序树查找，查找100万个数所用时间
int BSTreeTime2(int* a)
{
	// 先建一个二叉排序树
	BiTree T;
	CreatT(T, a, 10000);

	int begin = clock();
	for (int i = 1; i <= 1000000; ++i)
	{
		SearchT(T, i);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

// 使用哈希查找，查找100万个数所用时间
int HashTime2(int* a)
{
	// 先建一个哈希表
	hashbiao H;
	Inithashbiao(&H, 100000);
	for (int i = 0; i <= 10000; ++i)
	{
		CharuKey(&H, a[i], 100000);
	}

	int begin = clock();
	for (int i = 1; i <= 1000000; ++i)
	{
		ChaZhao(H, i, 100000);
	}
	int end = clock();
	int t = end - begin;

	return t;
}

void CompareTime(int* a)
{
	int t1_1 = SequentialSTime1(a);
	int t1_2 = BinarySTime1(a);
	int t1_3 = BSTreeTime1(a);
	 int t1_4 = HashTime1(a);

	cout << "第一次使用四种查找算法查找1万个数测试" << endl;
	cout << "使用顺序查找1万个数所需时间: " << t1_1 << endl;
	cout << "使用折半查找1万个数所需时间: " << t1_2 << endl;
	cout << "使用二叉排序树查找1万个数所需时间: " << t1_3 << endl;
	cout << "使用哈希表查找1万个数所需时间: " << t1_4 << endl;
	cout << endl;

	cout << "第二次使用除顺序查找以外的查找算法查找10万个数测试" << endl;
	int t2_2 = BinarySTime2(a);
	int t2_3 = BSTreeTime2(a);
	int t2_4 = HashTime2(a);

	cout << "使用折半查找10万个数所需时间: " << t2_2 << endl;
	cout << "使用二叉排序树查找10万个数所需时间: " << t2_3 << endl;
	cout << "使用哈希表查找10万个数所需时间: " << t2_4 << endl;
	cout << endl;
}

// 查找菜单
void menu()
{
	cout << "**************************************************" << endl;
	cout << "******** 1.顺序查找        2.折半查找     ********" << endl;
	cout << "******** 3.二叉排序树查找  4.哈希查找     ********" << endl;
	cout << "************  5.比较查找算法执行时间  ************" << endl;
	cout << "******************  0.退出  **********************" << endl;
	cout << "**************************************************" << endl;
}

int main()
{
	// 随机数发生器初始化
	srand((unsigned int)time(nullptr));
	int n = 10000;
	int randarr[10000] = { 0 };
	// 随机生成查找数据
	for (int i = 0; i < n; ++i)
	{
		// rand() + i 使重复数据变少
		randarr[i] = (rand() + i) % 10000;
	}

	int input = 0;

	do
	{
		// 调用菜单
		menu();
		cout << "请选择要使用的查找算法>:";
		cin >> input;
		// 根据输入的数，执行不同的操作
		switch (input)
		{
		case 1:
		{
			int a[10000], n, i = 0, j;
			cout << "请输入待查数据个数" << endl;
			cin >> n;
			cout << "请输入待查数据" << endl;
			for (i = 0; i < n; i++)
			{
				scanf_s("%d", &a[i]);
			}
			cout << "请输入要查找的数" << endl;
			cin >> j;
			cout << "该数位置为：";
			cout << Shunxuchazhao(a, j,n)<<endl;
		}
			break;
		case 2:
		{
			int i, a[10000], b, j, k;
			cout << "请输入待查数据个数" << endl;
			scanf_s("%d", &i);
			cout << "请输入待查数据" << endl;
			for (j = 0; j < i; j++)
			{
				scanf_s("%d", &a[j]);
			}
			cout << "请输入要查找的数据" << endl;
			cin >> b;
			MaoPaopx(i, a);
			cout << "该数据的位置为：";
			k = Zhebanchazhao(i, a, b);
			cout << k<<endl;
		}
			break;
		case 3:
		{
			int i = 1, n, a[10000];
			int c;
			cout << "请输入待查数据个数" << endl;
			scanf_s("%d", &i);
			BiTree T;
			cout << "请输入待查数据"<<endl;
			for (int j = 0; j < i; ++j)
			{
				scanf_s("%d", &a[j]);
			}
			CreatT(T, a, i);
			cout << "请输入要查找的数"<<endl;
			cin >> c;
			SearchT(T, c);
			cout << "该数的指针";
			cout << SearchT(T, c) << endl;
		}
			break;
		case 4:
		{
			hashbiao H;
			int a[10000], m, n, i = 0, j = 0, k = 0;
			cout << "输入待查数据个数" << endl;
			cin >> n;
			cout << "输入待查数据" << endl;
			for (i = 0; i < n; i++)
				cin >> a[i];
			cout << "输入哈希函数中的除数" << endl;
			cin >> m;
			Inithashbiao(&H, m);
			for (k = 0; k <= i; k++)
			{
				CharuKey(&H, a[k], m);
			}
			cout << "输入要查找的数据" << endl;
			cin >> j;
			cout << "要查找的数据的地址为：";
			cout << ChaZhao(H, j, m) << endl;
		}
			break;
		case 5:
			CompareTime(randarr);
			break;
		case 0:
			cout << "退出" << endl;
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
		}
	} while (input);


	return 0;
}