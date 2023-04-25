#pragma once
#include "String.h"
#include "List.h"
#include "ConnectionList.h"

class Hashmap;

struct Position {
	int x;
	int y;
};

class City {
private:
	String name;
	Position position;
	ConnectionList connections;
	bool real;
public:

	City();
	City(String& set_name);
	City(String& set_name, Position set_pos, bool exists);
	City(String&& set_name);
	City(String& set_name, Position set_pos);
	City(String&& set_name, Position set_pos);

	String& GetName();
	const String& GetName() const;

	void AddConnection(City* city, int distance, Hashmap& hashmap);

	bool operator==(City& other);
	bool operator==(const City& other) const;
	friend std::ostream& operator<<(std::ostream& output, City& city);

	bool Empty();
};

