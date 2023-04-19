#include <iostream>
#include "String.h"
#include "Functions.h"
#include "Map.h"
#include "Hashmap.h"

int main() {
	int width, height, k, commands;
	std::cin >> width >> height;

	Map map(width, height);
	map.LoadMap();
	map.Print();

	String test = "haha";

	Hashmap hashmap;
	City city1(String("hihi"));
	hashmap.AddKey(city1);
	std::cout << hashmap.GetValue(city1).GetName() << "\n";

	City city2(String("ihih"));
	City city3(String("iasdih"));
	hashmap.AddKey(city2);
	std::cout << hashmap.GetValue(city1).GetName() << "\n";
	std::cout << hashmap.GetValue(city2).GetName() << "\n";
	std::cout << hashmap.GetValue(city3).GetName() << "\n";
	std::cout << "end\n";


	
}