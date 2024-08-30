

//������ 6 (���������): �� �� ������ �������, ����� ������ �������� ��� ������ �� ������� ����� � �������� ������ �� ����������, ����� �� ������� �� ������� ���� � ���� ���� ����� ���������.
template <typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	Node(const T& data) : data(data), left(nullptr), right(nullptr) {};
};
template<typename T>
int solveTask6(Node<T>* root, bool isOdd)
{
	if (root == nullptr)
	{
		return 0;
	}
	if (isOdd && root->right != nullptr && root->left == nullptr)
	{
		return root->data + solveTask6(root->right, !isOdd);
	}
	return solveTask6(root->right, !isOdd) + solveTask6(root->left, !isOdd);
}
template<class T>
int solveTask6(Node<T>* root)
{
	return solveTask6(root, false);
}
int main()
{

	Node<int>* root = new Node<int>(50);
	Node<int>* n1 = new Node<int>(25);
	Node<int>* n2 = new Node<int>(75);
	Node<int>* n3 = new Node<int>(12);
	Node<int>* n4 = new Node<int>(30);
	Node<int>* n5 = new Node<int>(60);
	Node<int>* n6 = new Node<int>(85);
	Node<int>* n7 = new Node<int>(52);
	Node<int>* n8 = new Node<int>(70);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
	n5->left = n7;
	n5->right = n8;

	solveTask6(root);
}