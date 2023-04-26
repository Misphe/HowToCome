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
	Hashmap hashmap;
	City*** city_map;
	bool** visited;

public:
	Map(int set_width, int set_height);
	~Map();

	void PrintHashmap();

	// Creating city connections
	void SearchConnections(int x, int y);
	void QueueAdjacent(Queue& queue, QueuePos& cur_slot);

	// City creation
	void LoadCoordinate(int x, int y);
	void LoadCity(int x, int y);
	int LocateNameStart(int cur_x, int cur_y);
	String CreateCityName(int cur_x, int cur_y);
	String FindCityName(const int& x, const int& y);
	void AddCity(const int& x, const int& y);
	bool StartOrEndOfName(int x, int y);

	// Flight related
	void LoadFlights();

	// visited array related
	void FindRoad(int start_x, int start_y);
	void ResetVisited(Vector<Position>& clearer);
	bool NotVisited(Position& pos);

	// map array related
	void Print();
	void IterateMap(void (Map::*callback)(int, int), bool (Map::*condition)(int, int));
	bool InsideMap(const int& x, const int& y);
	bool InsideMap(const Position& pos);
	bool IsRoad(const int& x, const int& y);
	bool IsRoad(const Position& pos);
	bool IsIntersection(int start_x, int start_y);

	// Iteration conditions
	bool ReturnTrue(int x, int y);
	bool IsCity(Position& pos);
	bool IsCity(int x, int y);
};

