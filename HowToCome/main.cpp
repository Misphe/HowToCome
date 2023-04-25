#include <iostream>
#include "Defines.h"
#include "String.h"
#include "Functions.h"
#include "Map.h"
#include "Hashmap.h"
#include "Queue.h"
#include "Vector.h"

int main() {
	std::ios::sync_with_stdio(false);

	int width, height, k, commands;
	std::cin >> width >> height;
	Hashmap hashmap;

	Map map(width, height, hashmap);
	map.LoadMap();

	map.IterateMap(&Map::LoadCity, &map, &Map::IsCity);
	map.IterateMap(&Map::SearchConnections, &map, &Map::IsCity);

	hashmap.Print();
}