#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>

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

int executeProgram(vector<string> program)
{
	int accumulator = 0;
	int arg;
	string instruction;
	set<int> visitedAddresses;
	int pc = 0;

	while (pc < program.size())
	{
		if (visitedAddresses.find(pc) != visitedAddresses.end())
		{
			return accumulator;
		}
		visitedAddresses.insert(pc);
		instruction = program[pc].substr(0, 3);
		arg = stoi(program[pc].substr(3));

		if (instruction.compare("nop") == 0) {
			pc++;
		}
		else if (instruction.compare("acc") == 0) {
			accumulator += arg;
			pc++;
		}
		else if (instruction.compare("jmp") == 0) {
			pc += arg;
		}
		//cout << instruction << " " << arg << endl;
	}

	//Went to end of program
	return -accumulator;
}

//
int findCorrupted(vector<string> program)
{
	int accumulator;
	string instruction;
	vector<string> changedProgram;

	changedProgram = program;

	for (int i = program.size()-1; i >= 0; i--)
	{
		changedProgram = program;
		instruction = changedProgram[i].substr(0, 3);
		if (instruction.compare("nop") == 0) {
			changedProgram[i][0] = 'j';
			changedProgram[i][1] = 'm';
			changedProgram[i][2] = 'p';

		}
		else if (instruction.compare("acc") == 0) {
			continue;
		}
		else if (instruction.compare("jmp") == 0) {
			changedProgram[i][0] = 'n';
			changedProgram[i][1] = 'o';
			changedProgram[i][2] = 'p';
		}

		accumulator = executeProgram(changedProgram);
		if (accumulator < 0) {
			cout << i << endl;
			return -accumulator;
		}

		changedProgram = program;
	}
}

int main()
{
	vector<string> program = parseInput("day8_input.txt");

	int result1 = executeProgram(program);
	int result2 = findCorrupted(program);

	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}