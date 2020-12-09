#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <queue>


using namespace std;

vector<string> parseInput(string path)
{
	ifstream myfile;
	string line;
	vector<string> inputVector;

	myfile.open(path);

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

map<string, vector<pair<string, int>>> parseRules(vector<string> input)
{
	map<string, vector<pair<string, int>>> rules;

	for (string rule : input) {
		regex colorRx("(.+?) bags contain");
		regex containedInRx("(\\d+) (.+?) bags?[,.]");
		smatch color;
		smatch containedIn;


		regex_search(rule, color, colorRx);
		regex_search(rule, containedIn, containedInRx);
		string container = color[1];
		
		//rules[container] = {};
		for (std::sregex_iterator i = std::sregex_iterator(rule.begin(), rule.end(), containedInRx);
			i != std::sregex_iterator();
			++i) {
			containedIn = *i;
			rules[container].push_back({ containedIn[2], stoi(containedIn[1]) });
			cout << container << " - " << containedIn[2] << " " << containedIn[1] << endl;
		}
	}
	return rules;
}

int countShinyGold(vector<int> rules)
{
	int count = 0;


	return count;
}

int main()
{
	vector<string> rulesInput = parseInput("day7_input.txt");

	map<string, vector<pair<string, int>>> rules = parseRules(rulesInput);

	for (auto rule : rules)
	{
		cout << rule.first << " : " << rule.second[0].first << endl;
	}
	//countShinyGold(rules);
	//cout << "Part 1 - " << result1 << endl;
	//cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}