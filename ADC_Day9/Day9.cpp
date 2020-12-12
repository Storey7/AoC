#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<long long int> parseInput(string path)
{
	ifstream myfile;
	string line;
	vector<long long int> inputVector;

	myfile.open(path);

	int count = 0;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			inputVector.push_back(stoll(line));
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return inputVector;
}

int checkSums(vector<long long int> cypher, int preamble)
{
	int validChecksum = -1;
	set<long long int> twoSumMap;
	
	for (long long int i = preamble; i < cypher.size(); i++)
	{
		twoSumMap.clear();
		for (long long int j = i - preamble; j < i; j++)
		{
			twoSumMap.insert(cypher[j]);
			//cout << cypher[j] << endl;
		}
		set<long long int>::iterator itr = twoSumMap.begin();

		while (itr != twoSumMap.end())
		{
			long long int complement = cypher[i] - *itr;
			if (twoSumMap.find(complement) != twoSumMap.end()) {
				//cout << *itr << " : " << complement << endl;
				break;
			}
			itr++;
			//return (cypher[i]);
		}
		if (itr == twoSumMap.end()) {
			cout << i << " " << cypher[i] << " " << endl;
			return(cypher[i]);
		}
	}
	return validChecksum;
}

int findWeakness(vector<long long int> cypher, long long int target)
{
	int targetIndex = 0;
	int searchIndex;

	//Very crude search.
	for (int i = 0; i < cypher.size(); i++)
	{
		if (cypher[i] == target) {
			cout << i << endl;
			targetIndex = i;
			break;
		}
	}
	searchIndex = targetIndex - 2;

	int sum = 0;
	while(searchIndex >= 0) {
		for (int i = searchIndex; i < targetIndex; i++) {
			sum += cypher[i];

			if (sum > target)
				break;
			if (sum == target) {
				int min = cypher[searchIndex];
				int max = cypher[i];

				cout << searchIndex << " " << i << endl;

				for (int k = searchIndex; k < i; k++) {
					if (cypher[k] > max)
						max = cypher[k];
					if (cypher[k] < min)
						min = cypher[k];
				}
				return (max+min);
			}
		}

		sum = 0;
		searchIndex--;
	}
	return 0;
}

int main()
{
	vector<long long int> xMasCypher = parseInput("day9_input.txt");

	int result1 = checkSums(xMasCypher, 25);
	int result2 = findWeakness(xMasCypher, result1);

	cout << "Part 1 : " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}