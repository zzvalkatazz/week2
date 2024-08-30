#include <iostream>

// Структура на възел в свързания списък
struct Node {
    int data;
    Node* next;

    Node(int x) : data(x), next(nullptr) {}
};

// Функция за изтриване на n-тия елемент от края на списъка
void deleteNthFromEnd(Node*& head, int n) {
    Node* fast = head;
    Node* slow = head;

    // Придвижване на "бързия" указател n стъпки напред
    for (int i = 0; i < n; ++i) {
        if (fast == nullptr) {
            std::cout << "n е по-голямо от броя на елементите в списъка.\n";
            return; // Ако n е по-голямо от броя на елементите
        }
        fast = fast->next;
    }

    // Специален случай: изтриваме първия елемент
    if (fast == nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Придвижваме и двата указателя, докато "бързият" достигне края
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    // Сега slow е преди n-тия елемент от края. Изтриваме следващия възел.
    Node* temp = slow->next;
    slow->next = slow->next->next;
    delete temp; // Освобождаваме паметта на изтрития възел
}

// Функция за добавяне на нов възел в началото на списъка
void push(Node*& head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

// Функция за отпечатване на свързания списък
void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Основна функция
int main() {
    Node* head = nullptr;

    // Създаваме свързан списък: 1 -> 2 -> 3 -> 4 -> 5
    push(head, 5);
    push(head, 4);
    push(head, 3);
    push(head, 2);
    push(head, 1);

    std::cout << "Свързан списък преди изтриване: ";
    printList(head);

    int n = 2;
    deleteNthFromEnd(head, n);

    std::cout << "Свързан списък след изтриване на " << n << "-тия елемент от края: ";
    printList(head);

    // Освобождаваме цялата останала памет
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
