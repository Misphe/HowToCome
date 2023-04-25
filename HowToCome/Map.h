#pragma once
#include "String.h"
#include "Hashmap.h"
#include "Queue.h"
#include "Vector.h"

class Map {
private:
	char** map;
	int width;
	int height;
	Hashmap& hashmap;
	City*** city_map;
	bool** visited;

public:
	Map(int set_width, int set_height, Hashmap& set_hashmap);

	void LoadMap();
	void Print();
	void LoadCity(int x, int y);
	void AddCity(const int& x, const int& y);
	//void AddFakeCity(const int& x, const int& y);
	String FindCityName(const int& x, const int& y);

	bool InsideMap(const int& x, const int& y);
	bool InsideMap(const Position& pos);

	int LocateNameStart(int cur_x, int cur_y);
	String CreateCityName(int cur_x, int cur_y);
	bool StartOrEndOfName(int x, int y);

	void IterateMap(void (Map::*callback)(int, int), Map* map, bool (Map::*condition)(int, int));

	void SearchConnections(int x, int y);

	void FindRoad(int start_x, int start_y);

	bool IsIntersection(int start_x, int start_y);

	void ResetVisited();
	void QueueAdjacent(Queue& queue, QueuePos& cur_slot);

	bool IsRoad(const int& x, const int& y);
	bool IsRoad(const Position& pos);
	bool IsCity(Position& pos);
	bool IsCity(int x, int y);
	bool NotVisited(Position& pos);
};

