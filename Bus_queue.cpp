#include <iostream>

using namespace std;

//Doubly linked list.
//QueueNode represents the person in the queue and the bus line chosen by this person.
struct QueueNode {
    string name;
    char line;
    QueueNode *prev;
    QueueNode *next;

    QueueNode(string name, char line, QueueNode *prev = nullptr, QueueNode *next = nullptr)
            : name(name), line(line), prev(prev), next(next) {}
};

//QueueList represents the queue and is responsible for managing the queue.
class QueueList {
private:
    QueueNode *head;
    QueueNode *tail;
public:
    //Default
    QueueList() {
        head = new QueueNode("", 0);
        tail = new QueueNode("", 0, head);
        head->next = tail;
    }

    //Display information of all passengers in the queue.
    void print_queue() {
        QueueNode *node = head->next;
        while (node != tail) {
            cout << "Name =" << node->name << ", Bus =" << node->line << "\n";
            node = node->next;
        }
        cout << endl;
    }

    //Remove a passenger from the queue.
    static void delete_passenger(QueueNode *passenger) {
        QueueNode *behind = passenger->prev;
        QueueNode *front = passenger->next;
        behind->next = front;
        front->prev = behind;
        delete passenger;
    }

    //Bring new passengers to the queue and return added passengers.
    QueueNode *append(string name, char line) {
        auto *passenger = new QueueNode(name, line);
        passenger->prev = tail->prev;
        tail->prev->next = passenger;
        tail->prev = passenger;
        passenger->next = tail;
        return passenger;
    }
};

//Linked list.
//BusNode represents the person(pointer to the QueueNode) on the bus.
struct BusNode {
    QueueNode *passenger;
    BusNode *next;

    BusNode(QueueNode *passenger, BusNode *next = nullptr) : passenger(passenger), next(next) {}
};

//BusList represents the people on the bus.
class BusList {
private:
    BusNode *head;
    BusNode *tail;
public:
    //Default
    BusList() {
        head = new BusNode(nullptr, nullptr);
        tail = head;
    }

    //Delete for all passengers in bus and also delete in QueueList
    void free_passenger() {
        BusNode *del;
        while (head != tail) {
            del = head;
            head = head->next;
            QueueList::delete_passenger(head->passenger);
            delete (del);
        }
    }

    //Bring new passengers to the bus;
    void append(QueueNode *passenger) {
        auto *newNode = new BusNode(passenger);
        newNode->next = nullptr;
        tail->next = newNode;
        tail = tail->next;
    }
};

BusList bus1;
BusList bus3;
BusList busS;
QueueList queue;

//Adds a passenger who wants to board bus line to the end of the queue
void AddPassenger(char line) {
    string name;
    cout << "name :";
    cin >> name;
    if (line == '1') bus1.append(queue.append(name, line));
    else if (line == '3') bus3.append(queue.append(name, line));
    else if (line == 'S') busS.append(queue.append(name, line));
}

//Removes all passenger who wants to board bus line from the queue.
void BoardBus(char line) {
    if (line == '1') bus1.free_passenger();
    else if (line == '3') bus3.free_passenger();
    else if (line == 'S') busS.free_passenger();
}

//Prints the bus each passenger in the queue for all passengers in the same order as the queue.
void GetQueue() {
    queue.print_queue();
}

//main
int main() {
    int choice = -1;
    char line;
    do {
        cout << "Choose 0: Exit the program.\n"
                "Choose 1: Add passenger.\n"
                "Choose 2: Board bus.\n"
                "Choose 3: Get queue.\n"
                "->";
        cin >> choice;
        if (choice == 1) {
            do {
                cout << "Choose your bus line (1,3,S):";
                cin >> line;
            } while (line != '1' && line != '3' && line != 'S');
            AddPassenger(line);
        } else if (choice == 2) {
            do {
                cout << "Choose your bus line (1,3,S):";
                cin >> line;
            } while (line != '1' && line != '3' && line != 'S');
            BoardBus(line);
        } else if (choice == 3) GetQueue();
        else cout << "Invalid input\n";
    } while (choice != 0);
    cout << "Exit program";
}