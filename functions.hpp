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


void chooseMaze(){

	int number;
	string name;
	ifstream in_stream;
	bool valid;

	do{
		cout << "Please choose the number(an integer value) of the maze you want to use(1-5)";
		cin >> number;
		if (cin.fail()) {
			valid = false;
			cin.clear();
			cin.ignore(1000000000,'\n');
            cout << "Invalid input." << endl;
		}

        // o utilizador pode ter posto um numero primeiro dps um espaço e dps outra coisa qqr e isso n da erro a primeira mas devia
        // temos de encontrar uma forma de evitar isso
		
	} while (!valid && (number < 1 ||number > 5));

	if (number >= 1 && number <= 5) name = "MAZE_0" + to_string(number) + ".txt";
	else valid = false;

	in_stream.open(name);

	//in_stream >> text;
}