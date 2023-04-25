#include "City.h"
#include "Defines.h"
#include "Hashmap.h"
#include "Connection.h"

City::City() {
	name = nullptr;
	position.x = 0;
	position.y = 0;
	real = false;
}

City::City(String& set_name, Position set_pos) {
	name = set_name;
	position = set_pos;
	real = true;
}

City::City(String& set_name, Position set_pos, bool exists) {
	name = set_name;
	position = set_pos;
	real = exists;
}

City::City(String&& set_name, Position set_pos) {
	name = set_name;
	position = set_pos;
	real = true;
}

City::City(String& set_name) {
	name = set_name;
	position = NULL_POS;
	real = false;
}

City::City(String&& set_name) {
	name = set_name;
	position = NULL_POS;
	real = false;
}

String& City::GetName() {
	return name;
}

const String& City::GetName() const {
	return name;
}

void City::AddConnection(City* city, int distance, Hashmap& hashmap) {
	Connection connection(city, distance);
	connections.PushBack({ city, distance });
}

bool City::operator==(City& other) {
	return GetName() == other.GetName();
}

bool City::operator==(const City& other) const {
	return GetName() == other.GetName();
}

bool City::Empty() {
	return name == "NULL";
}

std::ostream& operator<<(std::ostream& output, City& city) {
	output << city.GetName() << "(" << city.position.x << "," << city.position.y << ")";
	return output;
}
