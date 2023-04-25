#pragma once
#define NULL_POS {-1,-1}

struct Position {
	int x;
	int y;
};

struct QueuePos {
	Position position;
	int distance;
};