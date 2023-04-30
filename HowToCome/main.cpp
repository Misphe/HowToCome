#include <iostream>
#include "Defines.h"
#include "String.h"
#include "Functions.h"
#include "Map.h"
#include "Hashmap.h"
#include "Queue.h"
#include "Vector.h"
#include "PriorityQueue.h"
#include <chrono>
#define TEST 0

int main() {

	int width, height, k, commands;
	std::cin >> width >> height;

	{
		Map map(width, height);

		map.LoopLoadCoordinate();

		map.LoopLoadCity();

		map.LoopSearchConnections();

		map.LoadFlights();

		map.StartCommands();
	}

	return 0;
}