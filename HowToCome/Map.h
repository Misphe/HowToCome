#pragma once
#include "String.h"
#include "Hashmap.h"

class Map {
private:
	char** map;
	int width;
	int height;
	Hashmap& hashmap;
	City*** city_map;

public:
	Map(int set_width, int set_height, Hashmap& set_hashmap);

	void LoadMap();
	void Print();
	void LoadCities();
	void AddCity(const int& x, const int& y);
	void AddFakeCity(const int& x, const int& y);
	String FindCityName(const int& x, const int& y);

	bool InsideMap(const int& x, const int& y);

	int LocateNameStart(int cur_x, int cur_y);
	String CreateCityName(int cur_x, int cur_y);

	void IterateMap(void (Map::*callback)(int, int), Map* map, char condition);

	void SearchConnections(int x, int y);

	void FindRoad(int start_x, int start_y);

	bool IsIntersection(int start_x, int start_y);
};

