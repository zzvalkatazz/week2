
#include <iostream>
using namespace std;

struct TreeNode
{
	int value;
	char operation;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int val) : value(val), operation(0), left(nullptr), right(nullptr){}
	TreeNode(char op) : value(0), operation(op), left(nullptr), right(nullptr) {}
};
int countNodes(TreeNode* node)
{
	if (!node) return 0;
	return 1 + countNodes(node->left) + countNodes(node->right);
}
int calculateExpression(TreeNode* numberNode, TreeNode* operationNode)
{
	int numDescendants = countNodes(numberNode);
	if (numberNode->left == nullptr && numberNode->right == nullptr) {
		return numberNode->value;  // Листо: просто стойността му
	}
	switch(operationNode->operation)
	{
		case'+':
			return numberNode->value + numDescendants;
		case'-':
			return numberNode->value - numDescendants;
		case'*':
			return numberNode->value * numDescendants;
		default:
			throw invalid_argument("Невалидна операция");
	}
}
int calculateSum(TreeNode* numberNode, TreeNode* operationNode)
{
	if (!numberNode || !operationNode)
	{
		return 0;
	}
	int currentResult = calculateExpression(numberNode, operationNode);

	int leftSum = calculateSum(numberNode->left, operationNode->left);
	int rightSum = calculateSum(numberNode->right, operationNode->right);

	return currentResult + leftSum + rightSum;
}
void deleteTree(TreeNode* node) {
	if (node) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

int main() {
	// Примерно числово дърво
	TreeNode* numberRoot = new TreeNode(5);
	numberRoot->left = new TreeNode(4);
	numberRoot->right = new TreeNode(1);
	numberRoot->left->left = new TreeNode(3);
	numberRoot->left->right = new TreeNode(2);
	numberRoot->right->right = new TreeNode(10);

	// Примерно дърво с операции
	TreeNode* operationRoot = new TreeNode('*');
	operationRoot->left = new TreeNode('+');
	operationRoot->right = new TreeNode('-');
	operationRoot->left->left = new TreeNode('+');
	operationRoot->left->right = new TreeNode('*');
	operationRoot->right->right = new TreeNode('-');

	// Изчисляваме общата сума от всички поддървета
	int result = calculateSum(numberRoot, operationRoot);
	cout << "Обща сума: " << result << endl;

	// Освобождаваме заделената памет
	deleteTree(numberRoot);
	deleteTree(operationRoot);

	return 0;
}