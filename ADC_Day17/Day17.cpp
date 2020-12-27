#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Cube.h"

using namespace std;

vector<string> parseInput(string path)
{
	ifstream myfile;
	string line;
	vector<string> inputVector;

	myfile.open(path);

	int count = 0;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			inputVector.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return inputVector;
}

// Part 1. 
int sixCycleCount(vector<string> &input)
{
	vector<Cube> cubes;
	int space = input.size() / 2;
	//If 3 then 1. if 8 then 4. 

	//Parse input into z = 0;
	for (int k = -1; k < 2; k++) {
		for (int j = 0; j < input.size(); j++) { //y
			for (int i = 0; i < input.size(); i++) {//x
				if (input[j][i] == '#' && k == 0)
					cubes.push_back(Cube(i, j, k, true));
				else
					cubes.push_back(Cube(i, j, k, false));
			}
		}
	}

	//Pad surroundings with inactive cells;
	for (int j = 0; j < input.size(); j++) { //y
		for (int i = 0; i < input.size(); i++) {//x
			cubes.push_back(Cube(i, j, -1, false));
		}
	}
	
	//Get Neighbour count

	//Apply rules

	//Repeat 6 times

	//Count cubes

	int cubeCount = 0;
	for (Cube cube : cubes) {
		if (cube.active == true)
			cubeCount++;
	}

	return cubeCount;
}

int main()
{
	vector<string> input = parseInput("day17_input.txt");

	int result1 = sixCycleCount(input);

	cout << "Part 1 - " << result1 << endl;
	//cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}