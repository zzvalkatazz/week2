#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

template<typename T>
struct NodeFull
{
	T data;
	vector<NodeFull<T>*> children;

	NodeFull(T data) : data(data){}
};
template<typename T>
void print(NodeFull<T>* root)
{
	cout << root->data << " ";
	for (int i = 0; i < root->children.size(); i++)
	{
		print(root->children[i]);
	}
}
template<typename T>
void free(NodeFull<T>* root)
{
	for (int i = 0; i < root->children.size(); i++)
	{
		free(root->children[i]);
	}
	delete root;
}
template<typename T>
bool contains(NodeFull<T>* root, T element)
{
	int size = root->children.size();
	if (root->data == element)
	{
		return true;
	}
	for (int i = 0; i < size; i++)
	{
		if (contains(root->children[i], element))
		{
			return true;
		}
	}
	return false;
}
template<typename T>
int sum(NodeFull<T>* root)
{
	int sum = root->data;
	for (int i = 0; i < root->children.size(); i++)
	{
		sum += sum(root->children[i]);
	}
	return sum;
}
template<typename T>
T maxT(NodeFull<T>* root)
{
	T maxEl = root->data;
	for (int i = 0; i < root->children.size(); i++)
	{
		maxEl = max(maxEl, maxT(root->children[i]));
	}
	return maxEl;
}
template<typename T>
int height(NodeFull<T>* root)
{
	int maxHeight = -1;
	for (int i = 0; i < root->children.size(); i++)
	{
		int currHeight = height(root->children[i]);
		if (currHeight > maxHeight)
		{
			maxHeight = currHeight;
		}
	}
	return maxHeight + 1;
}
template<typename T>
int getNumOfElements(NodeFull<T>* root)
{
	int numOfElements = 1;

	for (int i = 0; i < root->children.size(); i++)
	{
		numOfElements += getNumOfElements(root->children[i]);
	}
	return numOfElements;
}
string word(NodeFull<char>* root, int k)
{
	std::string wordOnLevel;

	if (root == nullptr)
	{
		return "";
	}
	if (k == 1)
	{
		return wordOnLevel + (char)root->data;
	}
	for (int i = 0; i < root->children.size(); i++)
	{
		wordOnLevel += word(root->children[i], k - 1);
	}
	return wordOnLevel;
}
//// Çàäà÷à 8: Äà ñå íàïèøå ôóíêöèÿ, êîÿòî ïðèåìà ïðîèçâîëíî äúðâî è âðúùà âñè÷êè äóìè, êîèòî ñà ïîëó÷åíè îò êîðåíà äî íÿêîå ëèñòî.
void fillWords(NodeFull<char>* root, vector<string>& v, string currentWord)
{
	currentWord += root->data;
	if (root ->children.size() == 0)
	{
		v.push_back(currentWord);
		return;
	}
	for (int i = 0; i < root->children.size(); i++)
	{
		fillWords(root->children[i], v, currentWord);
	}
}
template<typename T>
int getNumOfLeaves(NodeFull<T>* root)
{
	int numOfLeaves = 0;
	if(root->children.empty())
	{
		numOfLeaves++;
	}
	for (int i = 0; i < root->children.size(); i++)
	{
		numOfLeaves += getNumOfLeaves(root->children[i]);
	}
	return numOfLeaves;
}
template<typename T>
int maxBranching(NodeFull<T>* root)
{
	int maxBranching = 1;
	int tempBranching = 0;
	for (int i = 0; i < root->children.size(); i++)
	{
		tempBranching = getNumOfLeaves(root->children[i]);
		if (tempBranching > maxBranching)
	           {
		maxBranching = tempBranching;
	          }
	}
	
	return maxBranching;
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

	cout << maxBranching(root);
}
