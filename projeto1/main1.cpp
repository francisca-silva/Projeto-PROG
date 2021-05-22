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


/** DONEEEE
Opens and reads the file where the maze is.
@param filename - name of the file to be opened
@param player - object player passed by reference to change it's position 
@param robots - vector passed by reference to be filled with all the robots on the maze and their positions
@param fences - vector passed by reference to be filled with all the fences on the maze and their positions
@return the number of columns and rows of a maze using the struct size_info (of tipe Maze_Size)
*/
Maze_Size readMaze(const string filename, Player& player, vector <Robot>& robots, vector <Fence>& fences);


/**  DONEEEE
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


struct Maze_Size { 
	int numcol; 
	int numrow;
};

struct Fence {  
	int pos_i, pos_j; //pos_i is the index of the row and pos_j is the index of the column
};


struct Player {
	int pos_i, pos_j, last_pos_i, last_pos_j; //pos_i is the index of the row, pos_j is the index of the column, the last_pos_x are used to store the value of the last position in case of input error
	bool alive = true;  // whether or not the player is dead or alive


/**   DONEEEEE
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
	
	
/**   DONEEEEEE
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
// POR DESCRICOES DAS LETRAS NAS REGRAS

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

/** 
Opens and reads the file where the maze is.
@param filename - name of the file to be opened
@param player - object player passed by reference to change it's position 
@param robots - vector passed by reference to be filled with all the robots on the maze and their positions
@param fences - vector passed by reference to be filled with all the fences on the maze and their positions
@return the number of columns and rows of a maze using the struct size_info (of tipe Maze_Size)
*/
Maze_Size readMaze(const string filename, Player& player, vector <Robot>& robots, vector <Fence>& fences) {

	ifstream in_stream; // stream that reads the contents of the chosen file 
	int numcol = 0, numrow = 0; //number of columns and rows
	string row;  // to store the value of each row at a time
	Robot robot;  //creates a generic robot to help fill the vector of robots
	Fence fence;  //creates a generic fence for the same purpose
	Maze_Size size_info;  // used at the end to return the proportions of the maze

	cout << endl << filename << endl; //prints the name of the maze

	in_stream.open(filename);

	while (getline(in_stream, row)) { // cycle that analyses the maze, collecting its different elements from line to line
		
		numcol = 0; // starts as 0 in every iteration of the while cycle
		char object = row[numcol];  // used to store the value of each space in the maze

		do {  // until the last element of each line
			switch (object)
			{
			case 'H': 
				player.pos_i = numrow; // sets the player's position
				player.pos_j = numcol;
				break;

			case 'R': 
				robot.pos_i = numrow;  // sets the generic robot's position and index on the vector of Robots
				robot.pos_j = numcol;
				robot.index = robots.size() - 1;
				robots.push_back(robot);  // adds the robot to the vector
				break;
				
			case '*': // 
				fence.pos_i = numrow;  // sets the generic fence's position
				fence.pos_j = numcol;
				fences.push_back(fence);  // and adds it to the vector of Fences
				break;
			default: // if it is ' ' it is ignored
				break;
			}
			numcol++;  //increments the number of columns
			object = row[numcol];  // reads the next element

		} while (object != '\0'); // repeats until the end of the string

		numrow++; //increments the number of rows
	} 
	
	in_stream.close(); 

	cout << numcol << " x " << numrow << endl << endl; //prints the number of columns and rows

	size_info.numcol = numcol; // stores numcol and numrow on the the size_info
	size_info.numrow = numrow;

	return size_info;  // returns the size of the maze
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
	
	vector <vector <char>> maze(numrow,vector<char>(numcol)); // this vector will be written in each function call

	for (int i = 0; i < numrow; i++){    // fills with blank spaces the number of columns and rows
		for (int j = 0; j < numcol; j++) maze[i][j] = ' ';		
	}
	 
	for (size_t i = 0; i < fences.size(); i++) {  // then it writes on top of the ' ' all of the fences
		maze[fences[i].pos_i][fences[i].pos_j] = '*';
	}

	for (size_t i = 0; i < robots.size(); i++) {  // if any robot dies because of a fence, it is written on top of it(and the fence disappears)
		if (robots[i].alive) maze[robots[i].pos_i][robots[i].pos_j] = 'R';
		else maze[robots[i].pos_i][robots[i].pos_j] = 'r';
	}
	
	if (player.alive) maze[player.pos_i][player.pos_j] = 'H'; // lastly if the player is dead because of a robot(in the same position) it is written on top of it
	else maze[player.pos_i][player.pos_j] = 'h';

	cout << endl;
	for (int i = 0; i < numrow; i++){       // prints the maze
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

	bool alldead; // to check if all of the robots are dead

	while (true){  // plays until the function returns true or false depending on the output

		alldead = true; //assuming all robots are dead
	
		drawMaze(numcol,numrow,player,robots,fences); // call to function in order to draw the chosen maze

		if (!player.alive) {
			cout << "You lost!" << endl << endl;
			return false;  
		}
		
		if (!player.newPlayerPosition(fences)) return false; // this function's purpose is to move the player but if the user typed CTRL-Z it immediately ends the play() function and returns false
		

		for (size_t i = 0; i < robots.size(); i++){  // moves each robot 
			
			if (robots[i].alive) robots[i].NewRobotPosition(player, robots, fences);
				
		}  
		
		for (size_t i = 0; i < robots.size(); i++) if (robots[i].alive) alldead = false;  // if any robot is still alive then they're not all dead

		if (alldead) {
			drawMaze(numcol,numrow,player,robots,fences); // shows the final maze before leaving the function
			cout << "You won!!" << endl <<endl;
			return true;  // this true will call the scoreboad() function to add the player's name and score
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
	
    vector <Player_Info> score_info; // this vector will hold all previous player information
    Player_Info p_info; // generic Player_Info to help fill the vector and eventually the current user's information
	string filename, line; // name of the file to be accessed and each line of it

	// code to read the scoreboard file
	ifstream in_stream;

	if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + "_WINNERS.txt"; //composing the name of the file according to the number of the chosen maze
	else filename = "MAZE_0" + to_string(num_maze) + "_WINNERS.txt";

	in_stream.open(filename);

    if (!in_stream) { // if the file doesn't exist
		ofstream newfile;
		newfile.open(filename);  // this will create it
		newfile.close();
	}
	in_stream.close();


	in_stream.open(filename); // now that the file exists, it can be read

    while(getline(in_stream, line)) {
        if (line[21] == 'e' || line[21] == '-') continue; // this will ignore the first 2 lines
        p_info.name = line.substr(0,15); // this slices the first 15 characters, starting at index 0
		p_info.score = stoi(line.substr(18,4), nullptr); // extracts the score
		score_info.push_back(p_info); // adds this information to the vector
	}
	
	in_stream.close(); 
	
	// code to add the player's info to the rest
	
	bool valid; // to be used in the do while cycle until the name input is valid  
	int index = 0; // inicialization of the index
	
	do {  // cycle that assures the input is valid
		valid = true;
		cout << "Insert name(max 15 characters): ";
		cin >> line;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // in case of the user typing '\t' this cleans the buffer

		if (cin.eof()) {  // if the user types CTRL-Z the function will not add this game to the scoreboard
			cin.clear();
			return false;
		}

		else if (line.size() > 15) {  // if the user types more than 15 characters
			cout << "Invalid input(too many characters)" << endl;
			valid = false;
		}

		line.resize(15,' '); // aligns the user input with the other players' names

		for (size_t i = 0; i < score_info.size();i++){  // this cycle prevents the user to put a name equal to an already existing name
			if (score_info[i].name == line) {
				cout << "Invalid input(already existing name)" << endl;
				valid = false;
				break;
			}
		}
	} while (!valid);

	p_info.name = line; // this reuses the generic Player_Info to store the information of the current player
	p_info.score = time;

	for (size_t i = 0; i < score_info.size(); i++){
		if (time <= score_info[i].score) {  // since the scoreboard is already ordered it only needs to find one score worst
			index = i;  // the current player will take it's place
			break;
		}
	}
	score_info.insert(score_info.begin() + index, p_info); 
	
	// Rewriting the scoreboard (also showing it to the user)
	
	ofstream write_stream;

	write_stream.open(filename);

	write_stream << "Player          - Time\n----------------------"; 

	for (size_t i = 0; i < score_info.size();i++){ // for each line
		write_stream << endl;
		write_stream << fixed << setw(15) << setfill(' ') << left << score_info[i].name; // this formats the information on the scoreboard
		write_stream << fixed << setw(3) << " - ";
		write_stream << fixed << setw(4) << setfill(' ') << right << to_string(score_info[i].score);
	}

	write_stream.close();

	in_stream.open(filename);
    while(getline(in_stream, line)) {
        cout << endl << line; // this shows the user the scoreboard
	}
	cout << endl << endl;
	in_stream.close();

	return true; // means the function was successful
}

int main()
{
	Player player;  
	vector <Robot> robots;  // this will hold all the robots
	vector <Fence> fences;  // this will hold all the fences
	int num_maze;  // number id to be chosen by the player
	bool win; //whether the player wins the game or not
	Maze_Size size_info;  // information on the number of columns and rows of the maze

	cout << "Hello friends, welcome to the most amazing game you are ever going to play. Are u ready?" << endl; //super oustanding introduction

	while (true) { // this cycle allows the user to play various games even with different mazes
		string filename; 
		
		if (!menu()) break; // if menu returns false it means the player wants to exit the game

		num_maze = chooseMaze();
		if (num_maze == -1) continue; // if the user types CTRL-Z this function will return -1, meaning it exits this game and shows the menu

		if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + ".txt";
		else filename = "MAZE_0" + to_string(num_maze) + ".txt";

		size_info = readMaze(filename,player,robots,fences); 
		
		time_t start = time(NULL); 
		win = play(size_info.numcol,size_info.numrow,player,robots,fences);
		time_t end = time(NULL); 
		int time = difftime(end, start); //calculates the game duration

		if(win) { // in case the player doesn't win the game continues
			if(!scoreboard(num_maze, time)) continue; // if the user types CTRL-Z this function will return false, meaning it exits this game and shows the menu
		}
		
		player.alive = true; //resets all information about the previous game
		robots.clear();
		fences.clear();
		
	}	
	return 0;
}