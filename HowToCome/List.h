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
};

template <typename T>
class List {
public:
    Node<T>* head;
    List() {
        head = nullptr;
    }

    void push_front(T value) {
        Node<T>* node = new Node<T>(value);
        node->next = head;
        head = node;
    }

    void push_back(T value) {
        Node<T>* node = new Node<T>(value);
        if (head == nullptr) {
            head = node;
        }
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = node;
        }
    }

    T& find(const T& value) const {
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

    void remove(T value) {
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

    void print() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << "\n";
    }


};
