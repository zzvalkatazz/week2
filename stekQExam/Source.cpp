#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template<typename T>
void rearrangeSequence(stack<T>& s) {
    queue<T> evenQueue;  // ������ �� ���������� �� ����� �������
    queue<T> oddQueue;   // ������ �� ���������� �� ������� �������
    int index = 0;

    // ��������� ���������� �� ����� � �� ������������ � ����� ������
    while (!s.empty()) {
        T element = s.top();
        s.pop();

        if (index % 2 == 0) {
            evenQueue.push(element);  // ����� �������
        }
        else {
            oddQueue.push(element);   // ������� �������
        }
        index++;
    }

    // ������� ���������� � ����� ����� �� ������� �������
    while (!evenQueue.empty()) {
        s.push(evenQueue.front());
        evenQueue.pop();
    }

    // ���� ���� �������� ���������� �� ��������� �������
    while (!oddQueue.empty()) {
        s.push(oddQueue.front());
        oddQueue.pop();
    }

    // ������ �� ����������� � ������, �� �� ������� ��������� ��� ��� ���������
    queue<T> resultQueue;
    while (!s.empty()) {
        resultQueue.push(s.top());
        s.pop();
    }

    // ���������� �� ���������
    cout << "Rearranged sequence: ";
    while (!resultQueue.empty()) {
        cout << resultQueue.front() << " ";
        resultQueue.pop();
    }
    cout << endl;
}

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);

    rearrangeSequence(s);

    return 0;
}