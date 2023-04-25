#include "Map.h"
#include "Functions.h"
#include <iostream>

Map::Map(int set_width, int set_height, Hashmap& set_hashmap) : hashmap(set_hashmap) {
	width = set_width;
	height = set_height;
	map = new char* [width];
	city_map = new City** [width];
	for (int i = 0; i < width; i++) {
		map[i] = new char[height];
		city_map[i] = new City* [height];
	}
	
}

void Map::LoadMap() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cin >> map[j][i];
		}
	}
}

void Map::Print() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << map[j][i];
		}
		std::cout << "\n";
	}
}

void Map::LoadCities() {
	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {

			if (map[x][y] == '*') {
				AddCity(x, y);
			}
			else if (map[x][y] == '#' && IsIntersection(x, y)) {
				map[x][y] = '*';
				AddFakeCity(x, y);
			}

		}
	}
}

void Map::AddCity(const int& x, const int& y) {
	String name = FindCityName(x, y);
	City city(name, { x,y });
	hashmap.AddKey(city);
	city_map[x][y] = &hashmap[city];
}

void Map::AddFakeCity(const int& x, const int& y) {
	static int fake_city_id = 0;
	fake_city_id++;
	City city(CreateFakeName(fake_city_id), {x,y});
	hashmap.AddKey(city);
	city_map[x][y] = &hashmap[city];
}

String Map::FindCityName(const int& x, const int& y) {
	char character;
	int cur_x;
	int cur_y;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {

			if (i == 0 && j == 0) continue;
			cur_x = x + j;
			cur_y = y + i;

			if (!InsideMap(cur_x, cur_y)) continue;

			character = map[cur_x][cur_y];

			if (!CityCharacter(character)) continue;

			int start = LocateNameStart(cur_x, cur_y);
			cur_x = start;

			return CreateCityName(cur_x, cur_y);

		}
	}

	std::cout << "ERROR IN MAP - NO CITY NEXT TO *";
	return "ERROR";
}

bool Map::InsideMap(const int& x, const int& y) {
	if (x < 0 || x > width - 1 || y < 0 || y > height + 1) {
		return false;
	}
	return true;
}

int Map::LocateNameStart(int cur_x, int cur_y) {
	while (InsideMap(cur_x - 1, cur_y) && CityCharacter(map[cur_x - 1][cur_y])) {
		cur_x--;
	}

	return cur_x;
}

String Map::CreateCityName(int cur_x, int cur_y) {
	String name;

	while (InsideMap(cur_x, cur_y) && CityCharacter(map[cur_x][cur_y])) {
		name += map[cur_x][cur_y];
		cur_x++;
	}

	return name;
}

void Map::IterateMap(void(Map::*callback)(int, int), Map* map, char condition) {
	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {

			if (map->map[x][y] == condition) {
				(map->*callback)(x,y);
			}

		}
	}
}

// to think of
void Map::SearchConnections(int x, int y) {
	const int start_x = x;
	const int start_y = y;
	City* start = city_map[start_x][start_y];
	bool end = false;
	int travel_time = 0;
	while (!end) {
		travel_time++;
		x++;

		if (!InsideMap(x, y)) break;

		if (map[x][y] == '*') {
			City* found = city_map[x][y];
			start->AddConnection(found, travel_time, hashmap);
			found->AddConnection(start, travel_time, hashmap);
			std::cout << *start << " and " << *found << " connected\n";
			end = true;
		}

	}
}

// perhaps delete later
void Map::FindRoad(int start_x, int start_y) {
	
}

// not completed - still not sure if it is the correct way of doing connections
bool Map::IsIntersection(int start_x, int start_y) {
	int x = start_x;
	int y = start_y;
	int count = 0;
	if (InsideMap(x - 1, y)) {
		if (map[x - 1][y] == '#') count++;
	}
	if (InsideMap(x + 1, y)) {
		if (map[x + 1][y] == '#') count++;
	}
	if (InsideMap(x, y - 1)) {
		if (map[x][y - 1] == '#') count++;
	}
	if (InsideMap(x, y + 1)) {
		if (map[x][y + 1] == '#') count++;
	}

	if (count > 2) {
		return true;
	}
	else {
		return false;
	}
}

