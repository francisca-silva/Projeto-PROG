using namespace std;

#include "GAME.hpp"


/*
Initializer that reads the maze and creates all other objects
@param filename - name of the file containing the maze
*/
Game::Game(const string &filename)
{
    ifstream in_stream;	// stream that reads the contents of the chosen file 
	string row;			// to store the value of each row at a time
	int NumRow, NumCol; // to store the number of the row and the number of the column
	char object;		// used to store the value of each space in the maze

	valid = true;		//to check if the maze is valid or not

	in_stream.open(filename); 

	in_stream >> NumRow >> object >> NumCol;
	getline(in_stream, row);	//to remove the first '\n'

	maze = Maze(NumRow,NumCol);	//initializes the maze with the correct size

	NumRow = 0;	//initializes the number of the row
	
	while (getline(in_stream, row)) { // cycle that analyses the maze, collecting its different elements from line to line

		NumCol = 0;	//initializes the number of the column
		object = row[NumCol];  

		do {  // until the last element of each line
			switch (object)
			{
			case 'H': 
				if(player.getRow() != -1) valid = false;	// if there is more than one player in the maze it sets it to invalid
                player.setPosition(NumRow, NumCol);			// sets the player's position
				break;
			case 'R': 
				robots.push_back(Robot(NumRow,NumCol));		// adds the robot to the vector
				break;
			case '*': case '+':
                maze.addPost(Post(NumRow,NumCol,object));	// adds the post to the maze
				break;
			case 'O':
				gates.push_back(Gate(NumRow,NumCol));		// adds the gate to the vector
				break;
			case 'h': case 'r':
				valid = false;								//if the player or any robot is dead it sets the maze invalid
				break;
			default:	// if it is ' ' it is ignored
				break;
			}
			NumCol++;	//increments the number of columns
			object = row[NumCol];	// reads the next element

		} while (object != '\0');	// repeats until the end of the string

		NumRow++;	//increments the number of rows
	} 	
	in_stream.close();
}

/*
Plays one game using the choosen maze.
@return true - if the player wins
@return false - if the player leaves the game or loses it   
*/
bool Game::play()
{
	int cont;	//will be used to se if the player has/hasn't won, or if it wants to leave the game

	while (true){	// plays until the function(play) returns true or false depending on the output

		showGameDisplay();	// call to function in order to draw the chosen maze

		if (!player.isAlive()) {
			cout << "You lost!" << endl << endl;
			return false;  
		}
		
		cont = NewPlayerPosition();	//stores the result of the function that can be 0(hasn't won yet), 1 or -1

		if (cont == -1) return false;
		
		if (cont == 1) { 
			showGameDisplay();	// shows the final maze before leaving the function
			cout << "You won!!" << endl <<endl;
			return true;	// this true will call the scoreboad() function to add the player's name and score
		}

		for (size_t i = 0; i < robots.size(); i++){	// moves each robot to its new position
			
			if (robots[i].isAlive()) NewRobotPosition(robots[i]);
				
		}  
	}
}	// implements the game loop; returns true if player wins, false otherwise

/*
@return true - if the maze meets allqualifications
@return false - otherwise
*/
bool Game::isValid()
{
	if (gates.size() == 0) valid = false;	// if there isn´t any gate the game is invalid
	else if (player.getRow() == -1) valid = false;	//if there isn´t any player the game is also invalid

	return valid;
}

/** 
Fills a bidimentional vector(same size as the maze) with spaces, and then with all the posts, robots, gates and the player.
Then it shows the vector on the screen
@return void
*/
void Game::showGameDisplay()
{
    vector <vector <char>> maze_(maze.getnumRows(),vector<char>(maze.getnumCols()));	// this vector will be written in each function call

	for (int i = 0; i < maze.getnumRows(); i++){	// fills with blank spaces the number of columns and rows
		for (int j = 0; j < maze.getnumCols(); j++) maze_[i][j] = ' ';		
	}
	 
	for (int i = 0; i < maze.getnumPosts(); i++) {	// then it writes on top of the ' ' all of the fences
		maze_[maze.getPost(i).getRow()][maze.getPost(i).getCol()] = maze.getPost(i).getSymbol();
	}

	for (size_t i = 0; i < robots.size(); i++) {	// if any robot dies because of a fence, it is written on top of it(and the fence disappears)
		maze_[robots[i].getRow()][robots[i].getCol()] = robots[i].getSymbol();
	}

	for (size_t i = 0; i < gates.size(); i++) {	// writes the gates 
		maze_[gates[i].getRow()][gates[i].getCol()] = 'O';
	}
	
	maze_[player.getRow()][player.getCol()] = player.getSymbol();	// lastly if the player is dead because of a robot(in the same position) it is written on top of it

	cout << endl;
	for (int i = 0; i < maze.getnumRows(); i++){	// prints the maze
		for (int j = 0; j < maze.getnumCols(); j++){
			cout << maze_[i][j];	
		} 	
		cout << endl;
	}
}

