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

#include "MAZE.hpp"
#include "POST.hpp"


Maze::Maze()
{
    numCols = 0;
    numRows = 0;
}

void Maze::addPost(const Post& post)
{
    posts.pushback(post);
}

inline int Maze::getnumRows() const
{
    return numRows;
}

inline int Maze::getnumCols() const
{
    return numCols;
}

inline void Maze::setnumCols(int c)
{
    numCols = c;
} 

inline void Maze::setnumRows(int d)
{
    numRows = d;
}


inline Post Maze::getPost(int id)
{
    return posts[id];
}

inline int Maze::getnumPosts() const
{
    return posts.size();
}

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
