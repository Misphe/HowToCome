#pragma once
#include "String.h"

template <typename T>
class Node {
public:
    T value;
    Node<T>* next;
    Node(T value) {
        this->value = value;
        next = nullptr;
    }
    ~Node() {
        if constexpr (std::is_pointer_v<T>) {
            if (value != nullptr) {
                delete value;
                value = nullptr;
            }
        }
    }
    
};

template <typename T>
class List {
public:
    Node<T>* head;
    Node<T>* last;
    List() {
        head = nullptr;
    }

    void PushFront(T value) {
        Node<T>* node = new Node<T>(value);
        node->next = head;
        head = node;
    }

    void PushBack(T value) {
        if (head == nullptr) {
            head = new Node<T>(value);
            last = head;
        }
        else {
            last->next = new Node<T>(value);
            last = last->next;
        }
    }

    T& Find(const T& value) const {
        static T null;
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return current->value;
            }
            current = current->next;
        }
        return null;
    }

    T& PointerFind(const T& value) const {
        static T null;
        Node<T>* current = head;
        while (current != nullptr) {
            if (*(current->value) == *value) {
                return current->value;
            }
            current = current->next;
        }
        return null;
    }

    T& PointerFind(String& value) const {
        static T null;
        Node<T>* current = head;
        while (current != nullptr) {
            if (*(current->value) == value) {
                return current->value;
            }
            current = current->next;
        }
        return null;
    }

    T& PointerFind(char*& value) const {
        static T null;
        Node<T>* current = head;
        while (current != nullptr) {
            if (*(current->value) == value) {
                return current->value;
            }
            current = current->next;
        }
        return null;
    }

    void Remove(T value) {
        Node<T>* current = head;
        Node<T>* prev = nullptr;
        while (current != nullptr) {
            if (current->value == value) {
                if (prev == nullptr) {
                    head = current->next;
                }
                else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void Print() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->value << "\n";
            current = current->next;
        }
    }

    bool Empty() {
        if (head == nullptr) {
            return true;
        }
        return false;
    }

    int GetSize() {
        int i = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            i++;
            current = current->next;
        }
        return i;
    }

    ~List() {
        Node<T>* current = head;
        Node<T>* tmp = current;
        while (current != nullptr) {
            tmp = current;
            current = current->next;
            delete tmp;
        }
        head = nullptr;
        last = nullptr;
    }
};
