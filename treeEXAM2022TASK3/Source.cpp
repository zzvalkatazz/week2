#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct TreeNode
{
	int data;
	std::vector<TreeNode*> children;

	TreeNode(int value) : data(value){}
};
TreeNode* buildTree(const std::string& str, int& pos)
{
	if (pos >= str.size() || str[pos] != '[') return nullptr;

	pos++;
	std::string numStr;

	while (pos < str.size() && std::isdigit(str[pos]))
	{
		numStr += str[pos++];
	}
	int rootValue = std::stoi(numStr);
	TreeNode* root = new TreeNode(rootValue);

	while (pos < str.size() && str[pos] != ']')
	{
		if (str[pos] == '[')
		{
			TreeNode* child = buildTree(str, pos);
			if (child)
			{
				root->children.push_back(child);
			}	
		}
		else
		{
			pos++;
		}
	}
	pos++;

	return root;
}
TreeNode* buildTree(const std::string& str)
{
	int pos = 0;
	return buildTree(str, pos);
}
void compile(const std::string& commands, TreeNode* root)
{
	TreeNode* current = root;
	int i = 0;
	while (i < commands.size())
	{
		if (commands[i] == '(')
		{
			i++;
			std::string numStr;
			while (std::isdigit(commands[i]))
			{
				numStr += commands[i++];
			}
			i++;
			int index = std::stoi(numStr) - 1;
			if (index >= 0 && index < current->children.size())
			{
				current = current->children[index];
			}
			else
			{
				std::cerr << "Грешка: Невалиден индекс на наследник!" << std::endl;
				return;
			}
		}
		else if (commands[i] == 'e')
		{
			i += 2;
			while (std::isdigit(commands[i]))
			{
				i++;
			}
			i++;
			bool found = false;
			for (TreeNode* child : current->children)
			{
				if (child->data % 2 == 0)
				{
					current = child;
					found = true;
					break;
				}
			}
			if (!found) {
				std::cerr << "Грешка: Няма четен наследник!" << std::endl;
				return;
			}
		}
		else if (commands[i] == '>')
		{
			i++;
			std::string numStr;
			while (std::isdigit(commands[i]))
			{
				numStr += commands[i++];
			}
			int x = std::stoi(numStr);
			std::vector<int> result;
			std::queue<TreeNode*> queue;
			for (TreeNode* child : current->children) {
				queue.push(child);
			}
			while (!queue.empty())
			{
				TreeNode* node = queue.front();
				queue.pop();
				if (node->data > x)
				{
					result.push_back(node->data);
				}
				for (TreeNode* child : node->children)
				{
					queue.push(child);
				}
			}
			for (int value : result)
			{
				std::cout << value << " ";
			}
			std::cout << std::endl;
		}
		else
		{
			i++;
		}
	}
}
void deleteTree(TreeNode* root)
{
	if (!root)
	{
		return;
	}
	for (TreeNode* child : root->children)
	{
		deleteTree(child);
	}
	delete root;
}
int main()
{
	std::string treeStr = "[10 [20] [30 [5] [35] [8 [70]]]]";
	TreeNode* root = buildTree(treeStr);

	std::string commands = "(2) >8";
	compile(commands, root);
	deleteTree(root);

	return 0;
}