/** 
Updates the robots' position afteer each movement
@param robot - robot to be moved
@return void
*/
void Game::NewRobotPosition(Robot& robot)
{
	Position last_pos = {robot.getRow(),robot.getCol()};	// stores the robot's previous position

    int newPos[9][2] = {{robot.getRow()-1,robot.getCol()-1},{robot.getRow()-1,robot.getCol()},{robot.getRow()-1,robot.getCol()+1},{robot.getRow(),robot.getCol()-1}, {robot.getRow(),robot.getCol()}, 
                        {robot.getRow(),robot.getCol()+1},{robot.getRow()+1,robot.getCol()-1},{robot.getRow()+1,robot.getCol()},{robot.getRow()+1,robot.getCol()+1}};	// this is an easy way to calculate the possible positions for each robot

    int min_index; 	// index of the position with the shorter distance
    double dist,min_dist = __DBL_MAX__;	// distance between a position and the player

    for (int i = 0; i < 9; i++){	// for each possible position
        dist = sqrt(pow(newPos[i][0]-player.getRow(),2) + pow(newPos[i][1]-player.getCol(),2));	//this calculates the distance to the player
        if (dist < min_dist) {	// checks if this position is the shortest at the moment
            min_dist = dist;	// stores this distance as the shortest
            min_index = i;		// and i as it's index
        }
    }
    robot.setRow(newPos[min_index][0]);	// stores the new position of the robot
    robot.setCol(newPos[min_index][1]);
    
    for (int i = 0; i < maze.getnumPosts(); i++) {	// checks if the robot collides with the fence
        if (maze.getPost(i).getRow() == robot.getRow() && maze.getPost(i).getCol() == robot.getCol()){  
			if(maze.getPost(i).isElectrified()) {
				robot.setRow(last_pos.row);	// if the fence is electrified the robot stays in it's previous position
				robot.setCol(last_pos.col);
			}
			robot.setAsDead();	// in case of collision, the robot dies
			break;	
        }
    }

	for (int i = 0; i < gates.size(); i++) {	// checks if the robot collides with the gates
        if (gates[i].getRow() == robot.getRow() && gates[i].getCol() == robot.getCol()){ 
			robot.setRow(last_pos.row);
			robot.setCol(last_pos.col);
			robot.setAsDead();
            break;
        }
    }

    for (size_t i = 0; i < robots.size(); i++) {	// check if collides with another robot
        if (robots[i].getID() != robot.getID() && robots[i].getRow() == robot.getRow() && robots[i].getCol() == robot.getCol()) {
            robot.setAsDead();  
            robots[i].setAsDead();	// if it collides, both die
            break;
        }
    }

    if (player.getRow() == robot.getRow() && player.getCol() == robot.getCol()){	// checks for collision with the player
        player.setAsDead();
    }
	
}

