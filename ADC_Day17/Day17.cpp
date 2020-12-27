#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

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
	set<vector<int>> on;
	set<vector<int>> check;
	vector<int> coords;
	int cubeCount = 0;
	int row = 0;
	
	for (int r = 0; r < input.size(); r++) {
		for (int c = 0; c < input[r].size(); c++) {
			if (input[r][c] == '#') {
				coords = { r, c, 0 };
				on.insert(coords);
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		for (vector<int> cube : on) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						vector<int> toBeChecked = { cube[0] + x, cube[1] + y, cube[2] + z };
						check.insert(toBeChecked);
					}
				}
			}
		}

		set<vector<int>> newOn; // wait till the end to change the cubes to on/off.

		for (vector<int> cube : check) {
			int count = 0;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						if (x != 0 || y != 0 || z != 0) {
							if (on.find({ cube[0] + x, cube[1] + y, cube[2] + z }) != on.end()) {
								count++;
							}
						}
					}
				}
			}
			if ((on.find(cube) == on.end()) && count == 3) {
				newOn.insert(cube);
			}
			if ((on.find(cube) != on.end()) && (count == 2 || count == 3)) {
				newOn.insert(cube);
			}
		}

		on = newOn;
	}


	return on.size();
}

// Part 2. 
int sixCycleCount4D(vector<string>& input)
{
	set<vector<int>> on;
	set<vector<int>> check;
	vector<int> coords;
	int cubeCount = 0;
	int row = 0;

	for (int r = 0; r < input.size(); r++) {
		for (int c = 0; c < input[r].size(); c++) {
			if (input[r][c] == '#') {
				coords = { r, c, 0, 0};
				on.insert(coords);
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		for (vector<int> cube : on) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						for (int w = -1; w <= 1; w++) {
							vector<int> toBeChecked = { cube[0] + x, cube[1] + y, cube[2] + z, cube[3] + w };
							check.insert(toBeChecked);
						}
					}
				}
			}
		}

		set<vector<int>> newOn; // wait till the end to change the cubes to on/off.

		for (vector<int> cube : check) {
			int count = 0;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						for (int w = -1; w <= 1; w++) {
							if (x != 0 || y != 0 || z != 0 || w != 0) {
								if (on.find({ cube[0] + x, cube[1] + y, cube[2] + z, cube[3] + w}) != on.end()) {
									count++;
								}
							}
						}
					}
				}
			}
			if ((on.find(cube) == on.end()) && count == 3) {
				newOn.insert(cube);
			}
			if ((on.find(cube) != on.end()) && (count == 2 || count == 3)) {
				newOn.insert(cube);
			}
		}

		on = newOn;
	}


	return on.size();
}

int main()
{
	vector<string> input = parseInput("day17_input.txt");

	int result1 = sixCycleCount(input);
	int result2 = sixCycleCount4D(input);

	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}