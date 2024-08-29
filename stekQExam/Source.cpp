#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template<typename T>
void rearrangeSequence(stack<T>& s) {
    queue<T> evenQueue;  // Опашка за елементите на четни позиции
    queue<T> oddQueue;   // Опашка за елементите на нечетни позиции
    int index = 0;

    // Извличаме елементите от стека и ги разпределяме в двете опашки
    while (!s.empty()) {
        T element = s.top();
        s.pop();

        if (index % 2 == 0) {
            evenQueue.push(element);  // Четна позиция
        }
        else {
            oddQueue.push(element);   // Нечетна позиция
        }
        index++;
    }

    // Връщаме елементите в стека първо от четните позиции
    while (!evenQueue.empty()) {
        s.push(evenQueue.front());
        evenQueue.pop();
    }

    // След това добавяме елементите от нечетните позиции
    while (!oddQueue.empty()) {
        s.push(oddQueue.front());
        oddQueue.pop();
    }

    // Накрая ги прехвърляме в опашка, за да запазим правилния ред при извеждане
    queue<T> resultQueue;
    while (!s.empty()) {
        resultQueue.push(s.top());
        s.pop();
    }

    // Принтиране на резултата
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