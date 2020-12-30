#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <algorithm>

using namespace std;
using ll = int64_t;

vector<string> rotateArray(vector<string> arr, int n);
vector<string> hFlipArray(vector<string> arr);
pair<string, string> getSides(vector<string>& tile);
string reverseString(string edge);

vector<string> readFile(string path)
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

map<int, vector<string>> parseInput(vector<string>& input)
{
	map<int, vector<string>> tiles;
	vector<string> tileContent;
	int tileNumber;
	regex rx("(Tile )([0-9]+)");
	smatch sm;

	for (string line : input)
	{
		if (regex_search(line, sm, rx)) {
			tileNumber = stoi(sm[2]);
		}
		else if (line.compare("") == 0) {
			tiles[tileNumber] = tileContent;
			tileContent.clear();
		}
		else {
			tileContent.push_back(line);
		}
	}

	tiles[tileNumber] = tileContent;

	return tiles;
}

pair<string, string> getSides(vector<string>& tile)
{
	stringstream left;
	stringstream right;

	for (string line : tile) {
		left << line[0];
		right << line[line.length() - 1];
	}

	return pair<string, string>(left.str(), right.str());
}

string reverseString(string edge)
{
	reverse(edge.begin(), edge.end());
	return edge;
}

vector<string> rotateArray(vector<string> arr, int n)
{
	//n = number of anticlockwise 90 degree rotations. 
	int N = 10, M = 10;
	for (int k = 0; k < n; k++) {
		vector<string> arr2 = arr;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j) {
				//(x, y) --> -y, x
				int ni = N - 1 - j, nj = i;
				arr2[ni][nj] = arr[i][j];
			}
		arr.swap(arr2);
	}
	return arr;
}

vector<string> hFlipArray(vector<string> arr)
{
	int N = 10, M = 10; // Size of tiles is constant
	//0 == horizontal, 1 = vertical.
	for (int i = 0; i < N; ++i) {
		for (int l = 0, r = M - 1; l < r; ++l, --r) {
			swap(arr[i][l], arr[i][r]);
		}
	}

	return arr;
}

void matchTiles(vector<string>& tile1, vector<string>& tile2)
{
	//These definitely match, just need to rotate / flip tile2 until correct. 
	set<string> tile1Edges; //Top, topR, bottom, bottomr, left, left r, right, right r. 
	set<string> tile2Edges;

	tile1Edges.insert(tile1[0]);
	tile1Edges.insert(tile1[tile1.size()-1]);
	pair<string, string> sides = getSides(tile1);
	tile1Edges.insert(sides.first);
	tile1Edges.insert(sides.second);

	tile2Edges.insert(tile2[0]);
	tile2Edges.insert(tile2[tile1.size()-1]);
	sides = getSides(tile2);
	tile2Edges.insert(sides.first);
	tile2Edges.insert(sides.second);

	set<string>::iterator itr = tile2Edges.begin();

	for (itr; itr != tile2Edges.end(); ++itr) {
		tile2Edges.insert(reverseString(*itr));
	}
	
	for (string edge : tile1Edges) {
		if (tile2Edges.find(edge) != tile2Edges.end()) {
			cout << edge << endl;
			break;
		}
	}

	bool match = false;
	for(int j = 0; j < 2; j++){
		for (int i = 0; i < 4; i++) {
			
		}
		if (match) {
			break;
		}
		tile2 = hFlipArray(tile2);
	}
	tile2 = hFlipArray(tile2);
}

pair<ll, ll> getCornerIds(map<int, vector<string>>& tiles)
{
	ll product = 1;
	ll waterRoughness = 0;

	map<string, vector<int>> edgeIds;
	
	map<int, vector<string>>::iterator itr;

	for (itr = tiles.begin(); itr != tiles.end(); ++itr)
	{
		int tileId = itr->first;
		vector<string> tile = itr->second;
		vector<string> edges;

		string top = tile[0];
		string bottom = tile[tile.size() - 1];
		pair<string, string> sides = getSides(tile);
		string left = sides.first;
		string right = sides.second;

		edges.push_back(top);
		edges.push_back(bottom);
		edges.push_back(left);
		edges.push_back(right);

		for (string edge : edges) {
			string reverseEdge = reverseString(edge);

			if (edgeIds.find(edge) == edgeIds.end()) {
				edgeIds[edge].push_back(tileId);
			}
			else
			{
				edgeIds[edge].push_back(tileId);
			}

			if (edgeIds.find(reverseEdge) == edgeIds.end()) {
				edgeIds[reverseEdge].push_back(tileId);
			}
			else
			{
				edgeIds[reverseEdge].push_back(tileId);
			}
		}
	}

	
	map<string, vector<int>>::iterator itr2;

	//Remove invalid edges (no matches)
	for (itr2 = edgeIds.begin(); itr2 != edgeIds.end(); )
	{
		if (itr2->second.size() < 2) {
			itr2 = edgeIds.erase(itr2);
		}
		else {
			++itr2;
		}
	}

	//Create a dictionary of matches.
	map<int, set<int>> matches;
	for (itr2 = edgeIds.begin(); itr2 != edgeIds.end(); ++itr2 )
	{
		for (int id : itr2->second)
		{
			for (int child : itr2->second){
				if (child != id)
				{
					matches[id].insert(child);
				}

			}
		}
	}

	map<int, set<int>>::iterator itr3;
	int tile1Id;

	//PART 1
	for (itr3 = matches.begin(); itr3 != matches.end(); ++itr3)
	{
		if (itr3->second.size() == 2)
		{
			tile1Id = itr3->first;
			product *= itr3->first;
		}
	}

	// PART 2
	//Match squares together. L to R, T to B.
	vector<string> tile1 = tiles[tile1Id]; //start with arbitrary corner tile. 
	vector<int> tile2Ids;
	int tile2Id;
	
	set<int>::iterator itr4;
	for (itr4 = matches[tile1Id].begin(); itr4 != matches[tile1Id].end(); itr4++)
	{
		tile2Ids.push_back(*itr4);
	}
	tile2Id = tile2Ids[0];
	vector<string> tile2 = tiles[tile2Id];

	while (true) {
		
		matchTiles(tile1, tile2);

		tiles[tile2Id] = tile2; //Assume tile1 is always correct.

		tile2Ids.clear();
		int prevTileId = tile1Id;
		tile1Id = tile2Id;

		for (itr4 = matches[tile1Id].begin(); itr4 != matches[tile1Id].end(); ++itr4)
		{
			tile2Ids.push_back(*itr4);
		}

		if (matches[tile1Id].size() == 2)
		{
			break; //Row completed
		}
		for (int id : tile2Ids) {
			if (matches[id].size() <= 3 && id != prevTileId)
			{
				tile2Id = id;
				break;
			}
		}
	}

	//Remove edges and combine tiles.
	//Check for seamonsts in each rotation and switch to Os
	//Count ##s

	return pair<ll,ll>(product, waterRoughness);
}



int main()
{
	vector<string> input = readFile("day20_input.txt");
	map<int, vector<string>> tiles;

	tiles = parseInput(input);

	pair<ll, ll> result;
	result = getCornerIds(tiles);
	cout << "Part 1 - " << result.first << endl;
	cout << "Part 2 - " << result.second << endl;

	cin.get();
	return 0;
}