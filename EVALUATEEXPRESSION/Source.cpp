#include<iostream>
#include<stack>
#include<string>
#include<queue>

using namespace std;

bool evaluateExpression(const string& expr);
bool evaluateExpressionHelper(const string& expr, size_t& index)
{
	stack<bool> st;
	while (index < expr.size())
	{
		char ch = expr[index];
		if (ch == 't')
		{
			st.push(true);
		}
		else if (ch == 'f')
		{
			st.push(false);
		}
		else if (ch == '!')
		{
			index++;
			bool val = evaluateExpressionHelper(expr, index);
			st.push(!val);
		}
		else if (ch == '&' || ch == '|')
		{
			bool result = (ch == '&');
			index++;//propuskame '('
			while (true)
			{
				index++;
				bool val = evaluateExpressionHelper(expr, index);

				if (ch == '&')
				{
					result = result && val;
				}
				else if (ch == '|')
				{
					result = result || val;
				}
				if (expr[index] == ')')
				{
					break;
				}
				
			}
			st.push(result);
		}
		else if (ch == ')')
		{
			break;
		}
		index++;
	}
	return st.top();
}
bool evaluateExpression(const string& expr)
{
	size_t index = 0;
	return evaluateExpressionHelper(expr, index);
}
int countTrueExpressions(queue<string> exprQueue)
{
	int count = 0;
	int size = exprQueue.size();

	for (int i = 0; i < size; ++i) {
		string expr = exprQueue.front();
		exprQueue.pop();

		if (evaluateExpression(expr)) {
			count++;
		}

		exprQueue.push(expr); // Връщаме елемента обратно в опашката
	}
	return count;
}
int main()
{
	queue<string> exprQueue;
	string input;
	int n;

	cout << "broq na bulevite izrazi:";
	cin >> n;
	cin.ignore();
	cout << "bulevite izrazi edin po edin" << endl;
	for (int i = 0; i < n; i++)
	{
		getline(cin, input);
		exprQueue.push(input);
	}
	int result = countTrueExpressions(exprQueue);
	cout << "Брой истинни булеви изрази: " << result << endl;
}