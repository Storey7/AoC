#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <regex>

using namespace std;

vector<string> parseInput(string path)
{
	ifstream myfile;
	string line;
	string passport;
	vector<string> passports;

	myfile.open(path);

	int count = 0;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == "")
			{
				passports.push_back(passport);
				passport.clear();
			}

			if(passport.length() != 0)
				passport.append(" ");
	
			passport.append(line);			
		}
		passports.push_back(passport);

		myfile.close();
	}
	else cout << "Unable to open file";

	return passports;
}
bool validPassport(string passport)
{
	bool validPassport = true;
	stringstream ss(passport);
	string token;
	unordered_set<string> keywords;
	vector<string> validKeywords = {
		"byr",
		"iyr",
		"eyr",
		"hgt",
		"hcl",
		"ecl",
		"pid",
	};

	//Tokenise by space and get first 3 chars
	while(ss >> token)
	{
		keywords.insert(token.substr(0, 3));
	}

	//Compare to valid data.
	for (string keyword : validKeywords)
	{
		if (keywords.find(keyword) == keywords.end())
		{
			validPassport = false;
			return validPassport;
		}
	}
	return validPassport;
}

bool validatedPassport(string passport)
{
	stringstream ss(passport);
	string token;
	string key;
	string data;
	map<string, string> dataMap;
	map<string, string>::iterator itr;
	unordered_set<string> colors;
	colors.insert("amb");
	colors.insert("blu");
	colors.insert("brn");
	colors.insert("gry");
	colors.insert("grn");
	colors.insert("hzl");
	colors.insert("oth");

	if (!validPassport(passport))
		return false;

	//Tokenise by space and get first 3 chars
	while (ss >> token)
	{
		key = token.substr(0, 3);
		data = token.substr(4, token.length());
		dataMap.insert(pair<string, string>(key, data));
	}

	for (itr = dataMap.begin(); itr != dataMap.end(); ++itr) {
		if (itr->first == "byr") {
			int byr = stoi(itr->second);
			if (byr < 1920 || byr > 2002) {
				return false;
			}
		}
		else if (itr->first == "iyr")
		{
			int iyr = stoi(itr->second);
			if (iyr < 2010 || iyr > 2020) {
				return false;
			}
		}
		else if (itr->first == "eyr")
		{
			int eyr = stoi(itr->second);
			if (eyr < 2020 || eyr > 2030) {
				return false;
			}
		}
		else if (itr->first == "hgt")
		{
			regex rx("([0-9]+)(cm|in)");
			smatch m;
			string myData = itr->second;
			if (!regex_match(myData, rx)) {
				return false;
			}
			regex_search(myData, m, rx);

			if (m[2] == "cm") {
				int height = stoi(m[1]);
				if (height < 150 || height > 193)
					return false;
			}
			if (m[2] == "in") {
				int height = stoi(m[1]);
				if (height < 59 || height > 76)
					return false;
			}
		}
		else if (itr->first == "hcl")
		{
			regex rx("#[0-9a-f]{6}");
			string myData = itr->second;
			if (!regex_match(itr->second, rx)) {
				return false;
			}
		}
		else if (itr->first == "ecl")
		{
			string color = itr->second;
			if (colors.find(color) == colors.end()) {
				return false;
			}
		}
		else if (itr->first == "pid")
		{
			regex rx("[0-9]{9}");
			string myData = itr->second;
			if (!regex_match(itr->second, rx)) {
				return false;
			}
		}
	}

	return true;
}

int main()
{
	vector<string> passports = parseInput("day4_input.txt");
	int countValid = 0;
	int countValidated = 0;
	for (auto line : passports) {
		if (validPassport(line))
			countValid++;
		if (validatedPassport(line))
			countValidated++;
	}

	cout << "Part 1 - Valid Passport Count: " << countValid << endl;
	cout << "Part 2 - Validated Passport Count: " << countValidated << endl;

	cin.get();
	return 0;
}