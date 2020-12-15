#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <regex>


using namespace std;
using ll = uint64_t;

string decToBinary(int value);
ll binaryToDec(string value);

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

ll applyMask(int value, string mask)
{
	string binaryValue = decToBinary(value);

	if (binaryValue.length() < 36) {
		string zeros = string(36 - binaryValue.length(), '0');
		zeros.append(binaryValue);
		binaryValue = zeros;
	}
	cout << mask << endl;
	cout << binaryValue << endl;
	for (int i = 0; i < binaryValue.length(); i++)
	{
		if (mask[i] == '0')
		{
			binaryValue[i] = '0';
		}
		else if (mask[i] == '1')
		{
			binaryValue[i] = '1';
		}
	}
	
	cout << binaryValue << endl;
	ll decimalValue = binaryToDec(binaryValue);


	return decimalValue;
}

//https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
string decToBinary(int value)
{
	std::string r;
	while (value != 0) { 
		r = (value % 2 == 0 ? "0" : "1") + r; 
		value /= 2; 
	}
	return r;
}

ll binaryToDec(string value)
{
	string num = value;
	ll dec_value = 0;

	// Initializing base value to 1, i.e 2^0
	ll base = 1;

	int len = num.length();
	for (int i = len - 1; i >= 0; i--) {
		if (num[i] == '1')
			dec_value += base;
		base = base * 2;
	}

	return dec_value;

}

ll initializeProgram(vector<string> input)
{
	//address, value.
	unordered_map<int, ll> memory;
	int address = 0;
	ll value = 0;
	string mask;

	for (string line : input)
	{
		if (line.substr(0, 4).compare("mask") == 0)
		{
			mask = line.substr(7);
		}
		else {
			regex rx("(\\[)([0-9]+)(\\])( = )([0-9]+)");
			smatch m;
			regex_search(line, m, rx);

			address = stoi(m[2]);
			value = stoi(m[5]);

			unsigned long long int maskedValue = applyMask(value, mask);

			if (memory.find(address) == memory.end()) {
				cout << "Inserting value " << address << " : " << maskedValue << endl;
				memory.insert(pair<int, ll>(address, maskedValue));
			}
			else
			{
				cout << "Overwriting value "<< address << " : " << maskedValue << endl;
				memory[address] = maskedValue;
			}
		}
	}

	ll sum = 0;
	unordered_map<int, ll>::iterator itr;
	for (itr = memory.begin(); itr != memory.end(); itr++)
	{
		sum += itr->second;
	}

	return sum;
}

void getPermutations(string binaryAddress, vector<int> &indices, int l, int r, vector<string> &permutations) {


}

vector<ll> applyAddressMask(int address, string mask) 
{
	vector<string> permutations;
	vector<int> indices;
	string binaryAddress = decToBinary(address);

	if (binaryAddress.length() < 36) {
		string zeros = string(36 - binaryAddress.length(), '0');
		zeros.append(binaryAddress);
		binaryAddress = zeros;
	}
	cout << mask << endl;
	cout << binaryAddress << endl;

	for (int i = 0; i < binaryAddress.length(); i++)
	{
		if (mask[i] == '0')
		{
			binaryAddress[i] = '0';
		}
		else if (mask[i] == '1')
		{
			binaryAddress[i] = '1';
		}
		else if (mask[i] == 'X')
		{
			indices.push_back(i);
		}
	}

	string tempAddress = binaryAddress;
	for (int i = 0; i < binaryAddress.length(); i++) {
		if (mask[i] == 'X') {
			tempAddress[i] == 0;
		}
	}

	getPermutations(tempAddress, indices, 0, indices.size()-1, permutations);
	//string tempAddress = binaryAddress;
	////Floating Numbers
	//for (int i = 0; i < binaryAddress.length(); i++)
	//{
	//	if (binaryAddress[i] = 'X') {
	//		tempAddress[i] = '0';
	//		for (int j = i; j < binaryAddress.length(); j++) {
	//			if (binaryAddress[j] = 'X') {
	//				binaryAddress[j] = '0';
	//			}
	//		}
	//	}
	//}


	cout << binaryAddress << endl;
	ll decimalAddress = binaryToDec(binaryAddress);

	vector<ll> temp;
	return temp;
}

ll memoryAddressDecoder(vector<string> input) {

	//address, value.
	unordered_map<ll, ll> memory;
	int address = 0;
	ll value = 0;
	string mask;

	for (string line : input)
	{
		if (line.substr(0, 4).compare("mask") == 0)
		{
			mask = line.substr(7);
		}
		else {
			regex rx("(\\[)([0-9]+)(\\])( = )([0-9]+)");
			smatch m;
			regex_search(line, m, rx);

			address = stoi(m[2]);
			value = stoi(m[5]);

			vector<ll> maskedAddresses = applyAddressMask(address, mask);

			for (auto maskedAddress : maskedAddresses) {
				if (memory.find(address) == memory.end()) {
					cout << "Inserting value " << address << " : " << maskedAddress << endl;
					memory.insert(pair <ll, ll >(maskedAddress, value));
				}
				else
				{
					cout << "Overwriting value " << address << " : " << maskedAddress << endl;
					memory[maskedAddress] = value;
				}
			}
		}
	}

	ll sum = 0;
	unordered_map<ll, ll>::iterator itr;
	for (itr = memory.begin(); itr != memory.end(); itr++)
	{
		sum += itr->second;
	}

	return sum;

}

int main()
{
	vector<string> input = parseInput("day14_input.txt");

	//ll result1 = initializeProgram(input);
	ll result2 = memoryAddressDecoder(input);
	//cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}