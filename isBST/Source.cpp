#include<climits>
#include<iostream>
#include<vector>

template<typename T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;
	Node(const T& data,Node<T>* left=nullptr,Node<T>* right=nullptr) : data(data),left(left),right(right){}
};
bool isBSTVer1(Node<int>* root, int minValue, int maxValue)
{
	if (root == nullptr)
	{
		return true;
	}
	if (root->data<minValue || root->data>maxValue)
	{
		return false;
	}
	return isBSTVer1(root->left, minValue, root->data) && isBSTVer1(root->right, root->data, maxValue);
}
bool isBSTVer1(Node<int>* root)
{
	return isBSTVer1(root, INT_MIN, INT_MAX);
}
int main()
{
	Node<int>* root1 = new Node<int>(12);
	root1->left = new Node<int>(5);
	root1->left->left = new Node<int>(3);
	root1->left->right = new Node<int>(14);
	root1->right = new Node<int>(20);
	root1->right->left = new Node<int>(15);
	root1->right->right = new Node<int>(28);

	std::cout << isBSTVer1(root1) << '\n';
}