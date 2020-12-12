#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

unsigned long long int getChainCount(int i, vector<int>& adapters, map<int, unsigned long long int>& storedValues);

vector<int> parseInput(string path)
{
	ifstream myfile;
	string line;
	vector<int> inputVector;

	myfile.open(path);

	int count = 0;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			inputVector.push_back(stoi(line));
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return inputVector;
}

map<string, int> getDifferences(vector<int> adapters)
{
	map<string, int> diffs;
	diffs.insert(pair<string, int>("ones", 0) );
	diffs.insert(pair<string, int>("threes", 0));
	adapters.push_back(0);

	sort(adapters.begin(), adapters.end());

	int i = 0;
	for ( i = 0; i < adapters.size()-1; i++) {
		int difference = adapters[i + 1] - adapters[i];
		if (difference == 3) {
			diffs["threes"]++;
		}
		if (difference == 1) {
			diffs["ones"]++;
		}
	}

	diffs["threes"]++;

	return diffs;
}

unsigned long long int getArrangments(vector<int> adapters)
{
	map<int, unsigned long long int> storedValues;
	adapters.push_back(0);
	sort(adapters.begin(), adapters.end());
	adapters.push_back(adapters[adapters.size() - 1] + 3);

	unsigned long long int result = getChainCount(0, adapters, storedValues);
	return result;
}


//Dynamic programming solution. 
unsigned long long int getChainCount(int i, vector<int> &adapters, map<int, unsigned long long int> &storedValues) 
{
	if (i == adapters.size()-1)
		return 1;
	if (storedValues.find(i) != storedValues.end())
		return storedValues[i];

	unsigned long long int ans = 0;
	for (int j = i + 1; j < adapters.size(); j++) {
		if (adapters[j] - adapters[i] <= 3) {
			ans += getChainCount(j, adapters, storedValues);
		}
	}
	storedValues[i] = ans;
	return ans;
}

int main()
{
	vector<int> input = parseInput("day10_input.txt");

	map<string, int> diffs = getDifferences(input);
	unsigned long long int result2 = getArrangments(input);

	cout << diffs["ones"] << " " << diffs["threes"] << endl;
	int result1 = diffs["ones"] * diffs["threes"];
	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}