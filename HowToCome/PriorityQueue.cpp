#include "PriorityQueue.h"
#include "Functions.h"

void Priority_Queue::Enqueue(City* set_city, Path path) {

	pq.Add(set_city, path.source, path.distance);
	int number = pq.GetSize();
	int parent;
	while (number > 1) {
		parent = number / 2;
		if (pq[number - 1] < pq[parent - 1]) {
			Swap(pq[number - 1], pq[parent - 1]);
		}
		else {
			break;
		}
		number = parent;
	}
}

void Priority_Queue::Enqueue(City* set_city, City*& source, int& distance) {

	pq.Add(set_city, source, distance);
	int number = pq.GetSize();
	int parent;
	while (number > 1) {
		parent = number / 2;
		if (pq[number - 1] < pq[parent - 1]) {
			Swap(pq[number - 1], pq[parent - 1]);
		}
		else {
			break;
		}
		number = parent;
	}
}

void Priority_Queue::Pop() {
	Swap(pq.Front(), pq.Back());
	pq.PopBack();
	int index = 1;
	Heapify(index);
}

void Priority_Queue::Heapify(int current) {
	while (current * 2 <= pq.GetSize()) {
		int left = 2 * current;
		int right = 2 * current + 1;

		if (right > pq.GetSize()) {
			if (pq[left - 1] < pq[current - 1]) {
				Swap(pq[left - 1], pq[current - 1]);
			}
			break;
		}

		int smaller = pq[left - 1] < pq[right - 1] ? left : right;
		if (pq[smaller - 1] < pq[current - 1]) {
			Swap(pq[smaller - 1], pq[current - 1]);
			current = smaller;
		}
		else {
			break;
		}
	}
}

Edge& Priority_Queue::Peek() {
	return pq[0];
}

bool Priority_Queue::Empty() {
	return !pq.GetSize();
}

void Priority_Queue::Clear() {
	delete this;
}















































//
//void PriorityQueue::Enqueue(City* set_city, Connection* set_connection) {
//	if (head == nullptr) {
//		head = new PQNode(set_city, set_connection);
//		last = head;
//		return;
//	}
//
//	PQNode* current = head;
//	while (current != nullptr) {
//		if (set_connection->distance <= current->edge.distance) {
//			if (current == head) {
//				current->prev = new PQNode(set_city, set_connection);
//				head = current->prev;
//				head->next = current;
//			}
//			else {
//				PQNode* new_node = new PQNode(set_city, set_connection);
//				current->prev->next = new_node;
//				new_node->prev = current->prev;
//				new_node->next = current;
//				current->prev = new_node;
//			}
//			return;
//		}
//	}
//	last->next = new PQNode(set_city, set_connection);
//	last->next->prev = last;
//	last = last->next;
//}
//
//void PriorityQueue::Pop() {
//	if (head != nullptr) {
//		PQNode* tmp = head;
//		if (last == head) {
//			last = last->next;
//		}
//		head = head->next;
//		delete tmp;
//	}
//}
//
//bool PriorityQueue::Empty() {
//	return head == nullptr ? true : false;
//}
