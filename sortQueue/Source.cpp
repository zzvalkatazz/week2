#include<iostream>
#include<queue>
#include<stack>

bool isSorted(std::queue<int>& q)
{
	// ako e prazna ili samo edin element
	if (q.empty() || q.size() == 1)
	{
		return true;
	}
	std::stack<int> helperStack;
	bool sorted = true;
	int prev = q.front();
	q.pop();
	helperStack.push(prev);
	while (!q.empty())
	{
		int current = q.front();
		q.pop();
		helperStack.push(current);
		if (prev > current)
		{
			sorted = false;
		}
		prev = current;
	}
	while (!helperStack.empty())
	{
		q.push(helperStack.top());
		helperStack.pop();
	}
	return sorted;
}
int main()
{
	std::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	if (isSorted(q))
	{
		std::cout << "The queue is sorted." << std::endl;
	}
	else
	{
		std::cout << "The queue is not sorted." << std::endl;
	}
	std::cout << "Queue elements after check:";
	while(!q.empty()){
		std::cout << q.front() << " ";
		q.pop();
	}
	std::cout << std::endl;
	return 0;
}