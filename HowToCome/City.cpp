#include "City.h"
#include "Defines.h"
#include "Hashmap.h"
#include "Connection.h"

City::City() {
	name = nullptr;
	position = { 0,0 };
}

City::~City() {

}

City::City(String& set_name, Position set_pos) {
	name = set_name;
	position = set_pos;
}

City::City(String& set_name, Position set_pos, bool exists) {
	name = set_name;
	position = set_pos;
}

City::City(String&& set_name, Position set_pos) {
	name = set_name;
	position = set_pos;
}

City::City(String& set_name) {
	name = set_name;
	position = NULL_POS;
}

City::City(String&& set_name) {
	name = set_name;
	position = NULL_POS;
}

String& City::GetName() {
	return name;
}

const String& City::GetName() const {
	return name;
}

void City::AddConnection(City* city, int distance) {
	Connection* new_connection_to = new Connection(city, distance);
	connections.PushBack(new_connection_to);
}

bool City::ConnectionExists(City* other) {
	if (connections.Find(*other)) return true;
	return false;
}

Connection* City::GetConnection() {
	return connections.head;
}

bool City::operator==(City& other) {
	return GetName() == other.GetName();
}

bool City::operator==(String& checked_name) {
	return GetName() == checked_name;
}

bool City::operator==(char*& other) {
	if (name == other) {
		return true;
	}
	return false;
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
