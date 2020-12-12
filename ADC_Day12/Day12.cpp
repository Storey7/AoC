#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>

#define PI 3.14159265

using namespace std;

int getRotationX(int x, int y, int degrees);
int getRotationY(int x, int y, int degrees);

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

int getManhattenWaypoint(vector<string> instructions)
{
	int distanceX = 0;
	int distanceY = 0;

	int waypointDistX = 10;
	int waypointDistY = 1;

	int direction = 0;
	char command;
	int arg;

	for (string instruction : instructions) {
		command = instruction[0];
		arg = stoi(instruction.substr(1, instruction.size() - 1));
		//cout << command << " " << arg << endl;

		if (command == 'N') {
			waypointDistY += arg;
		}
		else if (command == 'S') {
			waypointDistY -= arg;
		}
		else if (command == 'E') {
			waypointDistX += arg;
		}
		else if (command == 'W') {
			waypointDistX -= arg;
		}
		else if (command == 'L') {
			int tempWaypointX = waypointDistX;
			waypointDistX = getRotationX(waypointDistX, waypointDistY, arg);
			waypointDistY = getRotationY(tempWaypointX, waypointDistY, arg);
		}
		else if (command == 'R') {
			int tempWaypointX = waypointDistX;
			waypointDistX = getRotationX(waypointDistX, waypointDistY, -arg);
			waypointDistY = getRotationY(tempWaypointX, waypointDistY, -arg);
		}
		else if (command == 'F') {
			distanceX += waypointDistX * arg;
			distanceY += waypointDistY * arg;
		}
		/*cout << "SHIP" << endl;
		cout << distanceX << " " << distanceY << " " << direction << endl;

		cout << "WAYPOINT" << endl;
		cout << waypointDistX << " " << waypointDistY << " " << direction << endl;*/

		//cin.get();
	}

	return (abs(distanceX) + abs(distanceY));
}

int getRotationX(int x, int y, int degrees)
{
	int sine = sin(degrees * PI / 180);
	int cosine = cos(degrees * PI / 180);
	int rotatedY = (x * sine) + (y * cosine);
	int rotatedX = (x * cosine) - (y * sine);
	/*else if (degrees < 0)
		int rotatedX = x * cos;*/
	return rotatedX;
}

int getRotationY(int x, int y, int degrees) 
{
	int sine = sin(degrees * PI / 180);
	int cosine = cos(degrees * PI / 180);
	int rotatedY = (x * sine) + (y * cosine);
	return rotatedY;
}


int getManhattenDistance(vector<string> instructions)
{
	int distanceX = 0;
	int distanceY = 0;
	int direction = 0;
	char command;
	int arg;

	for (string instruction : instructions) {
		command = instruction[0];
		arg = stoi(instruction.substr(1, instruction.size()-1));
		//cout << command << " " << arg << endl;

		if (command == 'N') {
			distanceY += arg;
		}
		else if (command == 'S') {
			distanceY -= arg;
		}
		else if (command == 'E') {
			distanceX += arg;
		}
		else if (command == 'W') {
			distanceX -= arg;
		}
		else if (command == 'L') {
			direction += arg;
			direction = direction % 360;

		}
		else if (command == 'R') {
			direction -= arg;
			direction = direction % 360;
		}
		else if (command == 'F') {
			if (direction == 0) {
				distanceX += arg;
			}
			else if (direction == 90 || direction == -270){
				distanceY += arg;
			}
			else if (direction == 180 || direction == -180) {
				distanceX -= arg;
			}
			else if (direction == 270 || direction == -90) {
				distanceY -= arg;
			}
		}
		//cout << distanceX << " " << distanceY << " " << direction << endl;
		//cin.get();
	}

	return (abs(distanceX) + abs(distanceY));
}

int main()
{
	vector<string> input = parseInput("day12_input.txt");

	int result1 = getManhattenDistance(input);
	int result2 = getManhattenWaypoint(input);

	cout << "Part 1 - " << result1 << endl;
	cout << "Part 2 - " << result2 << endl;

	cin.get();
	return 0;
}