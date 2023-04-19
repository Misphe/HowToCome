#pragma once
class Map {
private:
	char** map;
	int width;
	int height;
public:
	Map(int set_width, int set_height);
	void LoadMap();
	void Print();
};

