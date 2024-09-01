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

// Функция за добавяне на нов град в края на свързания списък
Node* addCity(Node* head, string city) {
    Node* newNode = new Node(city);
    if (!head) {
        return newNode;  // Връща новия град като начало на списъка
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;  // Преминава до последния възел
        }
        temp->next = newNode;  // Свързва новия възел към края на списъка
        return head;
    }
}

// Функция за добавяне на директна връзка (skip) между два града
void addSkipConnection(Node* head, string from, string to) {
    Node* fromNode = nullptr;
    Node* toNode = nullptr;
    Node* temp = head;

    // Намери двата града и създай връзка между тях
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

// Функция за намиране на най-краткия път от началото до последния вкаран град
vector<string> findShortestPath(Node* head, const vector<string>& mustVisit) {
    vector<string> path;
    Node* current = head;
    size_t visitIndex = 0;

    while (current) {
        path.push_back(current->city);

        // Проверка дали трябва да се премине към следващия град от mustVisit
        if (visitIndex < mustVisit.size() && current->city == mustVisit[visitIndex]) {
            visitIndex++;
        }

        // Ако има skip връзка и тя води към следващия необходим град
        if (current->skip && visitIndex < mustVisit.size() && current->skip->city == mustVisit[visitIndex]) {
            current = current->skip;
        }
        else {
            current = current->next;
        }

        // Ако текущият възел е последен (няма next), прекъсваме цикъла
        if (current && current->next == nullptr) {
            path.push_back(current->city);
            break;
        }
    }

    return path;
}

int main() {
    Node* cities = nullptr;

    // Добавяне на градове
    cities = addCity(cities, "Sofia");
    cities = addCity(cities, "Pazardzhik");
    cities = addCity(cities, "Plovdiv");
    cities = addCity(cities, "Dimitrovgrad");
    cities = addCity(cities, "StaraZagora");
    cities = addCity(cities, "NovaZagora");
    cities = addCity(cities, "Yambol");
    cities = addCity(cities, "Karnobat");
    cities = addCity(cities, "Burgas");
   

    // Добавяне на директни връзки (skip)
    addSkipConnection(cities, "Sofia", "Plovdiv");
    addSkipConnection(cities, "Plovdiv", "NovaZagora");
    addSkipConnection(cities, "Dimitrovgrad", "NovaZagora");
    addSkipConnection(cities, "StaraZagora", "Yambol");
    addSkipConnection(cities, "NovaZagora", "Burgas");

    // Списък на градовете, които Аня и Ванката искат да посетят
    vector<string> mustVisit = { "Plovdiv", "StaraZagora", "Yambol" };

    // Намиране на най-краткия маршрут от началото до последния вкаран град
    vector<string> path = findShortestPath(cities, mustVisit);

    // Принтиране на резултата
    cout << "Най-кратък маршрут от началото до последния вкаран град, преминаващ през задължителните градове: " << endl;
    for (const string& city : path) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
