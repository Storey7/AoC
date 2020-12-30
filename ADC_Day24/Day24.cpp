#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int gameOfLife(set<vector<int>> black);

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

pair<int, int> countBlackTiles(vector<string>& input)
{
	vector<int> coords;
	set<vector<int>> black;
	int tileCount = 0;
	
	for (string line : input)
	{
		int x = 0;
		int y = 0;
		int z = 0;

		while (line.length() > 0) {
			if (line.rfind("e", 0) == 0) {
				x += 1;
				y -= 1;
				line = line.substr(1, line.npos);
			}
			else if (line.rfind("se", 0) == 0) {
				y -= 1;
				z += 1;
				line = line.substr(2, line.npos);
			}
			else if (line.rfind("sw", 0) == 0) {
				x -= 1;
				z += 1;
				line = line.substr(2, line.npos);
			}
			else if (line.rfind("w", 0) == 0) {
				x -= 1;
				y += 1;
				line = line.substr(1, line.npos);
			}
			else if (line.rfind("nw", 0) == 0) {
				z -= 1;
				y += 1;
				line = line.substr(2, line.npos);
			}
			else if (line.rfind("ne", 0) == 0) {
				x += 1;
				z -= 1;
				line = line.substr(2, line.npos);
			}
		}
		vector<int> coords{ x,y,z };
		if (black.find(coords) != black.end()) {
			black.erase(coords);
		}
		else {
			black.insert(coords);
		}
	}

	int part2 = gameOfLife(black);
	
	tileCount = black.size();
	return make_pair(tileCount, part2);
}

int countNeighbours(vector<int> coords, set<vector<int>>& black) {
	int blackTiles = 0;
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			for (int dz = -1; dz <= 1; dz++) {
				if (black.find(vector<int>{coords[0] + dx, coords[1] + dy, coords[2] + dz}) != black.end()) {
					blackTiles++;
				}
			}
		}
	}
	return blackTiles;
}

int gameOfLife(set<vector<int>> black)
{
	int blackTiles = 0;
	set<vector<int>> prevBlack = black;
	set<vector<int>> check;

	
	set<vector<int>>::iterator itr;

	for (itr = prevBlack.begin(); itr != prevBlack.end(); ++itr)
	{
		vector<int> coords = *itr;
		check.insert(coords);
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				for (int dz = -1; dz <= 1; dz++) {
					check.insert(vector<int>{coords[0] + dx, coords[1] + dy, coords[2] + dz});
				}
			}
		}
	}
	for (itr = check.begin(); itr != check.end(); ++itr)
	{
		vector<int> coords = *itr;
		int blackTiles = countNeighbours(coords, black);
		
	}

	return blackTiles;

}

int main()
{
	vector<string> input = parseInput("day24_input.txt");

	pair<int, int> result = countBlackTiles(input);
	cout << "Part 1 - " << result.first << endl;
	cout << "Part 2 - " << result.second << endl;

	cin.get();
	return 0;
}