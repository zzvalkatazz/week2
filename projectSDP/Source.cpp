#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string city;
    Node* next;
    Node* skip;

    Node(string city) : city(city), next(nullptr), skip(nullptr) {}
};

// ������� �� �������� �� ��� ���� � ���� �� ��������� ������
Node* addCity(Node* head, string city) {
    Node* newNode = new Node(city);
    if (!head) {
        return newNode;  // ����� ����� ���� ���� ������ �� �������
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;  // ��������� �� ��������� �����
        }
        temp->next = newNode;  // ������� ����� ����� ��� ���� �� �������
        return head;
    }
}

// ������� �� �������� �� �������� ������ (skip) ����� ��� �����
void addSkipConnection(Node* head, string from, string to) {
    Node* fromNode = nullptr;
    Node* toNode = nullptr;
    Node* temp = head;

    // ������ ����� ����� � ������ ������ ����� ���
    while (temp) {
        if (temp->city == from) {
            fromNode = temp;
        }
        if (temp->city == to) {
            toNode = temp;
        }
        temp = temp->next;
    }

    if (fromNode && toNode) {
        fromNode->skip = toNode;
    }
}

// ������� �� �������� �� ���-������� ��� �� �������� �� ��������� ������ ����
vector<string> findShortestPath(Node* head, const vector<string>& mustVisit) {
    vector<string> path;
    Node* current = head;
    size_t visitIndex = 0;

    while (current) {
        path.push_back(current->city);

        // �������� ���� ������ �� �� ������� ��� ��������� ���� �� mustVisit
        if (visitIndex < mustVisit.size() && current->city == mustVisit[visitIndex]) {
            visitIndex++;
        }

        // ��� ��� skip ������ � �� ���� ��� ��������� ��������� ����
        if (current->skip && visitIndex < mustVisit.size() && current->skip->city == mustVisit[visitIndex]) {
            current = current->skip;
        }
        else {
            current = current->next;
        }

        // ��� �������� ����� � �������� (���� next), ���������� ������
        if (current && current->next == nullptr) {
            path.push_back(current->city);
            break;
        }
    }

    return path;
}

int main() {
    Node* cities = nullptr;

    // �������� �� �������
    cities = addCity(cities, "Sofia");
    cities = addCity(cities, "Pazardzhik");
    cities = addCity(cities, "Plovdiv");
    cities = addCity(cities, "Dimitrovgrad");
    cities = addCity(cities, "StaraZagora");
    cities = addCity(cities, "NovaZagora");
    cities = addCity(cities, "Yambol");
    cities = addCity(cities, "Karnobat");
    cities = addCity(cities, "Burgas");
   

    // �������� �� �������� ������ (skip)
    addSkipConnection(cities, "Sofia", "Plovdiv");
    addSkipConnection(cities, "Plovdiv", "NovaZagora");
    addSkipConnection(cities, "Dimitrovgrad", "NovaZagora");
    addSkipConnection(cities, "StaraZagora", "Yambol");
    addSkipConnection(cities, "NovaZagora", "Burgas");

    // ������ �� ���������, ����� ��� � ������� ����� �� �������
    vector<string> mustVisit = { "Plovdiv", "StaraZagora", "Yambol" };

    // �������� �� ���-������� ������� �� �������� �� ��������� ������ ����
    vector<string> path = findShortestPath(cities, mustVisit);

    // ���������� �� ���������
    cout << "���-������ ������� �� �������� �� ��������� ������ ����, ���������� ���� �������������� �������: " << endl;
    for (const string& city : path) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
