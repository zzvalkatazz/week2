#include<iostream>

template<typename T>
struct ListNode
{
	int val;
	ListNode<T>* next;
	ListNode<T>(int x) : val(x),next(nullptr){}
};
template<typename T>
ListNode<T>* oddEvenList(ListNode<T>* head)
{
	if (!head)
	{
		return head;
	}
	ListNode<T>* odd = head, * even = head->next, * evenHead = even;
	while (even && even->next)
	{
		odd->next = even->next;
		odd = odd->next;
		even->next = odd->next;
		even = even->next;
	}
	odd->next = evenHead;
	return head;
}

template<typename T>
void print(ListNode<T>* head)
{
	while (head)
	{
		std::cout << head->val << ' ';
		head = head->next;
	}
}
template<typename T>
void deleteList(ListNode<T>* head)
{
	while (head)
	{
		ListNode<T>* temp = head;
		head = head->next;
		delete temp;
	}
}
int main()
{
	ListNode<int>* head = new ListNode<int>(1);
	ListNode<int>* n2 = new ListNode<int>(2);
	ListNode<int>* n3 = new ListNode<int>(3);
	ListNode<int>* n4 = new ListNode<int>(4);
	ListNode<int>* n5 = new ListNode<int>(5);

	head->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;

	std::cout << "Original list:";
	print(head);

	head = oddEvenList(head);

	std::cout << "After oddEvenList:";
	print(head);

	deleteList(head);

	return 0;
}