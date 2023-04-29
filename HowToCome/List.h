#pragma once
#include "String.h"

template <typename T>
class Node {
public:
    T value;
    Node<T>* next;
    Node<T>* prev;
    Node(T value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
    ~Node() {
        // MEMORY LEAK????
    }
    
};

template <typename T>
class List {
public:
    Node<T>* head;
    Node<T>* last;
    List() {
        head = nullptr;
        last = nullptr;
    }

    void PushFront(T value) {
        Node<T>* node = new Node<T>(value);
        node->next = head;
        if (head != nullptr) {
            head->prev = node;
        }
        head = node;
    }

    void PushBack(T value) {
        if (head == nullptr) {
            head = new Node<T>(value);
            last = head;
        }
        else {
            last->next = new Node<T>(value);
            last->next->prev = last;
            last = last->next;
        }
    }

    template <typename U>
    T& Find(const U& value) const {
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

    void Print() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->value << "\n";
            current = current->next;
        }
    }

    void PrintBackwards() {
        Node<T>* current = last;
        while (current != nullptr) {
            std::cout << " " << *current->value;
            current = current->prev;
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
