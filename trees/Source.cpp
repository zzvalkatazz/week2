#include<iostream>
#include<vector>
#include<tuple>
#include<queue>

struct Node
{
	int data;
	Node* left;
	Node* right;

	Node(int data) : data(data),left(nullptr),right(nullptr){}
};
bool leftLookSameAsRightLook(Node* t)
{
	if (t == nullptr)
	{
		return false;
	}
	std::queue<Node*> level;
	level.push(t);

	bool isSimilar = true;
	while (!level.empty())
	{
		int elements = level.size();

		Node* leftmost = level.front();
		Node* current = level.front();

		for (int i = 0; i < elements; i++)
		{
			current = level.front();
			level.pop();

			if (current->left)
			{
				level.push(current->left);
			}
			if (current->right)
			{
				level.push(current->right);
			}
		}
		if (current->data != leftmost->data)
		{
			isSimilar = false;
			break;
		}
	}
	return isSimilar;
}
int main()
{
	Node* root = new Node(1);
	root->left = new Node(2);
	root->left->left = new Node(3);
	root->left->right = new Node(4);
	root->left->right -> left = new Node(5);
	root->right = new Node(2);
	root->right->left = new Node(9);
	root->right->right = new Node(11);

	std::cout << leftLookSameAsRightLook(root) << std::endl;
}