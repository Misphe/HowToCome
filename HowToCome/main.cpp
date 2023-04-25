#include <iostream>
#include "String.h"
#include "Functions.h"
#include "Map.h"
#include "Hashmap.h"

int main() {
	std::ios::sync_with_stdio(false);
	int width, height, k, commands;
	std::cin >> width >> height;
	Hashmap hashmap;

	Map map(width, height, hashmap);
	map.LoadMap();

	map.LoadCities();
	map.IterateMap(&Map::SearchConnections, &map, '*');
	
	hashmap.Print();
}