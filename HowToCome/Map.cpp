#include "Map.h"
#include "Functions.h"
#include <iostream>

Map::Map(int set_width, int set_height, Hashmap& set_hashmap) : hashmap(set_hashmap) {
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

void Map::LoadCity(int x, int y) {
	AddCity(x, y);
}

void Map::AddCity(const int& x, const int& y) {
	String name = FindCityName(x, y);
	City city(name, { x,y });
	hashmap.AddKey(city);
	city_map[x][y] = &hashmap[city];
}

//void Map::AddFakeCity(const int& x, const int& y) {
//	static int fake_city_id = 0;
//	fake_city_id++;
//	City city(CreateFakeName(fake_city_id), {x,y});
//	hashmap.AddKey(city);
//	city_map[x][y] = &hashmap[city];
//}

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

void Map::IterateMap(void(Map::*callback)(int, int), Map* map, bool(Map::*condition)(int,int)) {
	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {

			if ((map->*condition)(x,y)) {
				(map->*callback)(x,y);
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

void Map::ResetVisited() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			visited[i][j] = false;
		}
	}
}

void Map::SearchConnections(int start_x, int start_y) {
	Queue queue;
	Vector<Position> visited_v;
	QueuePos start = { {start_x,start_y},0 };
	QueueAdjacent(queue, start);
	visited[start_x][start_y] = true;

	// TODO add vector logic
	
	while (!queue.Empty()) {
		QueuePos current_pos = queue.Peek();
		if (current_pos.position.x == 7 && current_pos.position.y == 4) {
			int x = 1;
		}
		if (current_pos.position.x == 9 && current_pos.position.y == 4) {
			int x = 2;
		}

		if (IsCity(current_pos.position)) {
			int x = current_pos.position.x;
			int y = current_pos.position.y;
			int distance = current_pos.distance;

			city_map[start_x][start_y]->AddConnection(city_map[x][y], distance, hashmap);
		}
		else {
			QueueAdjacent(queue, current_pos);
		}
		queue.Pop();
	}

	// TODO fix memory leaks
	ResetVisited();
}

void Map::QueueAdjacent(Queue& queue, QueuePos& cur_slot) {
	int x = cur_slot.position.x;
	int y = cur_slot.position.y;
	Position tmp = cur_slot.position;


	// add vector positions
	tmp.x = x - 1;
	if (InsideMap(tmp) && NotVisited(tmp) && (IsRoad(tmp) || IsCity(tmp))) {
		visited[tmp.x][tmp.y] = true;
		queue.PushBack({ tmp, cur_slot.distance + 1 });
	}
	tmp.x = x + 1;
	if (InsideMap(tmp) && NotVisited(tmp) && (IsRoad(tmp) || IsCity(tmp))) {
		visited[tmp.x][tmp.y] = true;
		queue.PushBack({ tmp, cur_slot.distance + 1 });
	}
	tmp.x = x;
	tmp.y = y + 1;
	if (InsideMap(tmp) && NotVisited(tmp) && (IsRoad(tmp) || IsCity(tmp))) {
		visited[tmp.x][tmp.y] = true;
		queue.PushBack({ tmp, cur_slot.distance + 1 });
	}
	tmp.y = y - 1;
	if (InsideMap(tmp) && NotVisited(tmp) && (IsRoad(tmp) || IsCity(tmp))) {
		visited[tmp.x][tmp.y] = true;
		queue.PushBack({ tmp, cur_slot.distance + 1 });
	}
}

bool Map::IsRoad(const int& x, const int& y) {
	if (map[x][y] == '#') return true;
	return false;
}

bool Map::IsRoad(const Position& pos) {
	if (map[pos.x][pos.y] == '#') return true;
	return false;
}

bool Map::IsCity(Position& pos) {
	if (map[pos.x][pos.y] == '*') {
		return true;
	}
	return false;
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

//const int start_x = x;
//const int start_y = y;
//City* start = city_map[start_x][start_y];
//bool end = false;
//int travel_time = 0;
//while (!end) {
//	travel_time++;
//	x++;
//
//	if (!InsideMap(x, y)) break;
//
//	if (map[x][y] == '*') {
//		City* found = city_map[x][y];
//		start->AddConnection(found, travel_time, hashmap);
//		found->AddConnection(start, travel_time, hashmap);
//		std::cout << *start << " and " << *found << " connected\n";
//		end = true;
//	}
//
//}

