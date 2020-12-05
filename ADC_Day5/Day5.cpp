#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int binaryToDec(string binaryString);

vector<string> parseInput()
{
	ifstream myfile;
	string line;
	vector<string> boardingPasses;

	myfile.open("day5_input.txt");

	int count = 0;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			boardingPasses.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return boardingPasses;
}

int getSeatId(string boardingPass)
{
	int id = 0;
	int row = 0;
	int column = 0;

	string rowString = boardingPass.substr(0,7);
	string columnString = boardingPass.substr(7,3);

	for (int i = 0; i < rowString.length(); i++)
	{
		if (rowString[i] == 'F')
			rowString[i] = '0';
		else if (rowString[i] == 'B')
			rowString[i] = '1';
	}
	for (int i = 0; i < columnString.length(); i++)
	{
		if (columnString[i] == 'L')
			columnString[i] = '0';
		else if (columnString[i] == 'R')
			columnString[i] = '1';
	}

	//Could concat row and column and do 1 call to binaryToCat.
	row = binaryToDec(rowString);
	column = binaryToDec(columnString);

	id = row * 8 + column;

	return id;

}

int binaryToDec(string binaryString)
{
	//Borrowed for GeeksForGeeks.com.
	string num = binaryString;
	int decValue = 0;

	int base = 1;

	int len = num.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (num[i] == '1')
		{
			decValue += base;
		}
			base = base * 2;
	}

	return decValue;
}

int findHighestId(vector<string> boardingPasses)
{
	int max = 0;
	int id = 0;

	for (string boardingPass : boardingPasses)
	{
		id = getSeatId(boardingPass);
		if (id > max)
			max = id;
	}
	return max;
}

int findMissing(vector<string> boardingPasses)
{
	int id = 0;
	int prevId = 0;
	int missing = 0;
	set<int> seatIds;
	for (string boardingPass : boardingPasses)
	{
		id = getSeatId(boardingPass);
		seatIds.insert(id);
	}

	set<int>::iterator itr;
	prevId = *seatIds.begin();

	for (itr = seatIds.begin(); itr != seatIds.end(); ++itr)
	{
		if ((*itr - prevId) > 1) {
			missing = prevId+1;
			return missing;
		}
		prevId = *itr;
	}

	return missing;

}

int main()
{
	vector<string> boardingPasses = parseInput();
	int result1 = findHighestId(boardingPasses);
	int result2 = findMissing(boardingPasses);

	cout << "Part 1 : Highest ID: " << result1 << endl;
	cout << "Part 2 - Missing Seat: " << result2 << endl;

	cin.get();
	return 0;
}