#pragma once
#include "String.h"
#include "List.h"
#include "City.h"
#define HASHMAP_SIZE 2391

class Hashmap {
private:
	List<City>* map;
public:
	Hashmap();

	int Hash(City& key);
	int Hash(String& key);

	void AddKey(City& key);

	City& GetValue(City& key);
	City& GetValue(String key);

	City& operator[](City& key);
	City& operator[](String& key);
	City& operator[](String&& key);

	void Print();
};

