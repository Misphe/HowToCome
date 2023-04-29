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
	Edge(City* set_destination, City* set_source, int set_distance) {
		destination = set_destination;
		path.source = set_source;
		path.distance = set_distance;
	}
	bool operator<(const Edge& other) {
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
	void Enqueue(City* set_city, Path path);
	void Heapify(int index);

	void Pop();
	Edge& Peek();

	bool Empty();
	void PrintTime();

	void start() {
		s_time = std::chrono::high_resolution_clock::now();
	}
	void end() {
		e_time = std::chrono::high_resolution_clock::now();
	}
	void update() {
		dur += std::chrono::duration_cast<std::chrono::microseconds>(e_time - s_time).count();
	}
};