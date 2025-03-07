#include "Map.h"
#include "Functions.h"
#include "stdio.h"
#include "PriorityQueue.h"
#include <iostream>

Map::Map(int set_width, int set_height) {
	width = set_width;
	height = set_height;
	cities_count = 0;
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
	cities_count++;
}

void Map::AddCity(const int& x, const int& y) {
	String name = FindCityName(x, y);
	City* city = new City(name, { x,y });
	city_map[x][y] = city;
	hashmap.AddKey(city);
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

//void Map::IterateMap(void(Map::* callback)(int, int), bool(Map::* condition)(int, int)) {
//	for (int y = 0; y < height; y++) {
//		for (int x = 0; x < width; x++) {
//
//			if ((this->*condition)(x, y)) {
//				(this->*callback)(x, y);
//			}
//
//		}
//	}
//}

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
	clearer.Reserve(300);
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
	}
	delete[] city1;
	delete[] city2;
}

void Map::ResetVisitedDijkstra(Vector<City*>& clearer) {
	for (City*& city : clearer) {
		city->visited = false;
		city->path.Reset();
	}
}

void Map::StartCommands() {

	int commands_amount;
	int command;
	std::cin >> commands_amount;
	char* city1 = new char[64];
	char* city2 = new char[64];
	getchar();

	for (int i = 0; i < commands_amount; i++) {

		Vector<City*> clearer;
		InputCityName(city1);
		InputCityName(city2);
		command = getchar() - 48;
		getchar();

		if (strcmp(city1, city2) == 0) {
			std::cout << "0" << "\n";
			continue;
		}

		City* start = hashmap[city1];
		City* end = hashmap[city2];

		Dijkstra(start, end, clearer);


		start->path.distance = INF;
		start->path.source = nullptr;
		start->visited = false;

		if (command == 1) {
			std::cout << end->path.distance;
			PrintTrip(end->path.source, start);
			std::cout << "\n";
		}
		else {
			std::cout << end->path.distance << "\n";
		}
		ResetVisitedDijkstra(clearer);
	}
	delete[] city1;
	delete[] city2;
}

void Map::Dijkstra(City* start, City* end, Vector<City*>& clearer) {
	int distance;
	Connection* end_condition = end->GetConnection();

	start->path.distance = 0;
	start->path.source = start;
	start->visited = true;

	Priority_Queue pq(1000);
	PQAdjacent(pq, start, distance);

	Edge current;
	while (!pq.Empty() && !DijkstraEnd(end)) {
		current = pq.Peek();
		clearer.Add(current.destination);

		if (current.destination->path.distance == INF) {
			current.destination->path = current.path;
		}

		current.destination->visited = true;
		pq.Pop();
		PQAdjacent(pq, current.destination, distance);
	}
}

void Map::PQAdjacent(Priority_Queue& pq, City*& start, int& distance) {
	Connection* current = start->GetConnection();
	while (current != nullptr) {
		if (!current->city->visited) {
			distance = start->path.distance + current->distance;
			pq.Enqueue(current->city, start, distance);
		}
		current = current->next;
	}
}

void Map::PrintTrip(City* current, City* source) {
	List<String*> journey;

	while (current != source) {
		journey.PushBack(&current->GetName());
		current = current->path.source;
	}

	journey.PrintBackwards();
}

void Map::LoopLoadCoordinate() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			LoadCoordinate(x, y);

		}
	}
}

void Map::LoopLoadCity() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			if (IsCity(x, y)) {
				LoadCity(x, y);
			}

		}
	}
}

void Map::LoopSearchConnections() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			if (IsCity(x, y)) {
				SearchConnections(x, y);
			}

		}
	}
}

bool Map::DijkstraEnd(City*& end) {
	if (end->visited == true) {
		return true;
	}
	return false;
}
