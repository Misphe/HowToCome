#include "Map.h"
#include "Functions.h"
#include "stdio.h"
#include <iostream>

Map::Map(int set_width, int set_height) {
	width = set_width;
	height = set_height;
	map = new char* [width];
	city_map = new City** [width];
	visited = new bool* [width];
	for (int i = 0; i < width; i++) {
		map[i] = new char[height];
		city_map[i] = new City* [height];
		visited[i] = new bool [height];
		for (int j = 0; j < height; j++) {
			visited[i][j] = false;
		}
	}
	
}

Map::~Map() {
	for (int x = 0; x < width; x++) {
		delete[] map[x];
		delete[] visited[x];
		delete[] city_map[x];
	}
	delete[] map;
	delete[] visited;
	delete[] city_map;
}

void Map::PrintHashmap() {
	hashmap.PrintTaken();
}

void Map::LoadCoordinate(int x, int y) {
	map[x][y] = getchar();
	if (map[x][y] == '\n') {
		map[x][y] = getchar();
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

void Map::LoadCity(int x, int y) {
	AddCity(x, y);
}

void Map::AddCity(const int& x, const int& y) {
	String name = FindCityName(x, y);
	City* city = new City(name, { x,y });
	hashmap.AddKey(city);
	city_map[x][y] = city;
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
			if (!StartOrEndOfName(cur_x, cur_y)) continue;

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

bool Map::InsideMap(const Position& pos) {
	return InsideMap(pos.x, pos.y);
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

bool Map::StartOrEndOfName(int x, int y) {
	if (InsideMap(x - 1, y) && CityCharacter(map[x - 1][y])) {
		if (InsideMap(x + 1, y) && CityCharacter(map[x + 1][y])) {
			return false;
		}
	}
	return true;
}

void Map::IterateMap(void(Map::*callback)(int, int), bool(Map::*condition)(int,int)) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			if ((this->*condition)(x,y)) {
				(this->*callback)(x,y);
			}

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

void Map::ResetVisited(Vector<Position>& clearer) {
	for (Position& pos : clearer) {
		visited[pos.x][pos.y] = false;
	}
}

void Map::SearchConnections(int start_x, int start_y) {
	Queue queue;
	Vector<Position> clearer;
	QueuePos start = { {start_x,start_y},0 };
	QueueAdjacent(queue, start);
	visited[start_x][start_y] = true;
	clearer.Add(start.position);
	
	while (!queue.Empty()) {
		QueuePos current_pos = queue.Peek();
		clearer.Add({ current_pos.position.x, current_pos.position.y });

		if (IsCity(current_pos.position)) {
			int x = current_pos.position.x;
			int y = current_pos.position.y;
			int distance = current_pos.distance;

			city_map[start_x][start_y]->AddConnection(city_map[x][y], distance);
		}
		else {
			QueueAdjacent(queue, current_pos);
		}
		queue.Pop();
	}

	// TODO fix memory leaks
	ResetVisited(clearer);
}

void Map::QueueAdjacent(Queue& queue, QueuePos& cur_slot) {
	int x = cur_slot.position.x;
	int y = cur_slot.position.y;
	int distance = cur_slot.distance;
	Position tmp[] = { {x - 1,y},{x + 1,y},{x, y + 1},{x, y - 1} };

	for (auto& pos : tmp) {
		if (InsideMap(pos) && NotVisited(pos) && (IsRoad(pos) || IsCity(pos))) {
			visited[pos.x][pos.y] = true;
			queue.PushBack({ pos, distance + 1 });
		}
	}
}

bool Map::IsRoad(const int& x, const int& y) {
	if (map[x][y] == '#') return true;
	return false;
}

bool Map::IsRoad(const Position& pos) {
	return IsRoad(pos.x, pos.y);
}

bool Map::ReturnTrue(int x, int y) {
	return true;
}

bool Map::IsCity(Position& pos) {
	return IsCity(pos.x, pos.y);
}

bool Map::IsCity(int x, int y) {
	if (map[x][y] == '*') {
		return true;
	}
	return false;
}

bool Map::NotVisited(Position& pos) {
	if (visited[pos.x][pos.y] == false) return true;
	return false;
}

void Map::LoadFlights() {
	int flights_count;
	std::cin >> flights_count;
	char* city1 = new char[64];
	char* city2 = new char[64];
	int distance;

	getchar();
	int i;
	for (i = 0; i < flights_count; i++) {
		distance = 0;
		InputCityName(city1);
		InputCityName(city2);
		InputDistance(distance);

		City* city1_p = hashmap[city1];
		City* city2_p = hashmap[city2];
		city1_p->AddConnection(city2_p, distance);
		city2_p->AddConnection(city1_p, distance);
	}
	delete[] city1;
	delete[] city2;
}



