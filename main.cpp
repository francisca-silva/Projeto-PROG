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

using namespace std;

// POR DESCRICOES DAS LETRAS NAS REGRAS

struct Maze_Size;
struct Fence;
struct Player;
struct Robot;
struct Player_Info;


/** 
Shows menu options and redirects the game flow. If user chooses "1)Rules" it shows the rules of the game.
@return true - the user choose to play
@return false - the user choose to exit the game
*/
bool menu();


/** 
Only shows the rules of the game.
@return void 
*/
void rules();


/** 
Gives the user the option to choose the maze he wants to play.
@return number - number id of the maze to be used
*/
int chooseMaze();


/** 
Opens and reads the file where the maze is.
@param filename - name of the file to be opened
@param player - object player passed by reference to change it's position 
@param robots - vector passed by reference to be filled with all the robots on the maze and their positions
@param fences - vector passed by reference to be filled with all the fences on the maze and their positions
@return the number of columns and rows of a maze using the struct size_info (of tipe Maze_Size)
*/
Maze_Size readMaze(const string filename, Player& player, vector <Robot>& robots, vector <Fence>& fences);


/** 
Fills a bidimentional vector(same size as the maze) with spaces, and then with all the fences, robots and the player.
Then it shows the vector on the screen
@param numcol - number of columns
@param numrow - number of rows
@param player - object passed by reference to use the player position
@param robots - vector passed by reference to use the robots' position
@param fence - vector passed by reference to use the fences' position
@return void
*/
void drawMaze(const int numcol, const int numrow, Player& player, vector <Robot>& robots, vector <Fence>& fences);


/** 
Plays one game using the choosen maze.
@param numcol - number of columns
@param numrow - number of rows
@param player - uses the player and it's functions
@param robots - uses and changes the robots and their status
@param fences - uses the fences positions
@return true - if the player wins
@return false - if the player leaves the game or loses it   
*/
bool play(const int numcol, const int numrow, Player& player, vector <Robot>& robots, vector <Fence>& fences); 


/** 
Updates and presents the scoreboard of the winners of the game and the time they took to do so.
@param num_maze - used to create the filename of the scoreboard file to be accessed
@param time - number of seconds the player took to finish the game 
@return true - if it was able to finish the function correctly
@return false - if the user typed CTRL-Z in any of the moments that asked for input, this function exits with false before updating the scoreboard
*/
bool scoreboard(const int num_maze, const int time);


// -----------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION DEFINITIONS


struct Maze_Size { //Declare Maze_Size struct
	int numcol; // declare member types numcol and numrow
	int numrow;
};

struct Fence {  // Declare Fence struct
	int pos_i, pos_j; //pos_i is the index of the row and pos_j is the index of the column
};


struct Player {
	int pos_i, pos_j, last_pos_i, last_pos_j; //pos_i is the index of the row, pos_j is the index of the column, the last_pos_x are used to store the value of the last position in case of input error
	bool alive = true;  // whether or not the player is dead or alive


/** 
Updates the players' position for each move
@param fences - used to check if the player tried to move to a fences position
@return true - if it was able to finish the function correctly
@return false - if the user typed CTRL-Z in any of the moments that asked for input, this function exits with false before changing the player's position
*/
	bool newPlayerPosition(vector <Fence>& fences) {

		char input;   // this will store the key pressed by the player(to determine the next position)
		bool valid = false;  // used to check if the input is valid depending on the possible positions
		
		while (!valid){    //this cycle only ends when the player chooses a valid position

			last_pos_i = pos_i;
			last_pos_j = pos_j;

			cout << "Please choose one of the following positions:\n Q W E \n A S D \n Z X C" << endl;
			cin >> input;
			valid = true;

			if (cin.eof()) {  //checks if the player wants to exit this game
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				return false;  // means the user wants to leave the game
			}

			switch (toupper(input)){  // calculates the new player position
				case 'Q': 
					pos_i += -1;  // depending on the key, this will change the position
					pos_j += -1;
					break;
				case 'W': 
					pos_i += -1;
					break;
				case 'E':
					pos_i += -1;
					pos_j += 1;
					break;
				case 'A':
					pos_j += -1;
					break;
				case 'S': break;
				case 'D': 
					pos_j += 1;
					break;
				case 'Z': 
					pos_i += 1;
					pos_j += -1;
					break;
				case 'X': 
					pos_i += 1;
					break;
				case 'C': 
					pos_i += 1;
					pos_j += 1;
					break;
				default:
					cout << "Invalid input" << endl << endl;
					valid = false;  // if the player doesn't choose one of the valid positions the input is not valid
					break;
			}

			cin.ignore(numeric_limits<streamsize>::max(),'\n');  // ignores any other input besides the first character(if the first is valid the rest is just ignored)

			for (size_t i = 0; i < fences.size(); i++) {  // warns the player if he goes against any fence
				if (fences[i].pos_i == pos_i && fences[i].pos_j == pos_j){
					cout << "Invalid input(can't go to fence)" << endl << endl;
					valid = false;
					pos_i = last_pos_i;  // resets the position for the next cycle iteration
			    	pos_j = last_pos_j;
					break;
				}
			}
		}
		return true; // means the function was successful
	}
};

