#include "Hashmap.h"

Hashmap::Hashmap() {
	map = new List<City>[HASHMAP_SIZE];
}

int Hashmap::Hash(City& key) {
	String name = key.GetName();
	int length = name.GetSize();
	int id = 0;
	for (int i = 0; i < length; i++) {
		id += name[i] - 'A';
	}
	return id;
}

void Hashmap::AddKey(City& key) {
	map[Hash(key)].push_back(key);
}

City& Hashmap::GetValue(City& key) {
	String nullstring = "NULL";
	static City null(nullstring);
	int id = Hash(key);

	City* found = &map[id].find(key);
	if (found->Empty()) return null;

	return *found;
}