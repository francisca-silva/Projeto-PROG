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

		if (number == 0) return -1;

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
	
	ifstream in_stream;
	string line;

	in_stream.open("RULES.txt");

	while(getline(in_stream,line)) cout << line << endl;

	in_stream.close();

}

void Show_Scoreboard(const int num_maze)
{
	string filename, line; // name of the file to be accessed and each line of it
	ifstream in_stream;

	if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + "_WINNERS.txt"; //composing the name of the file according to the number of the chosen maze
	else filename = "MAZE_0" + to_string(num_maze) + "_WINNERS.txt";

	in_stream.open(filename);

    if (!in_stream) { // if the file doesn't exist
		cout << "Empty list." << endl;
	}

	while(getline(in_stream, line)) cout << line << endl;

	in_stream.close();

}


bool menu() {
	char input;  // stores the value choosen by the player
	bool valid = false;

	while (true) {  // Shows the menu
		
		cout << "1) Rules" << endl;
		cout << "2) Play" << endl;
		cout << "3) Winners" << endl;
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
		case '3':
			int numberofmaze;
			valid = false;
			
			while(!valid){
				
				valid = true;
				cout << "Please choose the number of the maze to see the respective scoreboard of winners: " <<endl;
				cin >> numberofmaze;
				cout << endl;

				if (cin.eof()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
					break;
				}
				if (cin.fail()) {  // if the input is not an integer number, the cycle produces an error message 
					cin.clear();
					cout << "Invalid input(not an integer)." << endl << endl;
					valid = false;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			Show_Scoreboard(numberofmaze);
			cout << endl;
			break;
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

		if (!game.isValid()){
			cout << "This maze is not valid!" << endl;
			cout <<endl;
			continue;
		}
		
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
