#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>

using namespace std;

// FUNCTION DECLARATION 
// POR DESCRICOES DAS LETRAS NAS REGRAS


//void readMaze(string filename);
bool menu();
void rules();

struct Fence {
	int pos_i, pos_j;
};

struct Player
{
	int pos_i, pos_j, last_pos_i, last_pos_j;
	bool alive = true;

	bool NewPlayerPosition(vector <Fence>& fences) {

		char input;
		bool valid = false, eof;
		
		while (!valid){

			last_pos_i = pos_i;
			last_pos_j = pos_j;

			cout << "Please choose one of the following positions:\n Q W E \n A S D \n Z X C" << endl;
			cin >> input;
			valid = true;

			if (cin.eof()) {
				cin.clear();
				cin.ignore(100000,'\n');
				return false;
			}

			switch (toupper(input)){
				case 'Q': 
					pos_i += -1;
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
					cout << "Invalid input" << endl;
					valid = false;
					break;
			}

			cin.ignore(100000,'\n');

			
			for (size_t i = 0; i < fences.size(); i++) {
				if (fences[i].pos_i == pos_i && fences[i].pos_j == pos_j){
					cout << "Invalid input(can't go to fence)" << endl;
					valid = false;
					pos_i = last_pos_i;
			    	pos_j = last_pos_j;
					break;
				}
			}
/*
			for (size_t i = 0; i < robots.size(); i++) {
				if (robots[i].pos_i == pos_i && robots[i].pos_j == pos_j){
					alive = false;

					break;
				}
			}
*/
		}

		
		return true;
			
	}
};

struct Robot {
	int pos_i, pos_j, index;
	bool alive = true;
	

	void NewRobotPosition(Player &player, vector <Robot>& robots, vector <Fence>& fences){
		
		int newPos[9][2] = {{pos_i-1,pos_j-1},{pos_i-1,pos_j},{pos_i-1,pos_j+1},{pos_i,pos_j-1}, {pos_i,pos_j},
							{pos_i,pos_j+1},{pos_i+1,pos_j-1},{pos_i+1,pos_j},{pos_i+1,pos_j+1}};

		int min_index;
		double dist,min_dist = __DBL_MAX__;
	
		for (int i = 0; i < 9; i++){
			dist = sqrt(pow(newPos[i][0]-player.pos_i,2) + pow(newPos[i][1]-player.pos_j,2));
			if (dist < min_dist) {
				min_dist = dist;
				min_index = i;
			}
		}
		
		pos_i = newPos[min_index][0];
		pos_j = newPos[min_index][1];

		for (size_t i = 0; i < fences.size(); i++) {
			if (fences[i].pos_i == pos_i && fences[i].pos_j == pos_j){
				alive = false;
				break;
			}
		}

		for (size_t i = 0; i < robots.size(); i++) {
			if (robots[i].index != index && robots[i].pos_i == pos_i && robots[i].pos_j == pos_j) {
				alive = false;
				robots[i].alive = false;
				break;
			}
		}

		if (player.pos_i == pos_i && player.pos_j == pos_j){
			player.alive = false;
		}
			

	}

};

struct Player_info{
	string name;
	int score;
};

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

		//cin.clear();
		//cin.ignore(1000000000, '\n');
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


int chooseMaze() {

	int number;
	string filename;
	ifstream in_stream;
	bool valid;

	do {
		valid = true;
		cout << "Please choose the number(an integer value) of the maze you want to use(1-5): " << endl;
		cin >> number;
		
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000000000, '\n');
			cout << "Invalid input." << endl;
			valid = false;
		}
		cin.ignore(1000000000, '\n');

		if (number > 9) filename = "MAZE_" + to_string(number) + ".txt";
		else filename = "MAZE_0" + to_string(number) + ".txt";

		in_stream.open(filename);
		if (!in_stream){
			cout << "This maze doesn't exist" << endl;
			valid = false;
		}
		in_stream.close();
		// o utilizador pode ter posto um numero primeiro dps um espaço e dps outra coisa qqr e isso n da erro a primeira mas devia
		// temos de encontrar uma forma de evitar isso

	} while (!valid);

	return number;
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

	cout << endl << numcol << " x " << numrow << endl << endl;
}



void drawMaze(int numcol, int numrow, Player& player, vector <Robot>& robots, vector <Fence>& fences)
{
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

	for (int i = 0; i < numrow; i++){
		for (int j = 0; j < numcol; j++){
			cout << maze[i][j];	
		} 	
		cout << endl;
	}
	
}

bool play(int numcol, int numrow, Player& player, vector <Robot>& robots, vector <Fence>& fences){

	bool alldead, play = true;

	while (play){

		alldead = true;
	
		drawMaze(numcol,numrow,player,robots,fences);

		if (!player.alive) {
			cout << "You lost!" << endl << endl;
			return false;
		}
		
		if (!player.NewPlayerPosition(fences)) return false;
		

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

void scoreboard(int num_maze, int time){
	
    vector <Player_info> score_info;
    Player_info p_info;
	string filename, line;

	// ler o ficheiro
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
	
	// trabalhar os dados
	bool valid;
	do {
		valid = true;
		cout << "Insert name(max 15 characters): ";
		getline(cin, line);
		if (line.size() > 15) {
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

	for (size_t i = 0; i < score_info.size();i++){
		//if (time == score_info[i].score) {
		//	if (p_info.name > )
		//}
		if (time <= score_info[i].score) {
			index = i;
			break;
		}
	}
	cout << "index: " << index << endl;
	score_info.insert(score_info.begin() + index, p_info);
	
	// voltar a escrever(mostrar ao utilizador tambem)
	
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
	cout << endl;
    while(getline(in_stream, line)) {
        cout << line << endl;
	}
	cout << endl;
	in_stream.close();
}

int main()
{
	Player player;
	vector <Robot> robots;
	vector <Fence> fences;
	int num_maze;
	bool win;

	cout << "Hello friends, welcome to the most amazing game you are ever going to play.Are u ready?" << endl;


	while (true) {
		string filename;
		
		if (!menu()) break;

		num_maze = chooseMaze();

		if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + ".txt";
		else filename = "MAZE_0" + to_string(num_maze) + ".txt";

		ReadMaze(filename,player,robots,fences);
		
		time_t start = time(NULL);
		win = play(20,10,player,robots,fences);
		time_t end = time(NULL);
		int time = difftime(end, start);

		cout << time <<endl;

		if(win) {
			scoreboard(num_maze, time);
		}
		
		player.alive = true;
		robots.clear();
		fences.clear();
		
	}	
	return 0;
}


