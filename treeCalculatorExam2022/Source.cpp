#include<iostream>
#include<cmath>
#include<functional>

template<typename T>
struct BinTreeNode
{
	T data;
	BinTreeNode<T>* left;
	BinTreeNode<T>* right;

	BinTreeNode(T value) : data(value),left(nullptr),right(nullptr){}
};

double evaluate(BinTreeNode<char>* root)
{
	if (!root->left && !root->right)
	{
		return root->data-'0';
	}

	double leftValue = evaluate(root->left);
	double rightValue = evaluate(root->right);

	switch (root->data)
	{
	case'+': return leftValue + rightValue;
	case'-': return leftValue - rightValue;
	case'*': return leftValue * rightValue;
	case'/': return leftValue / rightValue;
	}
	return 0.0;
}

BinTreeNode<char>* findSubtreeWithResult(BinTreeNode<char>* root, double result, double c)
{
	if (!root)
	{
		return nullptr;
	}
	double currentResult = evaluate(root);

	if (std::abs(currentResult - result) <= c)
	{
		return root;
	}
	BinTreeNode<char>* leftResult = findSubtreeWithResult(root->left, result, c);
	if (leftResult)
	{
		return leftResult;
	}
	return findSubtreeWithResult(root->right, result, c);
}

template<typename T>
void deleteTree(BinTreeNode<T>* root)
{
	if (!root)
	{
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);

	delete root;
}
int main()
{
	BinTreeNode<char>* root = new BinTreeNode<char>('+');
	root->left = new BinTreeNode<char>('3');
	root->right = new BinTreeNode<char>('*');

	root->right->left = new BinTreeNode<char>('+');
	root->right->right = new BinTreeNode<char>('2');

	root->right->left->left = new BinTreeNode<char>('5');
	root->right->left->right = new BinTreeNode<char>('9');

	double result = 27.95;
	double c = 0.1;

	BinTreeNode<char>* subtree = findSubtreeWithResult(root, result, c);
	if (subtree)
	{
		std::cout << "namereno- " << subtree->data << std::endl;
	}
	else
	{
		std::cout << "nqma poddarvo" << std::endl;
	}
	deleteTree(root);
	return 0;
}