#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <ios>
#include <limits>



#include "PLAYER.hpp"
#include "ROBOTS.hpp"
#include "POST.hpp"
#include "MAZE.hpp"
#include "GAME.hpp"

using namespace std;

int chooseMaze() {

	int number; // number id of the maze to be used
	string filename;  // name of the file containing the maze
	ifstream in_stream; // stream that reads the contents of the file
	bool valid;  // used to repeat the do while cycle until the user types the right maze
	char check;  // used to give the user a chance to say if they choose the wanted maze

	do {    // checks if the input of the number of the maze is valid and when it reaches it, leaves the cycle
		valid = true;  // valid starts as true but is changed if any of the conditions is not met
		cout << "Please choose the number(an integer value) of the maze you want to use:(1-6) ";
		cin >> number;
		 
		if (cin.eof()) {   // if the user types CTRL-Z it leaves the function with -1, leading to the menu(on the main function)
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return -1;
		}
		if (cin.fail()) {  // if the input is not an integer number, the cycle produces an error message 
			cin.clear();
			cout << "Invalid input(not an integer)." << endl << endl;
			valid = false;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignores everything other than the first character

		if (valid) {  // checks if the file exists
			if (number > 9) filename = "MAZE_" + to_string(number) + ".txt"; // if more than 10 mazes were made this would access them
			else filename = "MAZE_0" + to_string(number) + ".txt";  // otherwise this would compose the respetive maze's name (according to the chosen number)

			in_stream.open(filename);
			if (!in_stream){
				cout << "This maze doesn't exist" << endl << endl;
				valid = false;
			}
			in_stream.close();
		}

		if (valid) {  // gives the user the possibility to confirm if the maze choice is correct
			while (true) {
				cout << "Open " << filename << " ?(y/n) "; cin >> check;
				if (cin.eof()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					return -1;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (tolower(check) == 'n') {  // it accepts inputs such as "yes"(because of cin.ignore), "Y"(tolower()), "NO", etc
					valid = false;
					break;
				}
				else if(tolower(check) == 'y') break;
				else cout << "Invalid input." << endl << endl;
			}
		}
	} while (!valid);

	return number;
}


void rules() {
	cout << "The player is placed in maze of high-voltage fences and posts.There are also some interceptor robots that will try to destroy the player." <<
		"If the player touches the maze or any of these robots, that is the end of the game." <<
		"The robots are also destroyed when they touch the fences / post or when they collide with each other." <<
		"Every time the player moves in any direction(horizontally, vertically, or diagonally) to a contiguous cell, each robot moves one cell closer to the new player's location, in whichever direction is the shortest path." <<
		"The robots have no  vision sensors but they have an accurate odour sensor that allows them to follow the player!" <<
		"There is one hope : make the robots hit the maze or each other. If all of them are destroyed, the player wins !!" << endl;
}


bool menu() {
	char input;  // stores the value choosen by the player

	while (true) {  // Shows the menu
		cout << "1) Rules" << endl;
		cout << "2) Play " << endl;
		cout << "0) Exit;" << endl;

		cin >> input;
	
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores anything other than the first character
		if (cin.eof()) return false;  // if the user typed CTRL-Z it ends the program

		switch (input) {  //according to the option chosen goes to the rules, the game or allows the player to exit the game. Otherwise it is an invalid input.
		case '1':
			rules();
			break;
		case '2':
			return true;
		case '0':
			return false;
		default:
			cout << "Invalid input"; // if input is not 1, 2 or 0, is not valid and asked again
			break;
		}
	}
}


int main()
{

	int num_maze;  // number id to be chosen by the player
	bool win; //whether the player wins the game or not

	cout << "Hello friends, welcome to the most amazing game you are ever going to play. Are u ready?" << endl; //super oustanding introduction

	while (true) { // this cycle allows the user to play various games even with different mazes
		string filename; 
		
		if (!menu()) break; // if menu returns false it means the player wants to exit the game

		num_maze = chooseMaze();
		if (num_maze == -1) continue; // if the user types CTRL-Z this function will return -1, meaning it exits this game and shows the menu

		if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + ".txt";
		else filename = "MAZE_0" + to_string(num_maze) + ".txt";

        Game game(filename);
		
		time_t start = time(NULL); 
		win = game.play();
		time_t end = time(NULL); 
		int time = difftime(end, start); //calculates the game duration

		if(win) { // in case the player doesn't win the game continues
			if(!game.scoreboard(num_maze, time)) continue; // if the user types CTRL-Z this function will return false, meaning it exits this game and shows the menu
		}
		
		//game.~Game();
		
	}	
	return 0;
}
