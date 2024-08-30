#include <iostream>

// ��������� �� ����� � ��������� ������
struct Node {
    int data;
    Node* next;

    Node(int x) : data(x), next(nullptr) {}
};

// ������� �� ��������� �� n-��� ������� �� ���� �� �������
void deleteNthFromEnd(Node*& head, int n) {
    Node* fast = head;
    Node* slow = head;

    // ����������� �� "������" �������� n ������ ������
    for (int i = 0; i < n; ++i) {
        if (fast == nullptr) {
            std::cout << "n � ��-������ �� ���� �� ���������� � �������.\n";
            return; // ��� n � ��-������ �� ���� �� ����������
        }
        fast = fast->next;
    }

    // ��������� ������: ��������� ������ �������
    if (fast == nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // ����������� � ����� ���������, ������ "�������" �������� ����
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    // ���� slow � ����� n-��� ������� �� ����. ��������� ��������� �����.
    Node* temp = slow->next;
    slow->next = slow->next->next;
    delete temp; // ������������� ������� �� �������� �����
}

// ������� �� �������� �� ��� ����� � �������� �� �������
void push(Node*& head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

// ������� �� ����������� �� ��������� ������
void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// ������� �������
int main() {
    Node* head = nullptr;

    // ��������� ������� ������: 1 -> 2 -> 3 -> 4 -> 5
    push(head, 5);
    push(head, 4);
    push(head, 3);
    push(head, 2);
    push(head, 1);

    std::cout << "������� ������ ����� ���������: ";
    printList(head);

    int n = 2;
    deleteNthFromEnd(head, n);

    std::cout << "������� ������ ���� ��������� �� " << n << "-��� ������� �� ����: ";
    printList(head);

    // ������������� ������ �������� �����
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
