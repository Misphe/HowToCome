#pragma once
#include "Connection.h"
#include "Vector.h"
#include "Hashmap.h"
#include <chrono>

class Edge {
public:
	City* destination;
	Path path;
	Edge() {
		destination = nullptr;
	}
	Edge(City* set_destination, City* set_source, int set_distance) : path(set_source, set_distance) {
		destination = set_destination;
	}
	Edge(City*&& set_destination, City*&& set_source, int&& set_distance) : path(set_source, set_distance) {
		destination = set_destination;
	}
	bool operator<(const Edge& other) {
		if (other.path.distance == INF) return true;

		return path.distance < other.path.distance;
	}
};

class Priority_Queue {
private:
	Vector<Edge> pq;
  

public:
	std::chrono::high_resolution_clock::time_point s_time = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point e_time = std::chrono::high_resolution_clock::now();
	long long dur = 0;
	Priority_Queue(int i) {
		pq.Reserve(i);
	}
	~Priority_Queue() {

	}

	void Enqueue(City* set_city, Path path);
	void Enqueue(City* set_city, City*& source, int& distance);
	void Heapify(int index);

	void Pop();
	Edge& Peek();

	bool Empty();
	void Clear();
};