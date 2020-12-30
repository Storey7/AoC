#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

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

int main()
{
	vector<string> input = parseInput("input.txt");


	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}