#pragma once
#include "String.h"
#include "List.h"
#include "ConnectionList.h"
#include "Defines.h"

struct Path {
	City* source;
	int distance;
	Path() : distance(INF), source(nullptr) {}
	Path(City* set_source, int set_distance) {
		source = set_source;
		distance = set_distance;
	}
	void Reset() {
		source = nullptr;
		distance = INF;
	}
};

class Hashmap;

class City {
private:
	String name;
	Position position;
	ConnectionList connections;

public:
	Path path;
	bool visited = false; // for optimalization
	int total_in_flights = 0;

	City();
	~City();
	City(String& set_name);
	City(String& set_name, Position set_pos, bool exists);
	City(String&& set_name);
	City(String& set_name, Position set_pos);
	City(String&& set_name, Position set_pos);

	String& GetName();
	const String& GetName() const;

	void AddConnection(City* city, int distance);
	bool ConnectionExists(City* other);
	Connection* GetConnection();

	bool operator==(City& other);
	bool operator==(String& other);
	bool operator==(char*& other);
	bool operator==(const City& other) const;
	friend std::ostream& operator<<(std::ostream& output, City& city);

	bool Empty();
};

