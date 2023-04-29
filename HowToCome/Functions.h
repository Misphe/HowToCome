#pragma once
#include <iostream>
#include "String.h"

char** CreateMap(int width, int height);

bool CityCharacter(const char& character);


// unused
String CreateFakeName(int number);

void InputCityName(char*& city);
void InputDistance(int& distance);

template <typename T>
void Swap(T& first, T& second) {
	T tmp = first;
	first = second;
	second = tmp;
}
