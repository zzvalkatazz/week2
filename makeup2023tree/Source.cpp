#include<iostream>
#include<cstring>
#include<queue>

struct Employee
{
	char name[64];
	int daysOfWork;
	double salary;
};
template<typename T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;

	Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
};

bool addEmployee(Node<Employee>*& root, const Employee& emp)
{
	if (root == nullptr)
	{
		root = new Node<Employee>(emp);
		return true;
	}
	if (emp.daysOfWork < root->data.daysOfWork || (emp.daysOfWork == root->data.daysOfWork && strcmp(emp.name, root->data.name) < 0))
	{
		return addEmployee(root->left, emp);
	}
	else if (emp.daysOfWork > root->data.daysOfWork || (emp.daysOfWork == root->data.daysOfWork && strcmp(emp.name, root->data.name) > 0))
	{
		return addEmployee(root->right, emp);
	}
	else
	{
		std::cout << "Employee already exists in the hierarchy." << std::endl;
		return false;
	}
}
double findAverageDaysOfWork(Node<Employee>* root, int& sum, int& count)
{
	if (root == nullptr)
	{
		return 0;
	}
	if (root->left != nullptr)
	{
		findAverageDaysOfWork(root->left, sum, count);
	}
	sum += root->data.daysOfWork;
	count++;
	if (root->right != nullptr)
	{
		findAverageDaysOfWork(root->right, sum, count);
	}
	double average = sum / count;
	return average;
}
template <class T>
size_t findSize(Node<T>* r)
{
	if (r == nullptr)
	{
		return 0;
	}

	return 1 + findSize(r->left) + findSize(r->right);
}

void findMedianHelp(Node<Employee>* r, int& stopper, int& med)
{
	if (r == nullptr)
	{
		return;
	}

	findMedianHelp(r->left, stopper, med);
	stopper = stopper - 1;
	if (stopper == 0)
	{
		med = r->data.daysOfWork;
		return;
	}
	findMedianHelp(r->right, stopper, med);
}

int findMedian(Node<Employee>* r)
{
	int size = findSize(r);
	int med1 = 0;
	int med2 = 0;
	int size1 = size / 2;
	int size2 = size / 2 + 1;
	findMedianHelp(r, size1, med1);
	findMedianHelp(r, size2, med2);
	if (size % 2 == 0)
	{
		return (med1 + med2) / 2;
	}
	return med2;
}

double findMaxAverageSalary(Node<Employee>* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	std::queue<Node<Employee>*> q;
	q.push(root);

	double maxAverageSalary = 0;
	while (!q.empty())
	{
		int levelSize = q.size();
		double sumSalary = 0;
		for (int i = 0; i < levelSize; i++)
		{
			Node<Employee>* current = q.front();
			q.pop();

			sumSalary += current->data.salary;

			if (current->left)
			{
				q.push(current->left);
			}
			if (current->right)
			{
				q.push(current->right);
			}
		}
		double averageSalary = sumSalary / levelSize;
		if (averageSalary > maxAverageSalary)
		{
			maxAverageSalary = averageSalary;
		}
	}
	return maxAverageSalary;
}
template<typename T>
void Free(Node<T>*& root)
{
	if (root == nullptr)
	{
		return;
	}
	Free(root->left);
	Free(root->right);
	delete root;
}
int main()
{
	Node<Employee>* root = nullptr;

	Employee emp1 = { "Alice",5,5000 };
	Employee emp2 = { "Bob",2,4500 };
	Employee emp3 = { "Charlie",3,6000 };
	Employee emp4 = { "David",1,4800 };
	//Employee emp5 = { "David",5,4800 };

	addEmployee(root, emp1);
	addEmployee(root, emp2);
	addEmployee(root, emp3);
	addEmployee(root, emp4);
	//addEmployee(root, emp5);
	int sum = 0, count = 0;
	double avgDays = findMedian(root);
	std::cout << "Average days of work:" << avgDays << std::endl;

	double maxAvgSalary = findMaxAverageSalary(root);
	std::cout << "MaxAverage salary" << maxAvgSalary << std::endl;

	free(root);

	return 0;
}
