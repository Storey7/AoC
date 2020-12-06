#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <map>

using namespace std;

vector<string> parseInput(string path)
{
	ifstream myfile;
	string line;
	vector<string> groupAnswers;
	string personAnswer;

	myfile.open(path);

	int count = 0;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == "")
			{
				groupAnswers.push_back(personAnswer);
				personAnswer.clear();
			}

			
			if (personAnswer.length() != 0)
				personAnswer.append(" ");
			

			personAnswer.append(line);
		}
		groupAnswers.push_back(personAnswer);

		myfile.close();	
	}
	else cout << "Unable to open file";

	return groupAnswers;
}

int countUniqueAnswers(string groupAnswer)
{
	int count = 0;
	set<char> answerSet;

	for (int i = 0; i < groupAnswer.length(); i++)
		if(groupAnswer[i] != ' ')
			answerSet.insert(groupAnswer[i]);

	count = answerSet.size();

	return count;
}

int countUnanimous(string groupAnswer) {
	int count = 0;
	int personCount = 0;
	map<char, int> answerMap;
	string personAnswer;
	istringstream ss(groupAnswer);

	while (getline(ss, personAnswer, ' '))
	{
		personCount++;
		//cout << personCount << " : " << personAnswer << endl;
		for (int i = 0; i < personAnswer.length(); i++) {
			if (answerMap.find(personAnswer[i]) == answerMap.end())
			{
				answerMap.insert(pair<char, int>(personAnswer[i], 1));
			}
			else
			{
				answerMap[personAnswer[i]]++;
			}
		}
	}

	for (auto itr = answerMap.begin(); itr != answerMap.end(); itr++)
	{
		//cout << itr->first << " : " << itr->second << endl;
		if (itr->second == personCount)
			count++;
	}

	return count;
}

int getSumUnique(vector<string> groupAnswers)
{
	int sum = 0;

	for (string line : groupAnswers)
	{
		sum += countUniqueAnswers(line);
	}

	return sum;
}

int getSumUnanimous(vector<string> groupAnswers)
{
	int sum = 0;

	for (string line : groupAnswers)
	{
		sum += countUnanimous(line);
	}

	return sum;
}

int main()
{
	vector<string> input = parseInput("day6_input.txt");

	int result1 = getSumUnique(input);
	int result2 = getSumUnanimous(input);

	cout << "\nPart 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}