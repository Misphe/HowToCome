#include "Functions.h"

char** CreateMap(int width, int height) {
	char** map = new char* [width];
	for (int i = 0; i < height; i++) {
		map[i] = new char[height];
	}
	return map;
}

bool CityCharacter(const char& character) {
	if ((character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9')) {
		return true;
	}
	return false;
}

// unused
String CreateFakeName(int number) {
	String result = "ABC";
	while (number != 0) {
		char tmp = number % 10 + '0';
		result += tmp;
		number /= 10;
	}
	return result;
}

void InputCityName(char*& city) {
	int i = 0;
	while ((city[i] = getchar()) != ' ') {
		i++;
	}
	city[i] = '\0';
}

void InputDistance(int& distance) {
	int a;
	while ((a = getchar()) != 10) {
		a = a - '0';
		distance = distance * 10 + a;
	}
}