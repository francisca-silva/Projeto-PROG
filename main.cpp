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
// POR DESCRICOES DAS LETRAS NAS REGRAS
// ultima linha do maze

struct Fence {
	int pos_i, pos_j;
	bool working = true;
};

struct Player
{
	int pos_i, pos_j;
	bool alive = true;
};

struct Robot {
	int pos_i, pos_j;
	bool alive = true;
};

//void readMaze(string filename);
bool menu();
void rules();

bool menu() {
	char c;

	while (true) {
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
			break;
		}
	}

}

void rules() {
	cout << "The player is placed in maze of high-voltage fences and posts.There are also some interceptor robots that will try to destroy the player." <<
		"If the player touches the maze or any of these robots, that is the end of the game." <<
		"The robost are also destroyed when they touch the fences / post or when they collide with each other." <<
		"Every time the player moves in any direction(horizontally, vertically, or diagonally) to a contiguous cell, each robot moves one cell closer to the new player's location, in whichever direction is the shortest path." <<
		"The robots have no  vision sensors but they have an accurate odour sensor that allows them to follow the player!" <<
		"There is one hope : make the robots hit the maze or each other.If all of them are destroyed, the player wins !!" << endl;
}


string chooseMaze() {

	int number, numberOfMaze = 5;
	string filename;
	ifstream in_stream;
	bool valid;

	do {
		cout << "Please choose the number(an integer value) of the maze you want to use(1-5): " << endl;
		cin >> number;
		cin.clear();
		cin.ignore(1000000000, '\n');
		if (cin.fail()) {
			valid = false;
			cout << "Invalid input." << endl;
		}

		// o utilizador pode ter posto um numero primeiro dps um espa�o e dps outra coisa qqr e isso n da erro a primeira mas devia
		// temos de encontrar uma forma de evitar isso

	} while (!valid && (number < 1 || number > numberOfMaze));

	if (number >= 1 && number <= numberOfMaze) filename = "MAZE_0" + to_string(number) + ".txt";
	else valid = false;

	return filename;
}

void ReadMaze(string filename, Player& player, vector <Robot>& robots, vector <Fence>& fences) {

	ifstream in_stream;
	int numcol = 0, numrow = 0;
	string row;
	size_t size;
	Robot robot;
	Fence fence;

	cout << filename;

	in_stream.open(filename);

	getline(in_stream, row);
	cout << row << endl;
	while (!in_stream.eof()) {

		char c = '.';
		numcol = 0;

		while (c != '\0') {
			c = row[numcol];
			
			switch (c)
			{
			case 'H':
				player.pos_i = numrow;
				player.pos_j = numcol;
				break;
			case 'R':
			
				robots.push_back(Robot());
				size = robots.size();
				robot.pos_i = numrow;
				robot.pos_j = numcol;
				robots[size - 1] = robot;
				break;
			case '*':
				
				fences.push_back(Fence());
				size = fences.size();
				fence.pos_i = numrow;
				fence.pos_j = numcol;
				fences[size - 1] = fence;
				break;
			default:
				break;
			}
			numcol++;
		}

		numrow++;
		getline(in_stream, row);
	}
	in_stream.close();

	cout << endl << numcol << " " << numrow << endl;
}

bool NewPlayerPosition(Player& player) {

	char input;
	bool valid = false;
	
	while (!valid){

		cout << "Please choose one of the following positions:" << endl;
		cout << "Valid positions: \n Q W E \n A S D \n Z X C" <<endl;
		cin >> input;
		valid = true;

		if (cin.eof()) return menu();

		switch (toupper(input)){
			case 'Q': 
				player.pos_i += -1;
				player.pos_j += -1;
				break;
			case 'W': 
				player.pos_i += -1;
				break;
			case 'E':
				player.pos_i += -1;
				player.pos_j += 1;
				break;
			case 'A':
				player.pos_j += -1;
				break;
			case 'S': break;
			case 'D': 
				player.pos_j += 1;
				break;
			case 'Z': 
				player.pos_i += 1;
				player.pos_j += -1;
				break;
			case 'X': 
				player.pos_i += 1;
				break;
			case 'C': 
				player.pos_i += 1;
				player.pos_j += 1;
				break;
			default:
				cout << "Invalid input" << endl;
				valid = false;
				break;
		}
		
	}
	return true;
		
}


void drawMaze(int numcol, int numrow, Player& player, vector <Robot>& robots, vector <Fence>& fences)
{
	vector <vector <char>> maze(numrow,vector<char>(numcol));


	for (int i = 0; i < numrow; i++){
		for (int j = 0; j < numcol; j++) maze[i][j] = ' ';		
	}
	 
	
	maze[player.pos_i][player.pos_j] = 'H';
	for (int i = 0; i < robots.size(); i++) {
		if (robots[i].alive) maze[robots[i].pos_i][robots[i].pos_j] = 'R';
		else maze[robots[i].pos_i][robots[i].pos_j] = 'r';
	}
	for (int i = 0; i < fences.size(); i++) {
		maze[fences[i].pos_i][fences[i].pos_j] = '*';
	}

	for (int i = 0; i < numrow; i++){
		for (int j = 0; j < numcol; j++){
			cout << maze[i][j];	
		} 	
		cout << endl;
	}
	
}


int main()
{
	bool play;
	Player player;
	vector <Robot> robots;
	vector <Fence> fences;

	play = menu();

	cout << "Hello friends, welcome to the most amazing game you are ever going to play.Are u ready?" << endl;

	ReadMaze(chooseMaze(),player,robots, fences);

	while (play){

		drawMaze(20,10,player,robots,fences);

		play = NewPlayerPosition(player);
	
		
	}


	return 0;
}

