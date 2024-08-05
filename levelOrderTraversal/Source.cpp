#include<iostream>
#include<queue>
#include<string>

template<typename T>
struct Node
{
	T data;
	Node* left, * right;
	Node(T data) : data(data),left(nullptr),right(nullptr){}
};
void levelOrderTraversal(Node<char>* root, std::vector<std::string>& levels)
{
	if (!root)
	{
		return;
	}
	std::queue < Node<char>*> q;
	q.push(root);
	while (!q.empty())
	{
		int size = q.size();
		std::string level;
		for (int i = 0; i < size; i++)
		{
			Node<char>* r = q.front();
			q.pop();

			level.push_back(r->data);
			if (r->left)
			{
				q.push(r->left);
			}
			if (r->right)
			{
				q.push(r->right);
			}
		}
		levels.push_back(level);
	}
}
template<typename T>
void levelZigZagOrder(Node<T>* root, std::vector<std::vector<T>>& levels)
{
	if (!root)
	{
		return;
	}
	std::queue<Node<T>*> q;
	q.push(root);
	int levelCheck = 0;
	while (!q.empty())
	{
		int n = q.size();
		std::vector<T> level;
		while (n--)
		{
			Node<T>* r = q.front();
			q.pop();
			if (levelCheck % 2)
			{
				level.insert(level.begin(), r->data);
			}
			else
			{
				level.push_back(r->data);
			}
			if (r->left)
			{
				q.push(r->left);
			}
			if (r->right)
			{
				q.push(r->right);
			}
		}
		levelCheck++;
		levels.push_back(level);
	}
}

int main()
{
	Node<char>* root = new Node<char>('a');
	root->left = new Node<char>('b');
	root->left->left = new Node<char>('c');
	root->left->right = new Node<char>('d');
	root->left->right->left = new Node<char>('e');
	root->right = new Node<char>('f');
	root->right->left = new Node<char>('g');
	root->right->right = new Node<char>('h');
	root->right->left->left = new Node<char>('i');
	root->right->right->left = new Node<char>('j');

	std::vector<std::string> levels;
	levelOrderTraversal(root, levels);

	for (int i = 0; i < levels.size(); i++)
	{
		std::cout << levels[i] << ' ';
	}
	std::cout << '\n';

	std::vector<std::vector<char>> levelsZigZag;
	levelZigZagOrder(root, levelsZigZag);

	for (int i = 0; i < levelsZigZag.size(); i++)
	{
		for (int j = 0; j < levelsZigZag[i].size(); j++)
		{
			std::cout << levelsZigZag[i][j] << ' ';
		}
		std::cout << '\n';
	}

	free(root);





}