/** 
Updates the players' position for each move
@return 1 - if the player reached a gate
@return 0 - if the player hasn't yet reached a gate
@return -1 - if the user typed CTRL-Z in any of the moments that asked for input
*/
int Game::NewPlayerPosition()
{
    char input;		// this will store the key pressed by the player(to determine the next position)
    bool valid = false;	// used to check if the input is valid depending on the possible positions
    Movement mov;
	map<char, Movement> moves = {{'Q',{-1,-1}},{'W',{-1,0}},{'E',{-1,1}},{'A',{0,-1}},	//dictionary that stores the keys
								{'S',{0,0}},{'D',{0,1}},{'Z',{1,-1}},{'X',{1,0}},{'C',{1,1}}};
    
    while (!valid){		//this cycle only ends when the player chooses a valid position

        cout << "Please choose one of the following positions:\n Q W E \n A S D \n Z X C" << endl;
        cin >> input;
        valid = true;	// at each cycle repetition it's assumed it will be valid

        cin.ignore(numeric_limits<streamsize>::max(),'\n');	//only the first character

        if (cin.eof()) {	//checks if the player wants to exit this game
            cin.clear();
            return -1;		// means the user wants to leave the game
        }

		if (moves.find(toupper(input)) == moves.end()) {
			cout << "Invalid input" << endl << endl;
    		valid = false;	// if the player doesn't choose one of the valid positions the input is not valid
			continue;
		}

		mov = moves[toupper(input)];	// calculates the new player position

    	player.move(mov);				//moves the player to the new position			

        for (int i = 0; i < maze.getnumPosts(); i++) {  // checks if the player goes against any fence
            if (maze.getPost(i).getRow() == player.getRow() && maze.getPost(i).getCol() == player.getCol()){
				player.move({-mov.dRow, -mov.dCol});	// resets the position for the next cycle iteration
				if(maze.getPost(i).isElectrified()) {	// if the player goes against an eletrified fence dies
					player.setAsDead();
				}
				else {
					cout << "Invalid input(can't go to post)" << endl << endl;
					valid = false;
					break;
				}
            }
        }

		for (size_t i = 0; i < robots.size(); i++) {	//checks if the player goes against a dead robot(not a valid move) or a living robot and dies
			if (robots[i].getRow() == player.getRow() && robots[i].getCol() == player.getCol()) {
				if(robots[i].isAlive()){
					player.setAsDead();
					break;
				}
				else {
					player.move({-mov.dRow, -mov.dCol});
					cout << "Invalid input(can't go to dead/stuck robot)" << endl << endl;
					valid = false;
					break;
				}
			}
		}

		for (size_t i = 0; i < gates.size(); i++){		//see if the player arrives to the gate successfully
			if (gates[i].getRow() == player.getRow() && gates[i].getCol() == player.getCol()) return 1;
		}

    }
    return 0;	// means the player didn't win
}

/*
Updates and presents the scoreboard of the winners of the game and the time they took to do so.
@param num_maze - used to create the filename of the scoreboard file to be accessed
@param time - number of seconds the player took to finish the game 
@return true - if it was able to finish the function correctly
@return false - if the user typed CTRL-Z in any of the moments that asked for input, this function exits with false before updating the scoreboard
*/
bool Game::scoreboard(const int num_maze,const int time)
{
	struct Player_Info{
		string name;  //players' name and the time it took to complete the maze
		int score;
	};

    vector <Player_Info> score_info;	// this vector will hold all previous player information
    Player_Info p_info;		// generic Player_Info to help fill the vector and eventually the current user's information
	string filename, line;	// name of the file to be accessed and each line of it

	////// code to read the scoreboard file
	ifstream in_stream;

	if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + "_WINNERS.txt"; //composing the name of the file according to the number of the chosen maze
	else filename = "MAZE_0" + to_string(num_maze) + "_WINNERS.txt";

	in_stream.open(filename);

    if (!in_stream) {	// if the file doesn't exist
		ofstream newfile;
		newfile.open(filename);	// this will create it
		newfile.close();
	}
	in_stream.close();

	in_stream.open(filename);	// now that the file exists, it can be read

    while(getline(in_stream, line)) {
        if (line[21] == 'e' || line[21] == '-') continue;	// this will ignore the first 2 lines
        p_info.name = line.substr(0,15);	// this slices the first 15 characters, starting at index 0
		p_info.score = stoi(line.substr(18,4), nullptr);	// extracts the score
		score_info.push_back(p_info);		// adds this information to the vector
	}
	
	in_stream.close(); 
	
	////// code to add the player's info to the rest
	
	bool valid; // to be used in the do while cycle until the name input is valid  
	int index = score_info.size(); // inicialization of the index
	
	do {	// cycle that assures the input is valid
		valid = true;

		cout << "Insert name(max 15 characters): ";
		getline(cin,line);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (cin.eof()) {  // if the user types CTRL-Z the function will not add this game to the scoreboard
			cin.clear();
			return false;
		}

		else if (line.size() > 15) {  // if the user types more than 15 characters
			cout << "Invalid input(too many characters)" << endl <<endl;
			valid = false;
		}

		line.resize(15,' '); // aligns the user input with the other players' names

		for (size_t i = 0; i < score_info.size();i++){  // this cycle prevents the user to put a name equal to an already existing name
			if (score_info[i].name == line) {
				cout << "Invalid input(already existing name)" << endl << endl;
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
	
	////// rewriting the scoreboard (also showing it to the user)
	
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

