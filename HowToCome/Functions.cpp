#include "Functions.h"

char** CreateMap(int width, int height) {
	char** map = new char* [width];
	for (int i = 0; i < height; i++) {
		map[i] = new char[height];
	}
	return map;
}

bool CityCharacter(const char& character) {
	if (character >= 'A' && character <= 'Z') {
		return true;
	}
	return false;
}

String CreateFakeName(int number) {
	String result = "ABC";
	while (number != 0) {
		char tmp = number % 10 + '0';
		result += tmp;
		number /= 10;
	}
	return result;
}