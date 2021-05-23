using namespace std;

#include "GAME.hpp"


Game::Game(const string &filename)
{

    ifstream in_stream; // stream that reads the contents of the chosen file 
	string row;  // to store the value of each row at a time
	//Maze_Size size_info;  // used at the end to return the proportions of the maze

	cout << endl << filename << endl; //prints the name of the maze

	in_stream.open(filename);

	while (getline(in_stream, row)) { // cycle that analyses the maze, collecting its different elements from line to line
		
		maze.setnumCols(0); // starts as 0 in every iteration of the while cycle
		char object = row[maze.getnumCols()];  // used to store the value of each space in the maze

		do {  // until the last element of each line
			switch (object)
			{
			case 'H': 
                player.setPosition(maze.getnumRows(), maze.getnumCols());
                //player.setSymbol('H');
				//this->player = Player(maze.getnumRows(), maze.getnumCols(), 'H');
				break;

			case 'R': 
				robots.push_back(Robot(maze.getnumRows(),maze.getnumCols()));  // adds the robot to the vector
				break;
				
			case '*': case '+':
                maze.addPost(Post(maze.getnumRows(),maze.getnumCols(),object)); // and adds it to the vector of Fences
				break;
			default: // if it is ' ' it is ignored
				break;
			}
			maze.setnumCols(maze.getnumCols()+1);  //increments the number of columns
			object = row[maze.getnumCols()];  // reads the next element

		} while (object != '\0'); // repeats until the end of the string

		maze.setnumRows(maze.getnumRows()+1); //increments the number of rows
	} 
	
	in_stream.close(); 

	cout << maze.getnumCols() << " x " << maze.getnumRows() << endl << endl; //prints the number of columns and rows

}


Game::~Game() 
{
    
}


bool Game::play()
{
    bool alldead; // to check if all of the robots are dead

	while (true){  // plays until the function returns true or false depending on the output

		alldead = true; //assuming all robots are dead
	
		showGameDisplay(); // call to function in order to draw the chosen maze

		if (!player.isAlive()) {
			cout << "You lost!" << endl << endl;
			return false;  
		}
		
		if (!NewPlayerPosition()) return false; // this function's purpose is to move the player but if the user typed CTRL-Z it immediately ends the play() function and returns false
		

		for (size_t i = 0; i < robots.size(); i++){  // moves each robot 
			
			if (robots[i].isAlive()) NewRobotPosition(robots[i]);
				
		}  
		
		for (size_t i = 0; i < robots.size(); i++) if (robots[i].isAlive()) alldead = false;  // if any robot is still alive then they're not all dead

		if (alldead) {
			showGameDisplay(); // shows the final maze before leaving the function
			cout << "You won!!" << endl <<endl;
			return true;  // this true will call the scoreboad() function to add the player's name and score
		}
	}
} // implements the game loop; returns true if player wins, false otherwise

bool Game::isValid()
{
    return true;
}

void Game::showGameDisplay() // TIRAMOS O CONST ISSO TEM PROBLEMA?
{
    vector <vector <char>> maze_(maze.getnumRows(),vector<char>(maze.getnumCols())); // this vector will be written in each function call

	for (int i = 0; i < maze.getnumRows(); i++){    // fills with blank spaces the number of columns and rows
		for (int j = 0; j < maze.getnumCols(); j++) maze_[i][j] = ' ';		
	}
	 
	for (int i = 0; i < maze.getnumPosts(); i++) {  // then it writes on top of the ' ' all of the fences
		if (maze.getPost(i).isElectrified()) maze_[maze.getPost(i).getRow()][maze.getPost(i).getCol()] = '*';
        else maze_[maze.getPost(i).getRow()][maze.getPost(i).getCol()] = '+';
	}

	for (size_t i = 0; i < robots.size(); i++) {  // if any robot dies because of a fence, it is written on top of it(and the fence disappears)
		if (robots[i].isAlive()) maze_[robots[i].getRow()][robots[i].getCol()] = 'R';
		else maze_[robots[i].getRow()][robots[i].getCol()] = 'r';
	}
	
	if (player.isAlive()) maze_[player.getRow()][player.getCol()] = 'H'; // lastly if the player is dead because of a robot(in the same position) it is written on top of it
	else maze_[player.getRow()][player.getCol()] = 'h';

	cout << endl;
	for (int i = 0; i < maze.getnumRows(); i++){       // prints the maze
		for (int j = 0; j < maze.getnumCols(); j++){
			cout << maze_[i][j];	
		} 	
		cout << endl;
	}
}

