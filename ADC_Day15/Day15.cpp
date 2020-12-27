#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

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
			stringstream ss(line);
			while (ss.good()) {
				string number;
				getline(ss, number, ',');
				inputVector.push_back(stoi(number));
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return inputVector;
}

int getSequence(int target, vector<int>& startingNumbers)
{
	int result = 0;
	vector<int> numberSequence = startingNumbers;
	map<int, int> alreadyAdded;

	for (int i = 0; i < numberSequence.size() - 1; i++) {
		alreadyAdded.insert(pair<int, int>(numberSequence[i], i));
	}

	for (int i = startingNumbers.size() - 1; i < target; i++)
	{
		if (alreadyAdded.find(numberSequence[i]) == alreadyAdded.end())
		{
			alreadyAdded.insert(pair<int, int>(numberSequence[i], i));
			numberSequence.push_back(0);
		}
		else {
			int difference = i - alreadyAdded.find(numberSequence[i])->second;
			numberSequence.push_back(difference);
			alreadyAdded[numberSequence[i]] = i;
		}
	}

	result = numberSequence[target - 1];

	return result;
}

int main()
{
	vector<int> startingNumbers = parseInput("day15_input.txt");

	int result1 = getSequence(2020, startingNumbers);
	cout << "Part 1 - " << result1 << endl;
	int result2 = getSequence(30000000, startingNumbers); //20 seconds. (Was 15 mins using part 1 method.)
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}