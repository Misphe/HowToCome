#include "Functions.h"

char** CreateMap(int width, int height) {
	char** map = new char* [width];
	for (int i = 0; i < height; i++) {
		map[i] = new char[height];
	}
	return map;
}