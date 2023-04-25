#include "Hashmap.h"
#include "Defines.h"

Hashmap::Hashmap() {
	map = new List<City>[HASHMAP_SIZE];
}

int Hashmap::Hash(City& key) {
	String name = key.GetName();
	return Hash(name);
}

int Hashmap::Hash(String& key) {
	int length = key.GetSize();
	int id = 0;
	for (int i = 0; i < length; i++) {
		if (key[i] >= 'A') {
			id += (key[i] - 'A') * (i + 1) * 41;
		}
		else {
			id += (key[i] - '0') * (i + 1) * 41;
		}
	}
	return id % 2391;
}

void Hashmap::AddKey(City& key) {
	map[Hash(key)].PushBack(key);
}

City& Hashmap::GetValue(City& key) {
	String nullstring = "NULL";
	static City null(nullstring);
	int id = Hash(key);

	City* found = &map[id].Find(key);
	if (found->Empty()) return null;

	return *found;
}

City& Hashmap::GetValue(String key) {
	String nullstring = "NULL";
	static City null(nullstring);
	int id = Hash(key);

	City* found = &map[id].Find(key);
	if (found->Empty()) return null;

	return *found;
}

City& Hashmap::operator[](String& key) {
	String nullstring = "NULL";
	static City null(nullstring, NULL_POS);
	int id = Hash(key);

	City* found = &map[id].Find(key);
	if (found->Empty()) return null;

	return *found;
}

City& Hashmap::operator[](String&& key) {
	String nullstring = "NULL";
	static City null(nullstring);

	int id = Hash(key);

	City* found = &map[id].Find(key);
	if (found->Empty()) return null;

	return *found;
}

City& Hashmap::operator[](City& city) {
	String nullstring = "NULL";
	static City null(nullstring);

	int id = Hash(city);

	City* found = &map[id].Find(city);
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
