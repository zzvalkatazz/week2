#include<iostream>
#include<stack>
#include<vector>
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode():val(0),left(nullptr),right(nullptr){}
	TreeNode(int x,TreeNode *left,TreeNode *right) : val(x),left(left),right(right){}
};
std::vector<int> result;
void inorderTraversalUtil(TreeNode* node)
{
	if (!node)
	{
		return;
	}
	inorderTraversalUtil(node->left);
	result.push_back(node->val);
	inorderTraversalUtil(node->right);
}
std::vector<int> inorderTraversalRec(TreeNode* root)
{
	inorderTraversalUtil(root);
	return result;
}

