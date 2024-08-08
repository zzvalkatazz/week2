#include<iostream>
struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int data) : data(data),left(nullptr),right(nullptr){}
};
TreeNode* insertIntoBST(TreeNode* root, int data)
{
	if (!root)
	{
		return new TreeNode(data);
	}
	if (root->data > data)
	{
		root->left = insertIntoBST(root->left, data);
	}
	else
	{
		root->right = insertIntoBST(root->right, data);
	}
	return root;
}
TreeNode* deleteMin(TreeNode* x)
{
	if (x->left == nullptr)
	{
		return x->right;
	}
	x->left = deleteMin(x->left);
	return x;
}
TreeNode* min(TreeNode* x)
{
	if (x->left == nullptr)
	{
		return x;
	}
	return min(x->left);
}
TreeNode* deleteNode(TreeNode* x, int key)
{
	if (!x)
	{
		return nullptr;
	}
	if (x->data == key)
	{
		auto toDelete = x;
		if (!x->left)
		{
			auto toReturn = x->right;
			delete toDelete;
			return toReturn;
		}
		if (!x->right)
		{
			auto toReturn = x->left;
			delete toDelete;
			return toReturn;
		}
		TreeNode* t = x;
		x = min(t->right);
		x->right = deleteMin(t->right);
		x->left = t->left;
		delete toDelete;
	}
	else if (x->data < key)
	{
		x->right = deleteNode(x->right, key);
	}
	else if (x->data > key)
	{
		x->left = deleteNode(x->left, key);
	}
	return x;
}
void printInOrder(TreeNode* root) {
	if (root == nullptr) {
		return;
	}

	// Обхождаме лявото поддърво
	printInOrder(root->left);

	// Извеждаме стойността на текущия възел
	std::cout << root->data << " ";

	// Обхождаме дясното поддърво
	printInOrder(root->right);
}
int main() {
	// Създаване на празно дърво
	TreeNode* root = nullptr;

	// Добавяне на елементи в дървото
	root = insertIntoBST(root, 50);
	root = insertIntoBST(root, 30);
	root = insertIntoBST(root, 70);
	root = insertIntoBST(root, 20);
	root = insertIntoBST(root, 40);
	root = insertIntoBST(root, 60);
	root = insertIntoBST(root, 80);


	printInOrder(root);
	std::cout << std::endl;

	// Изтриване на елементи
	root = deleteNode(root, 20);

	printInOrder(root);
	std::cout << std::endl;

	root = deleteNode(root, 30);
	
	printInOrder(root);
	std::cout << std::endl;

	root = deleteNode(root, 50);

	printInOrder(root);
	std::cout << std::endl;

	return 0;
}