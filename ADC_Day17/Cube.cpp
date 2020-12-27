#include "Cube.h"
#pragma once

Cube::Cube(int _x, int _y, int _z, bool state): x(_x), y(_y), z(_z), active(state)
{

}

Cube::~Cube()
{
}

int Cube::applyRules()
{
	return 0;
}

int Cube::countNeighbours()
{
	return 0;
}