struct Robot {
	int pos_i, pos_j, index; //pos_i is the index of the row, pos_j is the index of the column, index is the index in the vector of Robots
	bool alive = true;  // whether or not the robot is working
	
	
/** 
Updates the robot's position for each player move
@param player - used to update the robot's position and to check if there is a collision
@param robots - used to check if the robot collides with any of the other robots
@param fences - used to check if the robot collides with any of the fences
@return void
*/
	void NewRobotPosition(Player &player, vector <Robot>& robots, vector <Fence>& fences){
		
		int newPos[9][2] = {{pos_i-1,pos_j-1},{pos_i-1,pos_j},{pos_i-1,pos_j+1},{pos_i,pos_j-1}, {pos_i,pos_j}, 
							{pos_i,pos_j+1},{pos_i+1,pos_j-1},{pos_i+1,pos_j},{pos_i+1,pos_j+1}};   // this is an easy way to calculate the possible positions for each robot

		int min_index;  // index of the position with the shorter distance
		double dist,min_dist = __DBL_MAX__; // distance between a position and the player
	
		for (int i = 0; i < 9; i++){           // for each possible position
			dist = sqrt(pow(newPos[i][0]-player.pos_i,2) + pow(newPos[i][1]-player.pos_j,2)); //this calculates the distance to the player
			if (dist < min_dist) {  // checks if this position is the shortest to the moment
				min_dist = dist;  // stores this distance as the shortest
				min_index = i;    // and i as it's index
			}
		}
		
		pos_i = newPos[min_index][0];  // stores the new position of the robot
		pos_j = newPos[min_index][1]; 
		
		for (size_t i = 0; i < fences.size(); i++) {      // checks if the robot collides with the fence
			if (fences[i].pos_i == pos_i && fences[i].pos_j == pos_j){  
				alive = false;  // in case of collision, the robot dies
				break;
			}
		}

		for (size_t i = 0; i < robots.size(); i++) {  // check if collides with another robot
			if (robots[i].index != index && robots[i].pos_i == pos_i && robots[i].pos_j == pos_j) {
				alive = false;  
				robots[i].alive = false;  // if it collides, both die
				break;
			}
		}

		if (player.pos_i == pos_i && player.pos_j == pos_j){  // checks for collision with the player
			player.alive = false;
		}
	}
};

struct Player_Info{
	string name;  //players' name and the time it took to complete the maze
	int score;
};


/** 
Shows menu options and redirects the game flow. If user chooses "1)Rules" it shows the rules of the game.
@return true - the user choose to play
@return false - the user choose to exit the game
*/
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


/** 
Only shows the rules of the game.
@return void 
*/
void rules() {
	cout << "The player is placed in maze of high-voltage fences and posts.There are also some interceptor robots that will try to destroy the player." <<
		"If the player touches the maze or any of these robots, that is the end of the game." <<
		"The robots are also destroyed when they touch the fences / post or when they collide with each other." <<
		"Every time the player moves in any direction(horizontally, vertically, or diagonally) to a contiguous cell, each robot moves one cell closer to the new player's location, in whichever direction is the shortest path." <<
		"The robots have no  vision sensors but they have an accurate odour sensor that allows them to follow the player!" <<
		"There is one hope : make the robots hit the maze or each other. If all of them are destroyed, the player wins !!" << endl;
}


