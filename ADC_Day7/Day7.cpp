#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <queue>
#include <set>


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

//This is a pretty strange function and I will come back and fix it some day. 
// It makes 2 maps of bag - parents and of bag - contents
unordered_map<string, vector<pair<string, int>>> parseRules(vector<string> input, unordered_map<string, vector<string>> &parents)
{
	unordered_map<string, vector<pair<string, int>>> rules;

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
			
			parents[containedIn[2]].push_back(container);
			rules[container].push_back({ containedIn[2], stoi(containedIn[1]) });
		}
	}
	return rules;
}

int countParents(unordered_map<string, vector<string>> &parents)
{
	int count = 0;
	set<string> seen;
	deque<string> q;

	q.push_back("shiny gold");

	while (q.size() > 0)
	{
		string x = q.front(); q.pop_front();
		if (seen.find(x) != seen.end()) {
			continue;
		}
		seen.insert(x);
		for (string y : parents[x]) {
			q.push_back(y);
		}
	}

	return seen.size() - 1;
}

//This recursive algorithm is very much taken from Jonathan Paulson's solution. 
//https://github.com/jonathanpaulson/AdventOfCode/blob/master/2020/7.py
//The first time I had to use help!
int size(string bag, unordered_map<string, vector<pair<string, int>>> &rules)
{
	int ans = 1;
	for (pair<string, int> child : rules[bag]) {
		ans += child.second * size(child.first, rules);
	}
	return ans;
}

int main()
{
	vector<string> rulesInput = parseInput("day7_input.txt");
	unordered_map<string, vector<string>> parents;
	unordered_map<string, vector<pair<string, int>>> rules = parseRules(rulesInput, parents);

	int result1 = countParents(parents);
	int result2 = size("shiny gold", rules);

	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2-1 << endl;

	cin.get();
	return 0;
}