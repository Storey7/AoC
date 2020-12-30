#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <istream>
#include <numeric>

using namespace std;
using ll = int64_t;

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

//Largely taken from https://github.com/janpipek/advent-of-code-2020/blob/dev/advent_of_code/day18.cpp
ll applyOperator(char op, ll value1, ll value2) {
	
	// Apply
	if (op == '+') {
		return value1 + value2;
	}
	else if (op == '*') {
		return value1 * value2;
	}
	else {
		return value2;
	}
}

ll evalLine(istringstream &stream)
{
	ll value = 0;

	char currentOperator = ' ';
	char token;
	while (stream.peek() != EOF)
	{
		stream.read(&token, 1);

		if (token == '+' || token == '*') {
			currentOperator = token;
		}
		else if (token == '(') {
			value = applyOperator(currentOperator, value, evalLine(stream));
		}
		else if (token == ')') {
			return value;
		}
		else if (token == ' ') {
			continue;
		}
		else {
			ll number = token - '0';
			value = applyOperator(currentOperator, value, number);
		}
		
	}

	return value;
}

ll product(vector<ll>& numbers) {
	return accumulate(numbers.cbegin(), numbers.cend(), (ll) 1, std::multiplies<ll>());
}

ll evalLine2(istringstream& stream)
{
	ll currentFactor = 0;
	vector<ll> factors{};

	char token;
	while (stream.peek() != EOF)
	{
		stream.read(&token, 1);

		if (token == '*') {
			factors.push_back(currentFactor);
			currentFactor = 0;
		}
		else if (token == ')') {
			break;
		}
		else if ((token == ' ') || (token == '+')) {
			continue;
		}
		// Number of subexpression
		else {
			ll number = (token == '(') ? evalLine2(stream) : string("0123456789").find(token);
			if (number == string::npos) {
				cout << "Ya done fucked up" << endl;
			}
			currentFactor += number;
		}
	}
	if (currentFactor) {
		factors.push_back(currentFactor);
	}

	return product(factors);
}

int main()
{
	vector<string> input = parseInput("day18_input.txt");
	ll result1 = 0;
	for (string line : input) {
		istringstream stream(line);
		result1 += evalLine(stream);
	}

	ll result2 = 0;
	for (string line : input) {
		istringstream stream(line);
		result2 += evalLine2(stream);
	}

	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}