/** 
Gives the user the option to choose the maze he wants to play.
@return number - number id of the maze to be used
*/
int chooseMaze() {

	int number; // number id of the maze to be used
	string filename;  // name of the file containing the maze
	ifstream in_stream; // stream that reads the contents of the file
	bool valid;  // used to repeat the do while cycle until the user types the right maze
	char check;  // used to give the user a chance to say if they choose the wanted maze

	do {    // checks if the input of the number of the maze is valid and when it reaches it, leaves the cycle
		valid = true;  // valid starts as true but is changed if any of the conditions is not met
		cout << "Please choose the number(an integer value) of the maze you want to use: ";
		cin >> number;
		 
		if (cin.eof()) {   // if the user types CTRL-Z it leaves the function with -1, leading to the menu(on the main function)
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return -1;
		}
		if (cin.fail()) {  // if the input is invalid, the cycle produces an error message 
			cin.clear();
			cout << "Invalid input(not an integer)." << endl << endl;
			valid = false;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (valid) {  
			if (number > 9) filename = "MAZE_" + to_string(number) + ".txt";
			else filename = "MAZE_0" + to_string(number) + ".txt";

			in_stream.open(filename);
			if (!in_stream){
				cout << "This maze doesn't exist" << endl << endl;
				valid = false;
			}
			in_stream.close();
		}

		if (valid) {
			while (true) {
				cout << "Open " << filename << " ?(y/n) "; cin >> check;
				if (cin.eof()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					return -1;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (tolower(check) == 'n') {
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


/** 
Opens and reads the file where the maze is.
@param filename - name of the file to be opened
@param player - object player passed by reference to change it's position 
@param robots - vector passed by reference to be filled with all the robots on the maze and their positions
@param fences - vector passed by reference to be filled with all the fences on the maze and their positions
@return the number of columns and rows of a maze using the struct size_info (of tipe Maze_Size)
*/
Maze_Size readMaze(const string filename, Player& player, vector <Robot>& robots, vector <Fence>& fences) {

	ifstream in_stream;
	int numcol = 0, numrow = 0;
	string row;
	size_t size;
	Robot robot;
	Fence fence;
	Maze_Size size_info;

	cout << endl << filename << endl;

	in_stream.open(filename);

	while (getline(in_stream, row)) {
		
		numcol = 0;
		char c = row[numcol];

		do {
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
				robot.index = size - 1;
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
			c = row[numcol];

		} while (c != '\0');

		numrow++;
	} 
	
	in_stream.close();

	cout << numcol << " x " << numrow << endl << endl;

	size_info.numcol = numcol;
	size_info.numrow = numrow;

	return size_info;
}


/** 
Fills a bidimentional vector(same size as the maze) with spaces, and then with all the fences, robots and the player.
Then it shows the vector on the screen.
@param numcol - number of columns
@param numrow - number of rows
@param player - object passed by reference to use the player position
@param robots - vector passed by reference to use the robots' position
@param fence - vector passed by reference to use the fences' position
@return void
*/
void drawMaze(const int numcol, const int numrow, Player& player, vector <Robot>& robots, vector <Fence>& fences) {
	vector <vector <char>> maze(numrow,vector<char>(numcol));


	for (int i = 0; i < numrow; i++){
		for (int j = 0; j < numcol; j++) maze[i][j] = ' ';		
	}
	 
	for (size_t i = 0; i < fences.size(); i++) {
		maze[fences[i].pos_i][fences[i].pos_j] = '*';
	}

	for (size_t i = 0; i < robots.size(); i++) {
		if (robots[i].alive) maze[robots[i].pos_i][robots[i].pos_j] = 'R';
		else maze[robots[i].pos_i][robots[i].pos_j] = 'r';
	}
	
	if (player.alive) maze[player.pos_i][player.pos_j] = 'H';
	else maze[player.pos_i][player.pos_j] = 'h';

	cout << endl;
	for (int i = 0; i < numrow; i++){
		for (int j = 0; j < numcol; j++){
			cout << maze[i][j];	
		} 	
		cout << endl;
	}
}


/** 
Plays one game using the choosen maze.
@param numcol - number of columns
@param numrow - number of rows
@param player - uses the player and it's functions
@param robots - uses and changes the robots and their status
@param fences - uses the fences positions
@return true - if the player wins
@return false - if the player leaves the game or loses it   
*/
bool play(const int numcol, const int numrow, Player& player, vector <Robot>& robots, vector <Fence>& fences){

	bool alldead, play = true;

	while (play){

		alldead = true;
	
		drawMaze(numcol,numrow,player,robots,fences);

		if (!player.alive) {
			cout << "You lost!" << endl << endl;
			return false;
		}
		
		if (!player.newPlayerPosition(fences)) return false;
		

		for (size_t i = 0; i < robots.size(); i++){
			
			if (robots[i].alive) robots[i].NewRobotPosition(player, robots, fences);
				
		}  
		
		for (size_t i = 0; i < robots.size(); i++) if (robots[i].alive) alldead = false;

		if (alldead) {
			drawMaze(numcol,numrow,player,robots,fences);
			cout << "You won!!" << endl <<endl;
			return true;
		}
	}
}


/** 
Updates and presents the scoreboard of the winners of the game and the time they took to do so.
@param num_maze - used to create the filename of the scoreboard file to be accessed
@param time - number of seconds the player took to finish the game 
@return true - if it was able to finish the function correctly
@return false - if the user typed CTRL-Z in any of the moments that asked for input, this function exits with false before updating the scoreboard
*/
bool scoreboard(const int num_maze,const int time){
	
    vector <Player_Info> score_info;
    Player_Info p_info;
	string filename, line;

	// reading the file
	ifstream in_stream;
	int index = 0;

	if (num_maze > 9) filename = "Scoreboard_" + to_string(num_maze) + ".txt";
	else filename = "Scoreboard_0" + to_string(num_maze) + ".txt";

	in_stream.open(filename);

    if (!in_stream) {
		ofstream newfile;
		newfile.open(filename);
		newfile.close();
	}
	in_stream.close();


	in_stream.open(filename);

    while(getline(in_stream, line)) {
        if (line[21] == 'e' || line[21] == '-') continue;
        p_info.name = line.substr(0,15); 
		p_info.score = stoi(line.substr(18,4), nullptr);
		score_info.push_back(p_info);
        line = "                      ";
	}
	
	in_stream.close();
	
	// working the player's info
	bool valid;
	do {
		valid = true;
		cout << "Insert name(max 15 characters): ";
		getline(cin, line);

		if (cin.eof()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return false;
		}

		if (line.size() == 0) {
			cout << "Invalid input(no characters)" << endl;
			valid = false;
		}
		else if (line.size() > 15) {
			cout << "Invalid input(too many characters)" << endl;
			valid = false;
		}

		line.resize(15,' ');

		for (size_t i = 0; i < score_info.size();i++){
			if (score_info[i].name == line) {
				cout << "Invalid input(already existing name)" << endl;
				valid = false;
				break;
			}
		}
	} while (!valid);

	p_info.name = line; 
	p_info.score = time;

	for (size_t i = 0; i < score_info.size(); i++){
		//if (time == score_info[i].score) {
		//	if (p_info.name > )
		//}
		if (time <= score_info[i].score) {
			index = i;
			cout << index << endl;
			break;
		}
	}
	score_info.insert(score_info.begin() + index, p_info);
	
	// Rewriting(mostrar ao utilizador tambem)
	
	ofstream write_stream;

	write_stream.open(filename);

	write_stream << "Player          - Time\n----------------------";

	for (size_t i = 0; i < score_info.size();i++){
		write_stream << endl;
		write_stream << fixed << setw(15) << setfill(' ') << left << score_info[i].name;
		write_stream << fixed << setw(3) << " - ";
		write_stream << fixed << setw(4) << setfill(' ') << right << to_string(score_info[i].score);
	}

	write_stream.close();

	in_stream.open(filename);
    while(getline(in_stream, line)) {
        cout << endl << line;
	}
	cout << endl << endl;
	in_stream.close();

	return true;
}

int main()
{
	Player player;
	vector <Robot> robots;
	vector <Fence> fences;
	int num_maze;
	bool win;
	Maze_Size size_info;

	cout << "Hello friends, welcome to the most amazing game you are ever going to play.Are u ready?" << endl;

	while (true) {
		string filename;
		
		if (!menu()) break;

		num_maze = chooseMaze();
		if (num_maze == -1) continue;

		if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + ".txt";
		else filename = "MAZE_0" + to_string(num_maze) + ".txt";

		size_info = readMaze(filename,player,robots,fences);
		
		time_t start = time(NULL);
		win = play(size_info.numcol,size_info.numrow,player,robots,fences);
		time_t end = time(NULL);
		int time = difftime(end, start);

		if(win) {
			if(!scoreboard(num_maze, time)) continue;
		}
		
		player.alive = true;
		robots.clear();
		fences.clear();
		
	}	
	return 0;
}


