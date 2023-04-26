#include "ConnectionList.h"
#include "City.h"

ConnectionList::ConnectionList() : head(nullptr), last(nullptr) {

}

ConnectionList::~ConnectionList() {
    Connection* current = head;
    Connection* tmp = current;
    while (current != nullptr) {
        tmp = current;
        current = current->next;
        delete tmp;
    }
    head = nullptr;
    last = nullptr;
}

void ConnectionList::PushBack(Connection connection) {
    Connection* new_connection = new Connection(connection);
    if (head == nullptr) {
        head = new_connection;
        last = head;
    }
    else {
        last->next = new_connection;
        last = last->next;
    }
}

City* ConnectionList::Find(City& city) {
    Connection* current = head;
    while (current != nullptr) {
        if (*current->city == city) {
            return current->city;
        }
        current = current->next;
    }
    return nullptr;
}

Connection* ConnectionList::Find(City* city) {
    Connection* current = head;
    while (current != nullptr) {
        if (*current->city == *city) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
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