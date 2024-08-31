#include<iostream>
#include<algorithm>

using namespace std;
struct Node
{
	int key;
	int height;
	Node* left;
	Node* right;
};
int height(Node* n)
{
	if (n == nullptr)
	{
		return 0;
	}
	return n->height;
}

int balanceFactor(Node* n)
{
	if(n == nullptr)
	{
		return 0;
	}
	return height(n->left) - height(n->right);
}
Node* createNode(int key)
{
	Node* node = new Node();
	node->key = key;
	node->left = node->right = nullptr;
	node->height = 1;
	return node;
}
Node* rotateRight(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	y->height = max(height(x->left), height(x->right)) + 1;
	//vrashtame noviq koren
	return x;
}
