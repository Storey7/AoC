#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>
#include <vector>
#include <set>

using namespace std;
int final_score;

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

int calculateScore(deque<int>& winner) {
	int score = 0;
	int i = 1;
	deque<int>::reverse_iterator rit;
	for (rit = winner.rbegin(); rit != winner.rend(); ++rit) {
		score += i * *rit;
		i++;
	}
	return score;
}

pair<deque<int>, deque<int>> getDecks(vector<string> input)
{
	deque<int> player1;
	deque<int> player2;
	int mode = 0;

	for (string line : input) {
		if (line.compare("") == 0) {
			continue;
		}
		if (line.compare("Player 1:") == 0) {
			continue;
		}
		if (line.compare("Player 2:") == 0) {
			mode = 1;
			continue;
		}
		if (mode == 0) {
			player1.push_back(stoi(line));
		}
		else if (mode == 1) {
			player2.push_back(stoi(line));
		}
	}

	return make_pair(player1, player2);
}

int playGame(deque<int> player1, deque<int> player2) {
	int playerScore = 0;
	deque<int> winner;
	
	while (player1.size() != 0 && player2.size() != 0) {
		int player1Card = player1.front();
		int player2Card = player2.front();

		if (player1Card > player2Card) {
			player1.push_back(player1Card);
			player1.push_back(player2Card);
		}
		else if (player1Card < player2Card) {
			player2.push_back(player2Card);
			player2.push_back(player1Card);
		}
		player1.pop_front();
		player2.pop_front();
	}

	if (player1.size() > 0) {
		winner = player1;
	}
	else {
		winner = player2;
	}
	
	return calculateScore(winner);
}

void printDeque(deque<int> player) {
	cout << endl;
	for (int i : player) {
		cout << i << " ";
	}
	cout << endl;
}

int recursiveCombat(deque<int> player1, deque<int> player2) 
{
	// 1 - If there was a previous round in the same game with the same cards in the same order: Player1 wins.
	set<deque<int>> configurations;
	
	// 2 - If both players have enough cards remaining as the value of the card they just drew, the winner is determined by a new game of combat. 
	int winner = 0;

	deque<int> subPlayer1;
	deque<int> subPlayer2;

	while (player1.size() != 0 && player2.size() != 0) {
		int player1Card = player1.front();
		int player2Card = player2.front();

		if (configurations.find(player1) != configurations.end() ||
			configurations.find(player2) != configurations.end())
		{
			return 1;
		}
		configurations.insert(player1);
		configurations.insert(player2);

		if (player1.size() > player1Card && player2.size() > player2Card) {
			subPlayer1.clear();
			subPlayer2.clear();
			deque<int>::iterator itr;
			for (int i = 1; i <= player1Card; i++) {
				subPlayer1.push_back(player1[i]);
			}
			for (int i = 1; i <= player2Card; i++) {
				subPlayer2.push_back(player2[i]);
			}
			winner = recursiveCombat(subPlayer1, subPlayer2);
		}

		// 3 - Otherwise, the winner is the player with the higher value card. 
		else {
			if (player1Card > player2Card) {
				winner = 1;
			}
			else if (player1Card < player2Card) {
				winner = 2;
			}
		}

		if (winner == 1) {
			player1.push_back(player1Card);
			player1.push_back(player2Card);
		}
		else if (winner == 2) {
			player2.push_back(player2Card);
			player2.push_back(player1Card);
		}
		player1.pop_front();
		player2.pop_front();
	}

	if (player1.size() == 0 || player2.size() == 0) {
		if (winner == 1) {
			final_score = calculateScore(player1);
		}
		else {
			final_score = calculateScore(player2);
		}
	}

	return winner;
}

int main()
{
	vector<string> input = parseInput("day22_input.txt");
	pair<deque<int>, deque<int>> players = getDecks(input);
	
	int result1 = playGame(players.first, players.second);
	int result2 = recursiveCombat(players.first, players.second);
	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << final_score << endl;

	cin.get();
	return 0;
}