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
Node* rotateLeft(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	// Извършваме завъртане
	y->left = x;
	x->right = T2;

	// Актуализираме височините
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Връщаме новия корен
	return y;
}
Node* balance(Node* node)
{
	int balance = balanceFactor(node);
	//двойнолява
	if (balance > 1 && balanceFactor(node->left) >= 0)
	{
		return rotateRight(node);
	}
	//ляводясно
	if (balance > 1 && balanceFactor(node->left) < 0)
	{
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	//двойнадясна
	if(balance<-1 && balanceFactor(node->right)<=0)
	{
		return rotateLeft(node);
	}
	//дясноляво
	if (balance < -1 && balanceFactor(node->right)>0)
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node->right);
	}
	return node;
}
Node* insert(Node* node, int key) {
	// 1. Нормално вмъкване в двоично наредено дърво
	if (node == nullptr)
		return createNode(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node; // Duplicate keys are not allowed

	// 2. Актуализираме височината на този възел
	node->height = 1 + max(height(node->left), height(node->right));

	// 3. Балансираме дървото
	return balance(node);
}

Node* search(Node* root, int key) {
	if (root == nullptr || root->key == key)
		return root;

	if (root->key < key)
		return search(root->right, key);

	return search(root->left, key);
}

void inorderTraversal(Node* root) {
	if (root != nullptr) {
		inorderTraversal(root->left);
		cout << root->key << " ";
		inorderTraversal(root->right);
	}
}

int main() {
	Node* root = nullptr;

	// Вмъкване на елементи
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);

	// Преход (inorder traversal)
	inorderTraversal(root);  // Output: 10 20 25 30 40 50
	cout << endl;

	// Търсене на елемент
	Node* found = search(root, 25);
	if (found != nullptr)
		cout << "Element found: " << found->key << endl;
	else
		cout << "Element not found" << endl;

	return 0;
}