//How many passwords are valid according to their policies?
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool checkPolicyCount(string policy) {

	//Would've been cleaner as regex. Will redo later. 
	bool valid = false;
	int min, max;
	char letter;
	string password;
	string substring;
	int count = 0;

	size_t pos = policy.find("-");
	min = stoi(policy.substr(0, pos));
	policy.erase(0, pos + 1);

	pos = policy.find(" ");
	max = stoi(policy.substr(0, pos));
	policy.erase(0, pos + 1);

	letter = policy[0];
	policy.erase(0, 3);

	password = policy;

	for (int i = 0; i < password.length(); i++)
	{
		if (password[i] == letter) {
			count++;
		}
	}

	if (count >= min && count <= max)
	{
		valid = true;
	}

	return valid;
}

bool checkPolicyPosition(string policy)
{
	bool valid = false;
	int min, max;
	char letter;
	string password;
	string substring;

	size_t pos = policy.find("-");
	min = stoi(policy.substr(0, pos));
	policy.erase(0, pos + 1);

	pos = policy.find(" ");
	max = stoi(policy.substr(0, pos));
	policy.erase(0, pos + 1);

	letter = policy[0];
	policy.erase(0, 3);

	password = policy;

	if ((password[min-1] == letter) != (password[max-1] == letter))
		valid = true;

	return valid;
}

vector<string> parseFile(string path) {
	string line;
	ifstream myfile;
	myfile.open(path);
	vector<string> result;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//cout << line << '\n';
			result.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return result;
}

int main()
{
	int validPoliciesCount = 0;
	int validPoliciesPosition = 0;
	vector<string> policies = parseFile("day2_input.txt");

	int count = 0;

	for (auto line : policies)
	{
		if (checkPolicyCount(line) == true)
			validPoliciesCount++;
		if (checkPolicyPosition(line) == true)
			validPoliciesPosition++;
	}
	cout << "Part 1 - Valid Policies by count: " << validPoliciesCount << endl;
	cout << "Part 2 - Valid Policies by position: " << validPoliciesPosition << endl;

	cin.get();
	return 0;
}