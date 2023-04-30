#pragma once
#define NULL_POS {-1,-1}
#define DIGITGROUP 5
#define BASE 26
#define INF -1

struct Position {
	int x;
	int y;
};

struct QueuePos {
	Position position;
	int distance;
};