#pragma once
#include "String.h"
#include "List.h"
#include "ConnectionList.h"
#include "Defines.h"

class Hashmap;

class City {
private:
	String name;
	Position position;
	ConnectionList connections;
public:

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

	bool operator==(City& other);
	bool operator==(String& other);
	bool operator==(char*& other);
	bool operator==(const City& other) const;
	friend std::ostream& operator<<(std::ostream& output, City& city);

	bool Empty();
};

