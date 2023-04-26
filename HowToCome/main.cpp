#include <iostream>
#include "Defines.h"
#include "String.h"
#include "Functions.h"
#include "Map.h"
#include "Hashmap.h"
#include "Queue.h"
#include "Vector.h"
#include <chrono>
#define TEST 1

int main() {

	int width, height, k, commands;
	std::cin >> width >> height;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	{
		Map map(width, height);
		map.IterateMap(&Map::LoadCoordinate, &Map::ReturnTrue);

		if (TEST) {
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			std::cout << "Time taken: " << duration << " microseconds" << std::endl;
		}

		map.IterateMap(&Map::LoadCity, &Map::IsCity);

		if (TEST) {
			end = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			std::cout << "Time taken: " << duration << " microseconds" << std::endl;
		}

		map.IterateMap(&Map::SearchConnections, &Map::IsCity);

		if (TEST) {
			end = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			std::cout << "Time taken: " << duration << " microseconds" << std::endl;
		}

		map.LoadFlights();

		if (TEST){
			end = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			std::cout << "Time taken: " << duration << " microseconds" << std::endl;
		}

		//map.PrintHashmap();
	}

	std::cout << "finished";

	return 0;


	//hashmap.Print();
}