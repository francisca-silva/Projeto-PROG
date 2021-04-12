#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// FUNCTION DECLARATION 


struct Fence {
	int pos_x, pos_y;
	bool working = true;
};

struct Player {
	int pos_x, pos_y;
	bool alive = true;
};

struct Robot {
	int pos_x, pos_y;
	bool alive = true; 
};

//void readMaze(string filename);
bool menu();
void rules();

bool menu(){
	char c;
	bool valid = false;

	while (!valid){
		cout << "1) Rules" << endl;
		cout << "2) Play " << endl;
		cout << "0) Exit;" << endl;
		
		cin >> c;
 
		switch (c) {
			case '1':
				rules();
				break;
			case '2':
				return true;
			case '0':
				return false;
			default:
				cout << "Invalid input";
				valid = false;
				break;
		}
	}
		
}

void rules(){
	    cout << "The player is placed in maze of high-voltage fences and posts.There are also some interceptor robots that will try to destroy the player." << 
			"If the player touches the maze or any of these robots, that is the end of the game." <<
			"The robost are also destroyed when they touch the fences / post or when they collide with each other." <<
			"Every time the player moves in any direction(horizontally, vertically, or diagonally) to a contiguous cell, each robot moves one cell closer to the new player's location, in whichever direction is the shortest path." <<
			"The robots have no  vision sensors but they have an accurate odour sensor that allows them to follow the player!" << 
			"There is one hope : make the robots hit the maze or each other.If all of them are destroyed, the player wins !!" << endl;
}


string chooseMaze(){

	int number, numberOfMaze = 5;
	string filename;
	ifstream in_stream;
	bool valid;

	do{
		cout << "Please choose the number(an integer value) of the maze you want to use(1-5)" << endl;
		cin >> number;
		cin.clear();
		cin.ignore(1000000000,'\n');
		if (cin.fail()) {
			valid = false;
            cout << "Invalid input." << endl;
		}

        // o utilizador pode ter posto um numero primeiro dps um espaço e dps outra coisa qqr e isso n da erro a primeira mas devia
        // temos de encontrar uma forma de evitar isso
		
	} while (!valid && (number < 1 ||number > numberOfMaze));

	if (number >= 1 && number <= numberOfMaze) filename = "MAZE_0" + to_string(number) + ".txt";
	else valid = false;

	return filename;
}

void ReadMaze(string filename, Player & player, vector <Robot> &robots) {

	ifstream in_stream;
	int numcol = 1, numrow = 0;
	string row;
	size_t size;
	Robot robot;

	in_stream.open(filename);

    getline(in_stream, row);
	while (!in_stream.eof()) {
		
		getline(in_stream, row);
		char c;
		while(c != '\n'){
			c = row[numrow];
			numrow++;

			switch (c)
			{
			case 'H':
				player.pos_x = numrow;
				player.pos_y = numcol;
				break;
			case 'R':
				robots.push_back(Robot());
				size = robots.size();
				robot.pos_x = numcol;
				robot.pos_y = numrow;
				robots[size-1] = robot;
				break;
			case '*':
				break;
			default:
				break;
			}
		}
		
		numcol++;
	}
	in_stream.close();
	}