/*
bool Game::collide(Robot& robot, Post& post)
{
    return true;
} // check if robot collided with post (and possibly set it as dead)

bool Game::collide(Robot& robot, Player& player)
{
    return true;
}
*/

void Game::NewRobotPosition(Robot& robot)
{
    int newPos[9][2] = {{robot.getRow()-1,robot.getCol()-1},{robot.getRow()-1,robot.getCol()},{robot.getRow()-1,robot.getCol()+1},{robot.getRow(),robot.getCol()-1}, {robot.getRow(),robot.getCol()}, 
                        {robot.getRow(),robot.getCol()+1},{robot.getRow()+1,robot.getCol()-1},{robot.getRow()+1,robot.getCol()},{robot.getRow()+1,robot.getCol()+1}};   // this is an easy way to calculate the possible positions for each robot

    int min_index;  // index of the position with the shorter distance
    double dist,min_dist = __DBL_MAX__; // distance between a position and the player

    for (int i = 0; i < 9; i++){           // for each possible position
        dist = sqrt(pow(newPos[i][0]-player.getRow(),2) + pow(newPos[i][1]-player.getCol(),2)); //this calculates the distance to the player
        if (dist < min_dist) {  // checks if this position is the shortest to the moment
            min_dist = dist;  // stores this distance as the shortest
            min_index = i;    // and i as it's index
        }
    }
    robot.setRow(newPos[min_index][0]);  // stores the new position of the robot
    robot.setCol(newPos[min_index][1]);
    
    for (int i = 0; i < maze.getnumPosts(); i++) {      // checks if the robot collides with the fence
        if (maze.getPost(i).getRow() == robot.getRow() && maze.getPost(i).getCol() == robot.getCol()){  
            robot.setAsDead();  // in case of collision, the robot dies
            break;
        }
    }

    for (size_t i = 0; i < robots.size(); i++) {  // check if collides with another robot
        if (robots[i].getID() != robot.getID() && robots[i].getRow() == robot.getRow() && robots[i].getCol() == robot.getCol()) {
            robot.setAsDead();  
            robots[i].setAsDead();  // if it collides, both die
            break;
        }
    }

    if (player.getRow() == robot.getRow() && player.getCol() == robot.getCol()){  // checks for collision with the player
        player.setAsDead();
    }
	
}

bool Game::NewPlayerPosition()
{
    char input;   // this will store the key pressed by the player(to determine the next position)
    bool valid = false;  // used to check if the input is valid depending on the possible positions
    Movement mov;
    
    
    while (!valid){    //this cycle only ends when the player chooses a valid position

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
                mov = {-1,-1};
                break;
            case 'W': 
                mov = {-1,0};
                break;
            case 'E':
                mov = {-1,1};
                break;
            case 'A':
                mov = {0,-1};
                break;
            case 'S': break;
            case 'D': 
                mov = {0,1};
                break;
            case 'Z': 
                mov = {1,-1};
                break;
            case 'X': 
                mov = {1,0};
                break;
            case 'C': 
                mov = {1,1};
                break;
            default:
                cout << "Invalid input" << endl << endl;
                valid = false;  // if the player doesn't choose one of the valid positions the input is not valid
                break;
        }

        player.move(mov);

        cin.ignore(numeric_limits<streamsize>::max(),'\n');  // ignores any other input besides the first character(if the first is valid the rest is just ignored)

        for (int i = 0; i < maze.getnumPosts(); i++) {  // warns the player if he goes against any fence
            if (maze.getPost(i).getRow() == player.getRow() && maze.getPost(i).getCol() == player.getCol()){
                cout << "Invalid input(can't go to post)" << endl << endl;
                valid = false;
                player.move({-mov.dRow, -mov.dCol});   // resets the position for the next cycle iteration
                break;
            }
        }
    }
    return true; // means the function was successful
}

bool Game::scoreboard(const int num_maze,const int time)
{
	struct Player_Info{
	string name;  //players' name and the time it took to complete the maze
	int score;
};

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

