#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
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

	Node(const T& data) : data(data),left(nullptr),right(nullptr){}
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
		if (root->left == nullptr)
		{
			root->left = new Node<Employee>(emp);
			return true;
	    }
		else
		{
			return addEmployee(root->left, emp);
		}
	}
	else if (emp.daysOfWork > root->data.daysOfWork || (emp.daysOfWork == root->data.daysOfWork && strcmp(emp.name, root->data.name) > 0))
	{
		if (root->right == nullptr)
		{
			root->right = new Node<Employee>(emp);
			return true;
		}
		else
		{
			return addEmployee(root->right, emp);
		}
	}
	else
	{
		cout << "employee already exists in the hierarchy." << endl;
		return false;
	}
}
int findAverageDaysOfWork(Node<Employee>* root, int& sum, int& count)
{
	if (root == nullptr)
		return 0;
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
	return sum /count;
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
void freeTree(Node<T>*& root)
{
	if (root == nullptr)
	{
		return;
	}
	freeTree(root->left);
	freeTree(root->right);
	
	delete root;
	root = nullptr;
}
int main() {
	Node<Employee>* root = nullptr;

	Employee emp1 = { "Alice", 500, 5000 };
	Employee emp2 = { "Bob", 450, 4500 };
	Employee emp3 = { "Charlie", 700, 7000 };
	Employee emp4 = { "David", 480, 4800 };

	addEmployee(root, emp1);
	addEmployee(root, emp2);
	addEmployee(root, emp3);
	addEmployee(root, emp4);

	int sum = 0, count = 0;
	int avgDays = findAverageDaysOfWork(root, sum, count);
	std::cout << "Average days of work: " << avgDays << std::endl;

	double maxAvgSalary = findMaxAverageSalary(root);
	std::cout << "Max average salary: " << maxAvgSalary << std::endl;

	freeTree(root);
	return 0;
}