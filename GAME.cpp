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

#include "GAME.hpp"
#include "PLAYER_H.hpp"
#include "ROBOTS.hpp"
#include "POST.hpp"
#include "MAZE.hpp"

struct Movement
{
 int dRow, dCol; // displacement, taking into account the chosen movement
};

class Game {
public:
 Game(const string &filename);
 // This constructor should initialize the Maze, the vector of Robots, and the Player,
 // using the chars read from the file
 bool play(); // implements the game loop; returns true if player wins, false otherwise
 bool isValid();
private:
 void showGameDisplay() const;
 bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
 bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
 void NewRobotPosition(Robot& robot);
 // other methods, for example:

 // to check if player is trying to move to a valid place
 // to apply a valid play and check collisions
 // to check if two robots collide (and possibly set them as dead)
 // etc.
private:
 Maze maze;
 Player player;
 vector<Robot> robots;
 //other attributes
};


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
				player = Player(maze.getnumRows(), maze.getnumCols(), 'H');
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
    
}

void Game::showGameDisplay() const
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

bool Game::collide(Robot& robot, Post& post)
{
    return true;
} // check if robot collided with post (and possibly set it as dead)

bool Game::collide(Robot& robot, Player& player)
{
    return true;
}


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
    
    for (size_t i = 0; i < maze.getnumPosts(); i++) {      // checks if the robot collides with the fence
        if (maze.getPost(i).getRow() == robot.getRow() && maze.getPost(i).getCol() == robot.getCol()){  
            robot.setAsDead();  // in case of collision, the robot dies
            break;
        }
    }

    for (size_t i = 0; i < robots.size(); i++) {  // check if collides with another robot
        if (robots[i].getID() && robots[i].getRow() == robot.getRow() && robots[i].getCol() == robot.getCol()) {
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
    int last_pos_i, last_pos_j;
    
    while (!valid){    //this cycle only ends when the player chooses a valid position

        last_pos_i = player.getRow();
        last_pos_j = player.getCol();

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
                Movement m = {-1,-1};
                valid = player.move(m);
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
