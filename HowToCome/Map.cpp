#include "Map.h"
#include <iostream>

Map::Map(int set_width, int set_height) {
	width = set_width;
	height = set_height;
	map = new char* [width];
	for (int i = 0; i < width; i++) {
		map[i] = new char[height];
	}
}

void Map::LoadMap() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cin>> map[j][i];
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
