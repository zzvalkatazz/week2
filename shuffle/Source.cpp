#include<iostream>

template<typename T>
struct Node
{
	T data;
	Node* next;
	Node(T data) : data(data),next(nullptr){}
};
template<typename T>
Node<T>* getSecondHalf(Node<T>* list)
{
	Node<T>* slow = list;
	Node<T>* fast = list;
	
	while (fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	Node<T>* secondHalf = slow->next;
	slow->next = nullptr;
	return secondHalf;
}
template<typename T>
Node<T>* reverse(Node<T>*& head)
{
	Node<T>* prev = nullptr;
	Node<T>* current = head;

	while (current)
	{
		Node<T>* next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}
template<typename T>
Node<T>* shuffle(Node<T>* head)
{
	Node<T>* secondHalf = getSecondHalf(head);
	Node<T>* end = secondHalf;
	secondHalf = reverse(secondHalf);
	end->next = head;
	return secondHalf;
}
void print(Node<int>* head)
{
	while (head)
	{
		std::cout << head->data << ' ';
		head = head->next;
	}
}
template<typename T>
void Free(Node<T>* list)
{
	Node<T>* iter = list;
	while (iter != nullptr)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}
int main()
{
	Node<int>* head = new Node<int>(1);
	Node<int>* n2 = new Node<int>(2);
	Node<int>* n3 = new Node<int>(3);
	Node<int>* n4 = new Node<int>(4);
	Node<int>* n5 = new Node<int>(5);
	head->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	Node<int>* newHead = shuffle(head);
	print(newHead);
	free(head);
}
