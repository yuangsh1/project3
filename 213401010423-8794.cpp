#define	_CRT_SECURE_NO_WARNINGS 1

#include <cstdio>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
//��ϣ�����
#define Nullkey -12345
//������
typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, * LinkList;
//��ϣ��
typedef struct hashbiao
{
	LinkList list;
	int count;
}hashbiao;
//��ʼ����ϣ��
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
//�����ϣ����
int Hash(int key, int m)
{
	return key % m;
}
//����ؼ���
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
//���ҹؼ���
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
//ͨ��ɢ�е�ַ���ҹؼ���
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
//��ϣ����Һ�������
 
//��������������
//������
typedef struct BiNode
{
	int key;
	struct BiNode* lcd, * rcd;//���ҽ��
}BiNode, * BiTree;
//��ʼ��
void InitBT(BiTree& T)
{
	T = NULL;
}
//������
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
//��������������
void CreatT(BiTree& T, int array[], int n)
{
	int key;
	T = NULL;
	for (int i = 0; i < n; ++i)
	{
		InsertB(T, array[i]);
	}
}
//�����������Ĳ���
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
//�������������Һ�������

//�۰����
//ð������
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
//�۰����
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
//�۰���Һ�������

//˳�����
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
//˳����Һ�������

// ʹ��˳����ң�����1���������ʱ��
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

// ʹ���۰���ң�����1���������ʱ��
int BinarySTime1(int* a)
{
	// Ҫ�����۰���ң�Ҫ���������������۰���ҵ�ʱ��
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

// ʹ�ö������������ң�����1���������ʱ��
int BSTreeTime1(int* a)
{
	// �Ƚ�һ������������
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

// ʹ�ù�ϣ���ң�����1���������ʱ��
int HashTime1(int* a)
{
	// �Ƚ�һ����ϣ��
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

// ʹ���۰���ң�����100���������ʱ��
int BinarySTime2(int* a)
{
	// Ҫ�����۰���ң�Ҫ���������������۰���ҵ�ʱ��
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

// ʹ�ö������������ң�����100���������ʱ��
int BSTreeTime2(int* a)
{
	// �Ƚ�һ������������
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

// ʹ�ù�ϣ���ң�����100���������ʱ��
int HashTime2(int* a)
{
	// �Ƚ�һ����ϣ��
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

	cout << "��һ��ʹ�����ֲ����㷨����1���������" << endl;
	cout << "ʹ��˳�����1���������ʱ��: " << t1_1 << endl;
	cout << "ʹ���۰����1���������ʱ��: " << t1_2 << endl;
	cout << "ʹ�ö�������������1���������ʱ��: " << t1_3 << endl;
	cout << "ʹ�ù�ϣ�����1���������ʱ��: " << t1_4 << endl;
	cout << endl;

	cout << "�ڶ���ʹ�ó�˳���������Ĳ����㷨����10���������" << endl;
	int t2_2 = BinarySTime2(a);
	int t2_3 = BSTreeTime2(a);
	int t2_4 = HashTime2(a);

	cout << "ʹ���۰����10���������ʱ��: " << t2_2 << endl;
	cout << "ʹ�ö�������������10���������ʱ��: " << t2_3 << endl;
	cout << "ʹ�ù�ϣ�����10���������ʱ��: " << t2_4 << endl;
	cout << endl;
}

// ���Ҳ˵�
void menu()
{
	cout << "**************************************************" << endl;
	cout << "******** 1.˳�����        2.�۰����     ********" << endl;
	cout << "******** 3.��������������  4.��ϣ����     ********" << endl;
	cout << "************  5.�Ƚϲ����㷨ִ��ʱ��  ************" << endl;
	cout << "******************  0.�˳�  **********************" << endl;
	cout << "**************************************************" << endl;
}

int main()
{
	// �������������ʼ��
	srand((unsigned int)time(nullptr));
	int n = 10000;
	int randarr[10000] = { 0 };
	// ������ɲ�������
	for (int i = 0; i < n; ++i)
	{
		// rand() + i ʹ�ظ����ݱ���
		randarr[i] = (rand() + i) % 10000;
	}

	int input = 0;

	do
	{
		// ���ò˵�
		menu();
		cout << "��ѡ��Ҫʹ�õĲ����㷨>:";
		cin >> input;
		// �������������ִ�в�ͬ�Ĳ���
		switch (input)
		{
		case 1:
		{
			int a[10000], n, i = 0, j;
			cout << "������������ݸ���" << endl;
			cin >> n;
			cout << "�������������" << endl;
			for (i = 0; i < n; i++)
			{
				scanf_s("%d", &a[i]);
			}
			cout << "������Ҫ���ҵ���" << endl;
			cin >> j;
			cout << "����λ��Ϊ��";
			cout << Shunxuchazhao(a, j,n)<<endl;
		}
			break;
		case 2:
		{
			int i, a[10000], b, j, k;
			cout << "������������ݸ���" << endl;
			scanf_s("%d", &i);
			cout << "�������������" << endl;
			for (j = 0; j < i; j++)
			{
				scanf_s("%d", &a[j]);
			}
			cout << "������Ҫ���ҵ�����" << endl;
			cin >> b;
			MaoPaopx(i, a);
			cout << "�����ݵ�λ��Ϊ��";
			k = Zhebanchazhao(i, a, b);
			cout << k<<endl;
		}
			break;
		case 3:
		{
			int i = 1, n, a[10000];
			int c;
			cout << "������������ݸ���" << endl;
			scanf_s("%d", &i);
			BiTree T;
			cout << "�������������"<<endl;
			for (int j = 0; j < i; ++j)
			{
				scanf_s("%d", &a[j]);
			}
			CreatT(T, a, i);
			cout << "������Ҫ���ҵ���"<<endl;
			cin >> c;
			SearchT(T, c);
			cout << "������ָ��";
			cout << SearchT(T, c) << endl;
		}
			break;
		case 4:
		{
			hashbiao H;
			int a[10000], m, n, i = 0, j = 0, k = 0;
			cout << "����������ݸ���" << endl;
			cin >> n;
			cout << "�����������" << endl;
			for (i = 0; i < n; i++)
				cin >> a[i];
			cout << "�����ϣ�����еĳ���" << endl;
			cin >> m;
			Inithashbiao(&H, m);
			for (k = 0; k <= i; k++)
			{
				CharuKey(&H, a[k], m);
			}
			cout << "����Ҫ���ҵ�����" << endl;
			cin >> j;
			cout << "Ҫ���ҵ����ݵĵ�ַΪ��";
			cout << ChaZhao(H, j, m) << endl;
		}
			break;
		case 5:
			CompareTime(randarr);
			break;
		case 0:
			cout << "�˳�" << endl;
			break;
		default:
			cout << "�����������������" << endl;
		}
	} while (input);


	return 0;
}