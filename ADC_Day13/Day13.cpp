#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using ll = uint64_t;
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

int getBusID(vector<string> input)
{
	int departureTime = stoi(input[0]);
	vector<int> buses;
	map<int, int> timeMap;

	for (int i = 1; i < input.size(); i++)
	{
		stringstream ss(input[i]);
		while (ss.good())
		{
			string busTime;
			getline(ss, busTime, ',');
			if (busTime.compare("x") == 0)
				continue;
			buses.push_back(stoi(busTime));	
		}
	}
	int nextTime = 0;
	int minTime = 2000000;

	for (int bus : buses)
	{
		int closestTime = departureTime / bus;
		nextTime = (bus * closestTime) + bus;

		timeMap.insert(pair<int, int>(bus, nextTime));
	}

	map<int, int>::iterator itr;
	int minDiff = 1000;
	for (itr = timeMap.begin(); itr != timeMap.end(); itr++)
	{
		int diff = itr->second - departureTime;
		if (diff < minDiff)
		{
			minDiff = diff;
		}
	}

	for (itr = timeMap.begin(); itr != timeMap.end(); itr++)
	{
		if (itr->second - departureTime == minDiff)
		{
			return (itr->first * minDiff);
		}
	}

	return 0;
}

ll getEarliestTimestamp(vector<string> input)
{
	map<int,int> buses;
	vector<pair<int, int>> constraints;
	for (int i = 1; i < input.size(); i++)
	{
		int index = 0;
		int b;
		stringstream ss(input[i]);
		while (ss.good())
		{
			string busTime;
			getline(ss, busTime, ',');
			if (busTime.compare("x") == 0) {
				index++;
				continue;
			}

			b = stoi(busTime);
			buses.insert(pair<int,int>(index, b));
			constraints.push_back(pair<int, int>(abs((b - index) % b), b));
			index++;
		}
	}
	return 0;
}

int main()
{
	vector<string> input = parseInput("day13_input.txt");

	int result1 = getBusID(input);
	cout << "Part 1 - " << result1 << endl;
	ll result2 = getEarliestTimestamp(input);
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}