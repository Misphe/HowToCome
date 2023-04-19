#include "City.h"

City::City() {
	name = nullptr;
}

City::City(String& set_name) {
	name = set_name;
}

City::City(String&& set_name) {
	name = set_name;
}

String& City::GetName() {
	return name;
}

const String& City::GetName() const {
	return name;
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
