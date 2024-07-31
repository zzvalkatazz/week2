#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

template <typename T>
struct NodeFull
{
	T data;
	std::vector<NodeFull*> children;

	NodeFull(const T& data) : data(data) {};
};

template<typename T>
bool isTreeSameFromLeftAndRightView(const NodeFull<T>* root)
{
	if (root == nullptr)
	{
		return true;
	}
	std::list<const NodeFull<T>*> q;
	q.push_back(root);
	while (!q.empty())
	{
		if (q.front()->data != q.back()->data)
		{
			return false;
		}
		size_t currLevel = q.size();
		for (size_t i = 0; i < currLevel; i++)
		{
			const NodeFull<T>* curr = q.front();
			q.pop_front();
			for (const Node<T>* child : curr->children)
			{
				q.push_back(child);
			}
		}
	}
	return true;
}
int main()
{
	NodeFull<int>* root = new NodeFull<int>(1);

	(root->children).push_back(new NodeFull<int>(2));
	(root->children).push_back(new NodeFull<int>(3));
	(root->children).push_back(new NodeFull<int>(4));
	(root->children[0]->children).push_back(new NodeFull<int>(5));
	(root->children[1]->children).push_back(new NodeFull<int>(6));
	(root->children[1]->children[0]->children).push_back(new NodeFull<int>(7));
	(root->children[2]->children).push_back(new NodeFull<int>(8));
	(root->children[2]->children).push_back(new NodeFull<int>(10));
}