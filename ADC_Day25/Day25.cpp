#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;
using ll = uint64_t;

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


ll transform(ll subjectNumber, ll loop)
{
	ll power = pow(subjectNumber, loop);
	ll modulo = power % 20201227;
	return modulo;
}

ll findEncryptionKey(ll cardPublic, ll doorPublic)
{
	ll encryptionKey = 0;

	int cardLoop = 0;
	int doorLoop = 0;
	while (transform(7, cardLoop) != cardPublic)
	{
		cardLoop++;
	}
	while (transform(7, doorLoop) != doorPublic)
	{
		doorLoop++;
	}

	encryptionKey = transform(cardPublic, doorLoop);

	return encryptionKey;
}

int main()
{
	vector<string> input = parseInput("day25_input.txt");

	ll cardPublic = stoi(input[0]);
	ll doorPublic = stoi(input[1]);

	ll result1 = findEncryptionKey(cardPublic, doorPublic);

	cout << "Part 1 - " << result1 << endl;
	//cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}