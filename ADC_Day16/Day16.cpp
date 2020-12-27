#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

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

int validateTickets(vector<string> &input)
{
	int scanningError = 0;
	vector<pair<int, int>> validRanges;
	
	for (string line : input)
	{
		if (line.compare("") == 0)
			break;

		regex rx("([0-9]+)(-)([0-9]+)( or )([0-9]+)(-)([0-9]+)");
		smatch m;
		regex_search(line, m, rx);

		validRanges.push_back(pair<int, int>(stoi(m[1]), stoi(m[3])));
		validRanges.push_back(pair<int, int>(stoi(m[5]), stoi(m[7])));
	}

	for (string line : input)
	{
		if (line.compare("") == 0)
			break;
	}

	bool ticketList = false;
	for (string line : input)
	{

		if (ticketList) {
			stringstream ss(line);
			while (ss.good()) {
				string number;
				getline(ss, number, ',');

				int ticketNumber = stoi(number);
				bool valid = false;
				for (pair<int, int> validRange : validRanges) {
					if (ticketNumber >= validRange.first && ticketNumber <= validRange.second)
					{
						valid = true;
						break;
					}
				}
				if (valid == false) {
					cout << "Bad Ticket : " << line << endl;
					scanningError += ticketNumber;
				}
			}
		}

		if (line.compare("nearby tickets:") == 0)
			ticketList = true;
	}

	return scanningError;
}

// Could've just refactored code for part 1, but I like keeping it around 
// and seperate so we can see how I solved each problem individually. 
int determineFields(vector<string> &input) {
	int departureFieldCount = 1;
	int mode = 0;
	vector<pair<string, int>> fieldNames;
	vector<pair<int, int>> validRanges;
	vector<int> myTicket;
	vector<vector<int>> nearbyTickets;

	for (string line : input)
	{
		if (line.compare("") == 0)
			continue;
		if (line.compare("your ticket:") == 0) {
			mode = 1;
			continue;
		}
		if (line.compare("nearby tickets:") == 0) {
			mode = 2;
			continue;
		}

		if (mode == 0) {
			regex rx("([a-z ]+)(: )([0-9]+)(-)([0-9]+)( or )([0-9]+)(-)([0-9]+)");
			smatch m;
			regex_search(line, m, rx);
			fieldNames.push_back(pair<string, int>(m[1], 0));
			validRanges.push_back(pair<int, int>(stoi(m[3]), stoi(m[5])));
			validRanges.push_back(pair<int, int>(stoi(m[7]), stoi(m[9])));
		}
		else if (mode == 1) {
			stringstream ss(line);
			while (ss.good()) {
				string number;
				getline(ss, number, ',');
				int ticketField = stoi(number);

				myTicket.push_back(ticketField);
			}
		}
		else if (mode == 2) {
			vector<int> nearbyTicket;

			stringstream ss(line);
			while (ss.good()) {
				string number;
				getline(ss, number, ',');
				int ticketField = stoi(number);

				nearbyTicket.push_back(ticketField);
			}

			nearbyTickets.push_back(nearbyTicket);
		}
	}

	vector<vector<int>>::iterator itr;
	itr = nearbyTickets.begin();

	//erase invalid tickets.
	while (itr != nearbyTickets.end()) {
		bool valid = false;
		vector<int> ticket = *itr;
		for (int ticketField : ticket) {
			for (pair<int, int> validRange : validRanges) {
				valid = false;
				if (ticketField >= validRange.first && ticketField <= validRange.second)
				{
					valid = true;
					break;
				}
			}

			if (valid == false) {
				cout << "Erasing : " << ticket[0] << endl;
				itr = nearbyTickets.erase(itr);
			}
		}

		if (valid == true)
			itr++;
	}

	vector<int> currentColumn;
	for(int i = 0; i < nearbyTickets[0].size; i++;{
		for (auto row : nearbyTickets) {
			currentColumn.push_back(row[i]);
		}
	}

	for (vector<int> ticket : nearbyTickets)
	{
		cout << ticket[3] << endl;
	}

	for (int i = 0; i < myTicket.size(); i++)
	{
		if (fieldNames[i].first.rfind("departure", 0) == 0)
		{
			departureFieldCount = departureFieldCount * myTicket[i];
		}
	}
	


	return departureFieldCount;
}

int main()
{
	vector<string> input = parseInput("day16_input.txt");

	int result1 = validateTickets(input);
	int result2 = determineFields(input);
	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}