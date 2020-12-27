#pragma once

class Cube {
public:

	Cube(int _x, int _y, int _z, bool state);
	~Cube();

	int x, y, z;
	bool active;

	int applyRules();
	int countNeighbours();
};