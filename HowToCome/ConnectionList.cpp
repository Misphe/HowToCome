#include "ConnectionList.h"
#include "City.h"

ConnectionList::ConnectionList() : head(nullptr) {

}

void ConnectionList::PushBack(Connection connection) {
    Connection* new_connection = new Connection(connection);
    if (head == nullptr) {
        head = new_connection;
    }
    else {
        Connection* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_connection;
    }
}

City& ConnectionList::Find(City& city) {
    static City null;
    Connection* current = head;
    while (current != nullptr) {
        if (*current->city == city) {
            return *current->city;
        }
        current = current->next;
    }
    return null;
}

void ConnectionList::Print() {
    Connection* current = head;
    while (current != nullptr) {
        std::cout << *current->city << "\n";
        current = current->next;
    }
}

bool ConnectionList::Empty() {
    if (head == nullptr) {
        return true;
    }
    return false;
}