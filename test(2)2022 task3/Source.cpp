#include<iostream>

template<typename T>
struct DLListElem
{
	T data;
	DListElem<T>* next;
	DLListElem<T>* prev;

	DLListElem(const T& data) : data(data),next(nullptr),prev(nullptr){}
};
template<typename T>
DLListElem<T>* split(DLListElem<T>* head)
{
	DLListELem<T>* slow = head;
	DLListELem<T>* fast = head;
	while (fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}8
	DLListElem<T>* secondHalf = slow->next;
	slow->next = nullptr;
	if (secondHalf)
	{
		secondHalf->prev = nullptr;
	}
	return secondHalf;
}
template<typename T>
DLListElem<T>* merge(DLListElem<T>* first, DLListElem<T>* second)
{
	if (!first) return second;
	if (!second) return first;

	if (first->data < second->data)
	{
		first->next = merge(first->next, second);
		first->next->prev = first;
		first->prev = nullptr;
		return first;
	}
	else
	{
		second->next = merge(first, second->next);
		second->next->prev = second;
		second->prev = nullptr;
		return second;
	}
}
template<typename T>
void sortAscending(DLListElem<T>*& start, DLListElem<T>*& end)
{
	if (!start || !start->next)
	{
		end = start;
		return;
	}
	DLListElem<T>* secondHalf = split(start);

	DLListElem<T>* endFirstHalf = nullptr;
	DLListElem<T>* endSecondHalf = nullptr;
	sortAscending(start, endFirstHalf);
	sortAscending(secondHalf, endSecondHalf);

	start = merge(start, secondHalf);

	end = start;
	while (end->next)
	{
		end = end->next;
	}
}
template<typename T>
void printList(DLListElem<T>* head)
{
	while (head)
	{
		std::cout << head->data << " ";
		head = head->next;
	}
	std::cout << std::endl;
}
template<typename T>
void deleteList(DLListElem<T> *& head)
{
	while (head)
	{
		DLListElem<T>* temp = head;
		head = head->next;
		delete temp;
	}
}
int main() {
	// Create a sample doubly linked list: 4 <-> 3 <-> 2 <-> 1 <-> 5
	DLListElem<int>* n1 = new DLListElem<int>(4);
	DLListElem<int>* n2 = new DLListElem<int>(3);
	DLListElem<int>* n3 = new DLListElem<int>(2);
	DLListElem<int>* n4 = new DLListElem<int>(1);
	DLListElem<int>* n5 = new DLListElem<int>(5);

	n1->next = n2;
	n2->prev = n1;
	n2->next = n3;
	n3->prev = n2;
	n3->next = n4;
	n4->prev = n3;
	n4->next = n5;
	n5->prev = n4;

	DLListElem<int>* start = n1;
	DLListElem<int>* end = n5;

	std::cout << "Original list: ";
	printList(start);

	// Sort the list
	sortAscending(start, end);

	std::cout << "Sorted list: ";
	printList(start);

	// Clean up memory
	deleteList(start);

	return 0;
}