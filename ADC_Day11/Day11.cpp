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

int modelSeats(vector<string> seatMap, int limit)
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
				if (limit == 4) {
					seatsCount = countSeats(seatMap, i, j);
				}
				else if (limit == 5) {
					seatsCount = countSeatsLineOfSight(seatMap, i, j);
				}

				if (seatMap[i][j] == 'L') {
					
					if (seatsCount == 0)
					{
						currentMap[i][j] = '#';
					}
				}

				if (seatMap[i][j] == '#') {
					if (seatsCount >= limit)
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

int countSeatsLineOfSight(vector<string>& seatMap, int i, int j) {

	int count = 0;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (!(x == 0 && y == 0))
			{
				int rr = i + x;
				int cc = j + y;

				while ((rr >= 0 && rr < seatMap.size()-1 && cc >= 0 && cc < seatMap.size()-1
					&& seatMap[rr][cc] == '.')) {
					rr = rr + x;
					cc = cc + y;
				}
				if (rr >= 0 && rr < seatMap.size()  && cc >= 0 && cc < seatMap.size() && seatMap[rr][cc] == '#') {
					count++;
				}
			}
		}
	}

	return count;
}

int main()
{
	vector<string> input = parseInput("day11_input.txt");

	int result1 = modelSeats(input, 4);
	int result2 = modelSeats(input, 5);
	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}