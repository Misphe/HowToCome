#pragma once
#include "String.h"
#include "List.h"
#include "Pair.h"


class City {
private:
	String name;
	List<Pair<City, int>> connections;
public:
	City();
	City(String& set_name);
	City(String&& set_name);
	String& GetName();
	const String& GetName() const;
	bool operator==(City& other);
	bool operator==(const City& other) const;

	bool Empty();
};

