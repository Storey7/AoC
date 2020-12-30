#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;
using ll = uint64_t;

struct Node
{
	int data;
	struct Node* next;
};

//insert a new node in an empty list
struct Node* insertInEmpty(struct Node* last, int new_data)
{
	// if last is not null then list is not empty, so return
	if (last != NULL)
		return last;

	// allocate memory for node
	struct Node* temp = new Node;

	// Assign the data.
	temp->data = new_data;
	last = temp;

	// Create the link.
	last->next = last;

	return last;
}

//insert new node at the end of the list
struct Node* insertAtEnd(struct Node* last, int new_data)
{
	//if list is empty then add the node by calling insertInEmpty
	if (last == NULL)
		return insertInEmpty(last, new_data);

	//else create a new node
	struct Node* temp = new Node;

	//assign data to new node
	temp->data = new_data;
	temp->next = last->next;
	last->next = temp;
	last = temp;

	return last;
}

//insert a new node in between the nodes
struct Node* insertAfter(struct Node* last, int new_data, int after_item)
{
	//return null if list is empty
	if (last == NULL)
		return NULL;

	struct Node* temp, * p;
	p = last->next;
	do
	{
		if (p->data == after_item)
		{
			temp = new Node;
			temp->data = new_data;
			temp->next = p->next;
			p->next = temp;

			if (p == last)
				last = temp;
			return last;
		}
		p = p->next;
	} while (p != last->next);

	cout << "The node with data " << after_item << " is not present in the list." << endl;
	return last;

}

//traverse the circular linked list
void traverseList(struct Node* last) {
	struct Node* p;

	// If list is empty, return.
	if (last == NULL) {
		cout << "Circular linked List is empty." << endl;
		return;
	}
	p = last->next; // Point to the first Node in the list.

	// Traverse the list starting from first node until first node is visited again

	do {
		cout << p->data << "==>";
		p = p->next;
	} while (p != last->next);
	if (p == last->next)
		cout << p->data;
	cout << "\n\n";
}

string playGame(vector<int> numbers, int moves)
{
	// Pick current cup
	// Pick up 3 cups to the right.
	// Pick a destination cup which is current cup label - n (not in picked up cups)
	// place cups to the right of destination cup.
	// pick a new current cup. 

	struct Node* last = NULL;
	
	last = insertInEmpty(last, numbers[0]);

	for (int i = 1; i < numbers.size(); i++) {
		last = insertAtEnd(last, numbers[i]);
	}

	traverseList(last);

	for (int i = 0; i < moves; i++) {
		struct Node* currentNode = last->next;
		struct Node* pickUpNode = currentNode;
		struct Node* destinationNode = currentNode;
		struct Node* temp;
		
		int currentCup = currentNode->data;
		set<int> pickedUp;

		for (int i = 0; i < 3; i++) {
			pickUpNode = pickUpNode->next;
			pickedUp.insert(pickUpNode->data);
		}

		int destinationCupValue = currentCup - 1;
		if (destinationCupValue == 0) {
			destinationCupValue = 9;
		}
		while (pickedUp.find(destinationCupValue) != pickedUp.end()) {
			destinationCupValue -= 1;
			if (destinationCupValue == 0) {
				destinationCupValue = 9;
			}
		}

		while (destinationNode->data != destinationCupValue) {
			destinationNode = destinationNode->next;
		}

		temp = pickUpNode->next;
		pickUpNode->next = destinationNode->next;
		destinationNode->next = currentNode->next;
		currentNode->next = temp;

		last = currentNode;
	}

	traverseList(last);

	stringstream resultStream;
	while (last->data != 1) {
		last = last->next;
	}

	while (last->next->data != 1) {
		last = last->next;
		resultStream << last->data;
	}
	return resultStream.str();
}

ll playPart2(vector<int> numbers, ll moves)
{
	struct Node* last = NULL;
	map<int, Node*> nodeIndexes;

	last = insertInEmpty(last, numbers[0]);

	for (int i = 1; i < numbers.size(); i++) {
		last = insertAtEnd(last, numbers[i]);
	}

	for (int i = 0; i < numbers.size(); i++) {
		nodeIndexes[numbers[i]] = last->next;
		last = last->next;
	}

	for (ll i = 0; i < moves; i++) {
		struct Node* currentNode = last->next;
		struct Node* pickUpNode = currentNode;
		struct Node* destinationNode = currentNode;
		struct Node* temp;

		int currentCup = currentNode->data;
		set<int> pickedUp;

		for (int i = 0; i < 3; i++) {
			pickUpNode = pickUpNode->next;
			pickedUp.insert(pickUpNode->data);
		}

		int destinationCupValue = currentCup - 1;
		if (destinationCupValue == 0) {
			destinationCupValue = numbers[numbers.size()-1];
		}
		while (pickedUp.find(destinationCupValue) != pickedUp.end()) {
			destinationCupValue -= 1;
			if (destinationCupValue == 0) {
				destinationCupValue = numbers[numbers.size() - 1];
			}
		}

		destinationNode = nodeIndexes[destinationCupValue];

		temp = pickUpNode->next;
		nodeIndexes[pickUpNode->data] = destinationNode->next;
		pickUpNode->next = destinationNode->next;
		
		nodeIndexes[destinationNode->data] = currentNode->next;
		destinationNode->next = currentNode->next;
		
		nodeIndexes[currentNode->data] = temp;
		currentNode->next = temp;

		last = currentNode;
	}

	while (last->data != 1) {
		last = last->next;
	}

	ll product = 1;
	product = product * last->next->data * last->next->next->data;

	return product;
}

int main()
{
	string input = "389125467";
	vector<int> numbers;

	for (int i = 0; i < input.length(); i++) {
		numbers.push_back((int)input[i] - '0');
	}

	vector<int> part2Numbers = numbers;
	for (int i = 10; i < 1000001; i++) {
		part2Numbers.push_back(i);
	}

	string result1 = playGame(numbers, 100);
	ll result2 = playPart2(part2Numbers, 10000000);

	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}