#pragma once
#include "Defines.h"

class QueueNode {
private:
	QueuePos slot;
	QueueNode* next;

	friend class Queue;
public:
	QueueNode(QueuePos set_slot) {
		slot = set_slot;
		next = nullptr;
	}
	~QueueNode(){}
};

class Queue {
private: 
	QueueNode* head;
	QueueNode* last;
public:
	Queue() {
		head = nullptr;
		last = nullptr;
	}

	void Pop() {
		if (head == nullptr) {
			return;
		}
		QueueNode* current = head;
		head = head->next;
		delete current;
	}

	QueuePos& Peek() {
		static QueuePos null;
		if (head == nullptr) {
			return null;
		}

		return head->slot;
	}

	void PushBack(QueuePos set_slot) {

		if (head == nullptr) {
			head = new QueueNode(set_slot);
			last = head;
			return;
		}
		
		last->next = new QueueNode(set_slot);
		last = last->next;
	}
	
	bool Empty() {
		if (head == nullptr) return true;

		return false;
	}

	~Queue(){}
};
