#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>
#include <cctype>

using namespace std;

vector<string> readFile(string path)
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

void parseInput(vector<string>& input, map<int, string>& rules, vector<string>& messages)
{
	int mode = 0;
	for (string line : input) {
		if (line.compare("") == 0) {
			mode = 1;
		}
		if (mode == 0) {
			regex rx("([0-9]+)(: )(.+)");
			smatch m;
			regex_search(line, m, rx);

			int ruleNumber = stoi(m[1]);
			string rule = m[3];

			if (rule.find('"') != string::npos) {
				rule = rule[1];
			}

			rules[ruleNumber] = rule;
		}
		else if (mode == 1) {
			messages.push_back(line);
		}
	}
}

int applyRules(map<int, string>& rules, vector<string>& messages) {
	int count = 0;

	regex rx("([\\d]+)");
	string regExpression = rules[0];

	while (regex_search(regExpression, rx))
	{
		smatch m;
		regex_search(regExpression, m, rx);
		string firstDigit = m[1];
		string replacer = rules[stoi(firstDigit)];
		stringstream newTerm;

		if (replacer.compare("a") != 0 && replacer.compare("b") != 0) {
			newTerm << "[" << replacer << "]";
		}
		else {
			newTerm << replacer;
		}

		regExpression = regex_replace(regExpression, regex(firstDigit), newTerm.str());
	}

	regExpression.erase(std::remove_if(regExpression.begin(), 
							regExpression.end(), 
							[](unsigned char x){return std::isspace(x);}), 
		regExpression.end());

	//Colons breaking things
	regex finalRule(regExpression);
	smatch m;

	for (string message : messages) {
		if (regex_search(message, finalRule)) {
			count++;
		}
	}

	return count;
}

int main()
{
	vector<string> input = readFile("day19_input.txt");
	map<int, string> rules;
	vector<string> messages;

	parseInput(input, rules, messages);

	int result1 = applyRules(rules, messages);
	//cout << "Part 1 - " << result1 << endl;
	//cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}