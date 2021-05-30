//T04_G12
#include "GAME.hpp"

using namespace std;

/** 
Gives the user the option to choose the maze he wants to play.
@return number - number id of the maze to be used
*/
int chooseMaze() {

	int number;	// number id of the maze to be used
	string filename;	// name of the file containing the maze
	ifstream in_stream;	// stream that reads the contents of the file
	bool valid;	// used to repeat the do while cycle until the user types the right maze
	char check;	// used to give the user a chance to say if they choose the wanted maze

	do {	// checks if the input of the number of the maze is valid and when it reaches it, leaves the cycle
		valid = true;	// valid starts as true but is changed if any of the conditions is not met
		cout << "Please choose the number(an integer value) of the maze you want to use: ";
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

		if (number == 0) return -1;	//means the user wants to leave

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

		if(valid){	// checks if the maze is valid or not
			if (number > 9) filename = "MAZE_" + to_string(number) + ".txt";
			else filename = "MAZE_0" + to_string(number) + ".txt";

			Game game(filename);

			if (!game.isValid()){
				cout << "This maze is not valid!" << endl;
				cout <<endl;
				continue;
			}
		}

	} while (!valid);
	
	return number;	//id number chosen by user
}

/** 
Only shows the rules of the game.
@return void 
*/
void rules() {
	
	ifstream in_stream; //stores the
	string line;

	in_stream.open("RULES.txt");

	while(getline(in_stream,line)) cout << line << endl;

	cout << endl;

	in_stream.close();

}

/*
Shows the scoreboard if it exists
@param num_maze - number of the maze choosen
*/
void Show_Scoreboard(const int num_maze)
{
	bool empty = true;
	string filename, line; // name of the file to be accessed and each line of it
	ifstream in_stream;

	if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + "_WINNERS.txt"; //composing the name of the file according to the number of the chosen maze
	else filename = "MAZE_0" + to_string(num_maze) + "_WINNERS.txt";

	in_stream.open(filename);

	while(getline(in_stream, line)) {
		if (line[21] == 'e' || line[21] == '-') continue;	// this will ignore the first 2 lines
		else empty = false;	//if any other line exists then the list isn't empty
	}

	in_stream.close(); 
	
	if(empty) cout << "Empty list." << endl;
	else{
		in_stream.open(filename);
		while(getline(in_stream, line)) cout << line << endl;
		in_stream.close();
	}
}

/** 
Shows menu options and redirects the game flow. If user chooses "1)Rules" it shows the rules of the game.
@return true - the user choose to play
@return false - the user choose to exit the game
*/
bool menu() {
	char input;  // stores the value choosen by the player
	bool valid = false; 

	while (true) {  // Shows the menu
		
		cout << "1) Rules" << endl;
		cout << "2) Play" << endl;
		cout << "3) Winners" << endl;
		cout << "0) Exit;" << endl;
		
		cin >> input;
	
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// ignores anything other than the first character
		if (cin.eof()) return false;	// if the user typed CTRL-Z it ends the program

		switch (input) {	//according to the option chosen goes to the rules,the scoreboard, the game or allows the player to exit the game. Otherwise it is an invalid input.
		case '1':
			rules();		//shows the rules	
			break;
		case '2':
			return true;
		case '3':
			int numberofmaze;	//stores the number of the maze chosen by the user
			valid = false;
			
			while(!valid){		//cycle that assures that the number chosen by the user to see the scoreboard of winners is valid
				
				valid = true;
				cout << "Please choose the number of the maze to see the respective scoreboard of winners: " <<endl;
				cin >> numberofmaze;
				cout << endl;

				if (cin.eof()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					return false;
				}
				if (cin.fail()) {// if the input is not an integer number, the cycle produces an error message 
					cin.clear();
					cout << "Invalid input(not an integer)." << endl << endl;
					valid = false;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			Show_Scoreboard(numberofmaze);		//shows scoreboard of winners according to the chosen maze
			cout << endl;
			break;
		case '0':
			return false;
		default:
			cout << "Invalid input" << endl;	//if input is not 1, 2, 3 or 0, is not valid and asked again
			break;
		}
	}
}