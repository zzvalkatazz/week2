#include <stack>
#include <string>
#include <cassert>
#include<iostream>
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
int main() {
    std::cout << std::boolalpha; // Показваме булевите стойности като true/false

    std::cout << "!(f) => " << parseBoolExpr("!(f)") << std::endl;               // Очакван резултат: true
    std::cout << "|(f,t) => " << parseBoolExpr("|(f,t)") << std::endl;           // Очакван резултат: true
    std::cout << "&(f,t) => " << parseBoolExpr("&(f,t)") << std::endl;           // Очакван резултат: false
    std::cout << "|(&(t,f,t),!(t)) => " << parseBoolExpr("|(&(t,f,t),!(t))") << std::endl; // Очакван резултат: false

    return 0;
}