#include<iostream>

template<typename T>
bool representSameBST(T* arr1, T* arr2, int n)
{
	if (n == 0)
	{
		return true;
	}
	if (n == 1)
	{
		return arr1[0] == arr2[0];
	}
	T leftSubtree1[100];
	T rightSubtree1[100];
	T leftSubtree2[100];
	T rightSubtree2[100 ];

	int leftSubtree1Index = 0, rightSubtree1Index = 0, leftSubtree2Index = 0, rightSubtree2Index = 0;

	for (int i = 1; i < n; i++)
	{
		if (arr1[i] < arr1[0])
		{
			leftSubtree1[leftSubtree1Index++] = arr1[i];
		}
		else
		{
			rightSubtree1[rightSubtree1Index++] = arr1[i];
		}
		if (arr2[i] < arr2[0])
		{
			leftSubtree2[leftSubtree2Index++] = arr2[i];
		}
		else
		{
			rightSubtree2[rightSubtree2Index++] = arr2[i];
		}
	}
	bool currentSubtrees = leftSubtree1Index == leftSubtree2Index && rightSubtree1Index == rightSubtree2Index;

	return currentSubtrees && representSameBST(leftSubtree1, leftSubtree2, leftSubtree1Index) && representSameBST(rightSubtree1, rightSubtree2, rightSubtree1Index);
}
int main()
{
	int n = 11;
	int X[] = { 15, 25, 20, 22, 30, 18, 10, 8, 9, 12, 6 };
	int Y[] = { 15, 10, 12, 8, 25, 30, 6, 20, 18, 9, 22 };


	int X1[] = { 15, 25, 20, 22, 30, 19, 10, 8, 9, 12, 6 };
	int Y1[] = { 15, 10, 12, 8, 25, 30, 6, 20, 18, 9, 22 };

	std::cout << representSameBST(X, Y, n)
		<< ' '
		<< representSameBST(X1, Y1, n);
}