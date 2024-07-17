#include<iostream>
#include<queue>

template<typename T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;
	Node(T data,Node<T>* left=nullptr,Node<T>* right=nullptr) 
		: data(data),left(left),right(right){}
	void free()
	{
		if (left)
		{
			left->free();
			delete left;
		}
		if (right)
		{
			right->free();
			delete right;
		}
	}
	void print()
	{
		if (this == nullptr)
		{
			std::cout << '*';
			return;
		}
		std::cout << '(';
		left->print();
		std::cout << data;
		right->print();
		std::cout')';
	}
};
// ������ 1
// ���� �� ���������� �� �����

// ���������� �������
int sumIter(Node<int>* root)
{
	std::queue<Node<int>*> q;
	int sum=0;
	if (root == nullptr)
	{
		return sum;
	}
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		q.pop();
		sum += root->data;
		if (root->left)
		{
			q.push(root->left);
		}
		if (root->right)
		{
			q.push(root->right);
		}
	}
	return sum;
}
int sumRec(Node<int>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	int sumLeftChild = sumRec(root->left);
	int sumRightChild = sumRec(root->right);
	return root->data + sumLeftChild + sumRightChild;
}
// ������ 2
// ���� ������� X �� ������� � �����
template<typename T>
bool contains(Node<T>* root, T x)
{
	if (root == nullptr)
	{
		return false;
	}
	return root->data == x || contains(root->left, x) || contains(root->right, x);
}
// ������ 3
// ����� �� ��������� � �����
template<typename T>
int elementsCount(Node<T>* root)
{
	if (!root)
	{
		return 0;
	}
	// ������� ���� (1 �������)
   // + ���� �� ��������� � ������ ��������
   // + ���� �� ��������� � ������� ��������
	return 1 + elementsCount(root->left) + elementsCount(root->right);
}
// ������ 4
// ������������ �������� �� ���� � �����
int max(Node<int>* root)
{
	if (!root->left && !root->right)
	{
		return root->data;
	}
	if (root->left && !root->right)
	{
		return std::max(root->data, max(root->left));
	}
	if (!root->left && root->right)
	{
		return std::max(root->data, max(root->right));
	}
	return std::max(root->data, std::max(max(root->left), max(root->right)));
}
// ������ 5
// ����� �� ������� � �����
int leaves(Node<int>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return leaves(root->left) + leaves(root->right);
}
// ������ 6
// �������� � ������ ���������� ��������
template<typename T>
Node<T>* subtree(Node<T>* root, T x)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	if (root->data == x)
	{
		return root;
	}
	Node<T>* sub = subtree(root->left, x);
	return sub ? sub : subtree(root->right, x);
}
// ������ 7
// �� �� �������� �������, ���������� �� ���
template<typename T>
void inOrder(Node<T>* root)
{
	if (root == nullptr)
	{
		return;
	}
	inOrder(root->left);
	std::cout << root->data << ' ';
	inOrder(root->right);
}
// ������ 8
// �� �� �������� �������, ���������� �� ���

template<typename T>
void inOrder(Node<T>* root)
{
	if (root == nullptr)
	{
		return;
	}

	std::cout << root->data << ' ';
	preOrder(root->left);
	preOrder(root->right);
}
//�� �� ������ ������ �� ���������� �� �������� ����
int getSumLevel(Node<int>* root, int level)
{
	if (root == nullptr)
	{
		return 0;
	}
	if (level == 0)
	{
		return getSumLevel(root->left, level - 1) + getSumLevel(root->right, level - 1);
	}
	return getSumLevel(root->left, level - 1) + getSumLevel(root->right, level - 1);
}
template<typename T>
void printLevel(Node<T>* root, int level)
{
	if (root == nullptr)
	{
		return;
	}
	if (level == 0)
	{
		std::cout << root->data << ' ';
	}
	printLevel(root->left, level - 1);
	printLevel(root->right, level - 1);
}
// ������ 11
// �� �� ������ ���������� �� �����

// ���������� �������
template<typename T>
int getHeightIter(Node<T>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	std::queue<Node<T>*> q;
	q.push(root);

	int height = 0;
	while (!q.empty())
	{
		int size = q.size();
		// ������ � ���� ������ � �������� �� �� �������� ���� ���������
		// �� ���� � ���� ����
		// �� ����� ��������� ������ �� ��������, � ������� ���� �������� � ��������
		while (size--)
		{
			Node<>* front = q.front();
			q.pop();
			if(front->left)
			{
				q.push(front->left);
			}
			if (front->right)
			{
				q.push(front->right);
			}
		}
		height++;
	}
	return height;
}
template<typename T>
int getHeightRec(Node<T>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return 1 + std::max(getHeightRec(root->left), getHeightRec(root->right));
}
int main()
{
	Node<int>* root = new Node<int>(1);
	root->left = new Node<int>(2);
	root->right = new Node<int>(3);
	root->left->left = new Node<int>(4);
	root->left->right = new Node<int>(5);
	root->right->left = new Node<int>(6);
	root->right->right = new Node<int>(7);

	std::cout << "darvo:";
	root->print();
	std::cout << "\nPoddarvo s koren 3:";
	subtree(root, 3)->print();

	std::cout << "\ninorder:";
	inOrder(root);

	std::cout << "\n���� �� ��������� (����������): " << sumRec(root);
	std::cout << "\n���� �� ��������� (����������): " << sumIter(root);

	std::cout << "\n������� ������� 2: " << contains(root, 2);
	std::cout << "\n������� ������� 8: " << contains(root, 8);

	std::cout << "\n���� �� ����������: " << elementsCount(root);
	std::cout << "\n���� �� ���������� � ������� � ����� 2: " << elementsCount(root->left);

	std::cout << "\n���������� ������� � �������: " << max(root);
	std::cout << "\n���� ����� � ������� � ����� 2: " << leaves(root->left);

	std::cout << "\n���� �� ���������� �� ���� 1 (��� 1): " << getSumLevel(root, 1);
	std::cout << "\n���� �� ���������� �� ���� 3 (��� 1): " << getSumLevel(root, 3);

	std::cout << "\n�������� �� ������� (����������): " << getHeightIter(root);
	std::cout << "\n�������� �� ������� (����������): " << getHeightRec(root);

	root->free();
	delete root;
}