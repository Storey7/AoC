#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <set>

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

set<string> splitAllergens(string& allergenString) {
	set<string> allergens;
	regex rx("(\\w+)");

	for (sregex_iterator i = sregex_iterator(allergenString.begin(), allergenString.end(), rx);
		i != sregex_iterator();
		++i) {
		smatch m = *i;
		allergens.insert(m.str());
	}

	return allergens;
}

pair<int, vector<string>> findAllergens(vector<string>& input)
{
	int result1 = 0;
	map<string, set<string>> ingredients;
	map<string, set<string>> allergens;
	map<string, int> allIngredients;
	map<string, int> allAllergens;

	vector<pair<set<string>, set<string>>> foods;

	map<string, set<string>> couldBe;

	for (string line : input) {
		regex rx("(.+)( \\(contains )(.+)(\\))");
		smatch m;
		regex_search(line, m, rx);
		string ingredientString = m[1];
		string allergenString = m[3];
		
		set<string> ingredientList;
		set<string> allergenList = splitAllergens(allergenString);
		
		istringstream iss(ingredientString);
		string item;
		while (iss >> item) {
			ingredientList.insert(item);
		}

		foods.push_back(make_pair(ingredientList, allergenList));

		for(string ingredient : ingredientList) {
			for (string allergen : allergenList) {
				allAllergens[allergen]++;
				couldBe[ingredient].insert(allergen);

				ingredients[ingredient].insert(allergen);
				allergens[allergen].insert(ingredient);
			}
			allIngredients[ingredient]++;
		}
	}
	
	//For every allergen, find the ingredients not contained in the food item. 
	//E.g for every food that contains dairy, the only ingedients we know could be dairy are the ones not in those foods.
	//Erasing these ingredients from the list of possibilites eventually leaves us with items that cannot contain any allergen. 
	for (auto foodItem : foods) {
		set<string> ingredientList = foodItem.first;
		set<string> allergenList = foodItem.second;

		for (string allergen : allergenList) {
			map<string, int>::iterator itr;
			for (itr = allIngredients.begin(); itr != allIngredients.end(); ++itr) {
				string ingredient = itr->first;
				if (ingredientList.find(ingredient) == ingredientList.end()) {
					couldBe[ingredient].erase(allergen);
				}
			}
		}
	}

	for (auto item : couldBe)
	{
		string ingredient = item.first;
		set<string> allergenList = item.second;

		if (allergenList.size() == 0)
		{
			result1 += allIngredients[ingredient];
		}
	}

	//PART 2
	//Assign ingredients with where number of possibilites == 1. 
	//Do this until all ingredients are assigned. 
	vector<string> result2;
	set<string> used;
	map<string, string> ingredientDeductions;

	while (ingredientDeductions.size() < allAllergens.size()) {
		for (auto ingredientItem : allIngredients) {
			string ingredient = ingredientItem.first;
			set<string> couldBeAllergens = couldBe[ingredient];

			for (string allergen : used)
			{
				if (couldBeAllergens.find(allergen) != couldBeAllergens.end()) {
					couldBeAllergens.erase(allergen);
				}
			}
			
			if (couldBeAllergens.size() == 1) {
				string allergen = *couldBeAllergens.begin();
				ingredientDeductions[allergen] = ingredient;
				used.insert(allergen);
			}

		}
	}

	//Items are sorted into the map alphabetically by allergen, just need to return the list of ingredients.
	for (auto ingredientItem : ingredientDeductions) {
		result2.push_back(ingredientItem.second);
	}


	return make_pair(result1, result2);

}

int main()
{
	vector<string> input = parseInput("day21_input.txt");

	pair<int, vector<string>> result = findAllergens(input);

	cout << "Part 1 - " << result.first << endl;
	cout << "Part 2" << endl;
	for (string ingredient : result.second) {
		cout << ingredient << ",";
	}

	cin.get();
	return 0;
}