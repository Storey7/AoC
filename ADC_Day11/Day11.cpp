#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int countSeats(vector<string>& seatMap, int i, int j);
int countSeatsLineOfSight(vector<string>& seatMap, int i, int j);

vector<string> parseInput(string path)
{
	ifstream myfile;
	string line;
	vector<string> inputVector;
	string padding = "";

	myfile.open(path);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			string insertString;
			insertString.append(".");
			insertString.append(line);
			insertString.append(".");
			inputVector.push_back(insertString);
		}

		for (int i = 0; i < line.length()+2; i++)
		{
			padding.append(".");
		}

		inputVector.emplace(inputVector.begin(), padding); //This is terrible, but at least the array is only small. 
		inputVector.push_back(padding);
		myfile.close();
	}
	else cout << "Unable to open file";

	return inputVector;
}

int modelSeats(vector<string> seatMap)
{
	vector<string> currentMap = seatMap;
	vector<string> prevMap;
	int occupied = 0;
	int seatsCount;

	while (currentMap != prevMap) {
		prevMap = currentMap;
		for (int i = 1; i < seatMap.size() - 1; i++) {
			for (int j = 1; j < seatMap[i].size() - 1; j++)
			{
				if (seatMap[i][j] == 'L') {
					seatsCount = countSeats(seatMap, i, j);
					if (seatsCount == 0)
					{
						currentMap[i][j] = '#';
					}
				}

				if (seatMap[i][j] == '#') {
					seatsCount = countSeats(seatMap, i, j);
					if (seatsCount >= 4)
					{
						currentMap[i][j] = 'L';
					}
				}
			}
		}
		seatMap = currentMap;
	}


	for (int i = 1; i < seatMap.size() - 1; i++) {
		for (int j = 1; j < seatMap[i].size() - 1; j++) {
			if (seatMap[i][j] == '#')
				occupied++;
		}
	}

	return occupied;
}

int countSeats(vector<string>& seatMap, int i, int j) {

	int count = 0;

	for (int x = i-1; x <= i + 1; x++) {
		for (int y = j-1; y <= j + 1; y++) {
			if (x == i && y == j)
				continue;

			if (seatMap[x][y] == '#') {
				count++;
			}
		}
	}
	return count;
}

int modelSeatsLineOfSight(vector<string> seatMap)
{
	vector<string> currentMap = seatMap;
	vector<string> prevMap;
	int occupied = 0;
	int seatsCount;

	while (currentMap != prevMap) {
		prevMap = currentMap;
		for (int i = 1; i < seatMap.size() - 1; i++) {
			for (int j = 1; j < seatMap[i].size() - 1; j++)
			{
				if (seatMap[i][j] == 'L') {
					seatsCount = countSeatsLineOfSight(seatMap, i, j);
					if (seatsCount == 0)
					{
						currentMap[i][j] = '#';
					}
				}

				if (seatMap[i][j] == '#') {
					seatsCount = countSeatsLineOfSight(seatMap, i, j);
					if (seatsCount >= 5)
					{
						currentMap[i][j] = 'L';
					}
				}
			}
		}
		seatMap = currentMap;

		for (auto line : seatMap) {
			cout << line << endl;
		}
		cout << endl;
	}


	for (int i = 1; i < seatMap.size() - 1; i++) {
		for (int j = 1; j < seatMap[i].size() - 1; j++) {
			if (seatMap[i][j] == '#')
				occupied++;
		}
	}

	return occupied;
}

int countSeatsLineOfSight(vector<string>& seatMap, int i, int j) {

	int count = 0;

	for (int x = i-1; x > 0; x--) {
		if (seatMap[x][j] == '#') {
			count++;
			break;
		}
	}
	for (int y = i-1; y > 0; y--) {
		if (seatMap[i][y] == '#') {
			count++;
			break;
		}
	}

	for (int x = i+1; x < seatMap.size() - 1; x++) {
		if (seatMap[x][j] == '#') {
			count++;
			break;
		}
	}
	for (int y = j+1; y < seatMap.size() - 1; y++) {
		if (seatMap[i][y] == '#') {
			count++;
			break;
		}
	}

	for (int x = i-1; x > 0; x--){
		if (seatMap[x][x] == '#') {
			count++;
			break;
		}
	}
	for (int y = j-1; y > 0; y--) {
		if (seatMap[y][y] == '#') {
			count++;
			break;
		}
	}
	for (int x = i+1; x < seatMap.size()-1; x++) {
		if (seatMap[x][x] == '#') {
			count++;
			break;
		}
	}
	for (int y = j + 1; y < seatMap[0].length()-1; y++) {
		if (seatMap[y][y] == '#') {
			count++;
			break;
		}
	}
	return count;
}

int main()
{
	vector<string> input = parseInput("day11_input.txt");

	//int occupied = modelSeats(input);
	int result2 = modelSeatsLineOfSight(input);
	//cout << "Part 1 - " << occupied << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}