#pragma once
#include <iostream>
class City;

class Connection {
public:
	City* city;
	int distance;
	Connection* next;

	friend std::ostream& operator<<(std::ostream& output, Connection& connection) {
		output << connection.city << ", " << connection.distance;
		return output;
	}

	Connection() {
		city = nullptr;
		distance = 0;
	}
	Connection(City* destination, int set_distance) {
		city = destination;
		distance = set_distance;
		next = nullptr;
	}
	Connection(Connection& other) {
		city = other.city;
		distance = other.distance;
		next = nullptr;
	}
	Connection(Connection&& other) {
		city = other.city;
		distance = other.distance;
		next = nullptr;
		other.city = nullptr;
		other.distance = 0;
	}
};
