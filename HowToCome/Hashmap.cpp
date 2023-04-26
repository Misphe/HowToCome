#include "Hashmap.h"
#include "Defines.h"

Hashmap::Hashmap() {
	map = new List<City*>[HASHMAP_SIZE];
}

Hashmap::~Hashmap() {
	delete[] map;
}

int Hashmap::Hash(City& key) {
	String name = key.GetName();
	return Hash(name);
}

int Hashmap::Hash(String& key) {

	int length = key.GetSize();
	int digit_pos = 0;
	unsigned int key_val = 0;
	int digit;
	for (int i = 0; i < length; i++) {
		if (key[i] >= 'A') {
			digit = key[i] - 'A';
		}
		else {
			digit = key[i] - '0';
		}
		key_val = key_val + digit * pow(BASE, digit_pos);
		digit_pos = (digit_pos + 1) % (DIGITGROUP + 1);
	}
	return key_val % HASHMAP_SIZE;

	/*int length = key.GetSize();
	int id = 0;
	for (int i = 0; i < length; i++) {
		if (key[i] >= 'A') {
			id += (key[i] - 'A') * (i + 1) * 41;
		}
		else {
			id += (key[i] - '0') * (i + 1) * 41;
		}
	}
	return id % HASHMAP_SIZE;*/


}

int Hashmap::Hash(char*& key) {
	int length = strlen(key);
	int digit_pos = 0;
	unsigned int key_val = 0;
	int digit;
	for (int i = 0; i < length; i++) {
		if (key[i] >= 'A') {
			digit = key[i] - 'A';
		}
		else {
			digit = key[i] - '0';
		}
		key_val = key_val + digit * pow(BASE, digit_pos);
		digit_pos = (digit_pos + 1) % (DIGITGROUP + 1);
	}
	return key_val % HASHMAP_SIZE;
}

void Hashmap::AddKey(City* city) {
	map[Hash(*city)].PushBack(city);
}

City& Hashmap::GetValue(City* key) {
	String nullstring = "NULL";
	static City null(nullstring);
	int id = Hash(*key);

	City* found = map[id].Find(key);
	if (found->Empty()) return null;

	return *found;
}

City& Hashmap::GetValue(String key) {
	String nullstring = "NULL";
	static City null(nullstring);
	int id = Hash(key);

	City* searched = new City(key);
	City* found = map[id].Find(searched);
	delete searched;
	if (found->Empty()) return null;

	return *found;
}

City* Hashmap::operator[](String& key) {
	int id = Hash(key);

	City* found = map[id].PointerFind(key);

	return found;
}

City* Hashmap::operator[](char*& key) {
	int id = Hash(key);

	City* found = map[id].PointerFind(key);

	return found;
}

City* Hashmap::operator[](String&& key) {
	int id = Hash(key);

	City* found = map[id].PointerFind(key);

	return found;
}

City& Hashmap::operator[](City* city) {
	String nullstring = "NULL";
	static City null(nullstring);

	int id = Hash(*city);

	City* found = map[id].Find(city);

	if (found->Empty()) return null;

	return *found;
}

void Hashmap::Print() {
	for (int i = 0; i < HASHMAP_SIZE; i++) {
		if (map[i].Empty()) {
			continue;
		}
		else {
			map[i].Print();
		}
	}
}

void Hashmap::PrintTaken() {
	for (int i = 0; i < HASHMAP_SIZE; i++) {
		std::cout << i << ": ";
		std::cout << map[i].GetSize();
		std::cout << "\n";
	}
}
