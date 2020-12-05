#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

int getProductTwo(vector<int> expenses)
{
	int result = 0;
	int complement = 0;
	set<int> expenseSet;

	for (int i = 0; i < expenses.size(); i++) {
		complement = 2020 - expenses[i];
		if (expenseSet.find(complement) != expenseSet.end())
		{
			result = expenses[i] * complement;
			return result;
		}
		else
			expenseSet.insert(expenses[i]);
	}
	return result;

}

int getProductThree(vector<int> expenses)
{
	int result = 0;
	int l, r;
	
	sort(expenses.begin(), expenses.end());

	for (int i = 0; i < (int)expenses.size() - 2; i++)
	{
		l = i + 1;
		r = (int)expenses.size() - 1;

		while (l < r) {
			if (expenses[i] + expenses[l] + expenses[r] == 2020) {
				cout << expenses[i] << " " << expenses[l] << " " << expenses[r] << endl;
				return expenses[i] * expenses[l] * expenses[r];
			}
			else if (expenses[i] + expenses[l] + expenses[r] < 2020)
				l++;
			else
				r--;
		}
	}
	return result;
}

vector<int> parseFile(string path) {
	string line;
	ifstream myfile;
	myfile.open(path);
	vector<int> result;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//cout << line << '\n';
			result.push_back(stoi(line));
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return result;
}

int main()
{
	vector<int> expenses;
	expenses = parseFile("day1_input.txt");

	cout << "Part 1 : " << getProductTwo(expenses) << endl;
	cout << "Part 2 : " <<  getProductThree(expenses) << endl;

	return 0;
}