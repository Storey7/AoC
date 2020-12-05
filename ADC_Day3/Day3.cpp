#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

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
int countTree(vector<string> treeMap, int xOffset, int yOffset)
{
	int count = 0;
	int width = treeMap[0].length();
	int x = 0;
	int y = 0;

	for(int i = 0; i < treeMap.size(); i++)
	{
		if(treeMap[i][x] == '#')
			count++;

		x = (x + xOffset) % width;
		i = i + (yOffset - 1);
	}

	return count;
}

unsigned long getProduct(vector<string> treeMap)
{
	unsigned long int result = 1;

	//Implicit casts. Overflows if we stick to ints.
	result = result * countTree(treeMap, 1, 1);
	result = result * countTree(treeMap, 3, 1);
	result = result * countTree(treeMap, 5, 1);
	result = result * countTree(treeMap, 7, 1);
	result = result * countTree(treeMap, 1, 2);

	return result;
}

int main()
{
	vector<string> treeMap = parseFile("day3_input.txt");

	int treeCount = 0;
	unsigned long int treeProduct = 0;

	treeCount = countTree(treeMap, 3, 1);
	treeProduct = getProduct(treeMap);

	cout << "Part 1 - Tree Count: " << treeCount << endl;
	cout << "Part 2 - Tree Product: " << treeProduct << endl;

	cin.get();
	return 0;
}