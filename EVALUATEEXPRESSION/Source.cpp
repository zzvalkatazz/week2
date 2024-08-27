#include<iostream>
#include<stack>
#include<string>
#include<queue>

using namespace std;

char evaluate(std::stack<char>& s) {
    bool seenTrueUpToThisPoint = false, seenFalseUpToThisPoint = false;

    while (s.top() != '&' && s.top() != '!' && s.top() != '|') {
        if (s.top() == 't') {
            seenTrueUpToThisPoint = true;
        }
        else {
            seenFalseUpToThisPoint = true;
        }
        s.pop();
    }

    char op = s.top();
    s.pop(); // Попваме оператора след като го използваме

    if (op == '&' && !seenFalseUpToThisPoint) {
        return 't';
    }
    if (op == '!' && seenFalseUpToThisPoint) {
        return 't';
    }
    if (op == '|' && seenTrueUpToThisPoint) {
        return 't';
    }
    return 'f';
}

bool parseBoolExpr(const std::string& expression) {
    std::stack<char> s;

    for (int i = 0; i < expression.size(); i++) {
        char ch = expression[i];

        if (ch != ')' && ch != '(' && ch != ',') {
            s.push(ch);
        }
        if (ch == ')') {
            char evaluationResult = evaluate(s);
            s.push(evaluationResult);
        }
    }

    return s.top() == 't';
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

		exprQueue.push(expr); // Âðúùàìå åëåìåíòà îáðàòíî â îïàøêàòà
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
	cout << "Áðîé èñòèííè áóëåâè èçðàçè: " << result << endl;
}
