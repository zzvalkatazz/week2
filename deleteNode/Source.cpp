#include <iostream>

// Структура за възел на двоично наредено дърво
template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;

    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Функция за добавяне на елемент в дървото
template <typename T>
Node<T>* insert(Node<T>* root, T value) {
    if (root == nullptr) {
        return new Node<T>(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else {
        root->right = insert(root->right, value);
    }
    return root;
}
template<typename T>
Node<T>* findMin(Node<T>* root)
{
    while (root && root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}
template<typename T>
Node<T>* remove(Node<T>*& tree, const T& x)
{
    if (tree == nullptr)
    {
        return nullptr;
    }

    if (x < tree->data)
    {
        remove(tree->left, x);
    }
    else if (x > tree->data)
    {
        remove(tree->right, x);
    }
    else // x == tree->data
    {
        if (!tree->left && !tree->right)
        {
            delete tree;
            tree = nullptr;
        }
        else if (tree->left && tree->right)
        {
            tree->data = findMin(tree->right)->data;
            remove(tree->right, tree->data);
        }
        else
        {
            Node<T>* oldNode = tree;
            tree = tree->left ? tree->left : tree->right;
            delete oldNode;
        }
    }
    return tree;
}
template<typename T>
void inorder(Node<T>* root)
{
    if (root != nullptr)
    {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }
}
int main()
{
    Node<int>* root = nullptr;
      
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    std::cout << "Inorder traversal before deletion: ";
    inorder(root);
    std::cout << std::endl;

    // Изтриваме елемент от дървото (например, стойност 30)
    root = remove(root, 30);

    std::cout << "Inorder traversal after deletion: ";
    inorder(root);
    std::cout << std::endl;

    return 0;
}