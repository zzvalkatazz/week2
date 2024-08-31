#include <iostream>
#include <queue>

template<typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    Node(const T& data, Node<T>* left = nullptr, Node<T>* right = nullptr) : data(data), left(left), right(right) {}
};

template<typename T>
void isOddEven(Node<T>* root)
{
    if (!root)
    {
        return;
    }

    bool descending = true, ascending = true;
    int level = 0;

    std::queue<Node<T>*> q;
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        T prev;  // Не инициализираме `prev` предварително

        // Фиксираме стойността на prev на първия възел от текущото ниво
        bool firstElement = true;

        for (int i = 0; i < size; i++)
        {
            Node<T>* curr = q.front();
            q.pop();

            
            prev = INT_MIN;
            if (level % 2 != 0 && curr->data >= prev)
            {
                descending = false;
            }
            if (level % 2 == 0 && curr->data <= prev)
            {
                ascending = false;
            }

            prev = curr->data;

            if (curr->left != nullptr)
            {
                q.push(curr->left);
            }
            if (curr->right != nullptr)
            {
                q.push(curr->right);
            }
        }
        level++;
    }

    if (ascending)
    {
        std::cout << "IsEven" << std::endl;
    }
    if (descending)
    {
        std::cout << "IsOdd" << std::endl;
    }
    if (!ascending && !descending)
    {
        std::cout << "NO EVEN-NO ODD" << std::endl;
    }
}

template<typename T>
void Free(Node<T>* root)
{
    if (!root)
    {
        return;
    }
    Free(root->left);
    Free(root->right);
    delete root;
}

int main()
{
    // Създаваме дървото
    Node<int>* root = new Node<int>(8);
    Node<int>* n2 = new Node<int>(6);
    Node<int>* n3 = new Node<int>(10);
    Node<int>* n4 = new Node<int>(4);
    Node<int>* n5 = new Node<int>(7);
    Node<int>* n6 = new Node<int>(9);
    Node<int>* n7 = new Node<int>(11);
    Node<int>* n8 = new Node<int>(3);
    Node<int>* n9 = new Node<int>(5);

    // Свързваме възлите
    root->left = n2;
    root->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->left = n6;
    n3->right = n7;
    n4->left = n8;
    n4->right = n9;

    // Извършваме проверката
    isOddEven(root);

    // Освобождаваме паметта
    Free(root);

    return 0;
}
