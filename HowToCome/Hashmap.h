#pragma once
#include "String.h"
#include "List.h"
#include "City.h"
#define HASHMAP_SIZE 1000

class Hashmap {
private:
	List<City>* map;
public:
	Hashmap();
	int Hash(City& key);
	void AddKey(City& key);
	City& GetValue(City& key);

};

