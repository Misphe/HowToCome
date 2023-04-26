#pragma once
#include "String.h"
#include "List.h"
#include "City.h"
#define HASHMAP_SIZE 10099

class Hashmap {
private:
	List<City*>* map;
public:
	Hashmap();
	~Hashmap();

	int Hash(City& key);
	int Hash(String& key);
	int Hash(char*& key);

	void AddKey(City* key);

	City& GetValue(City* key);
	City& GetValue(String key);

	City& operator[](City* key);
	City* operator[](String& key);
	City* operator[](char*& key);
	City* operator[](String&& key);

	void Print();
	void PrintTaken();
};

