//T04_G12
#include "functions.hpp"

using namespace std;


int main()
{
	int num_maze;	// number id to be chosen by the player
	bool win;		//whether the player wins the game or not

	cout << "Hello friends, welcome to the most amazing game you are ever going to play. Are u ready?" << endl; //super oustanding introduction

	while (true) {	// this cycle allows the user to play various games even with different mazes
		string filename; 
		
		if (!menu()) break; // if menu returns false it means the player wants to exit the game

		num_maze = chooseMaze();
		if (num_maze == -1) continue; // if the user types 'CTRL-Z'/'0' this function will return -1, meaning it exits this game and shows the menu

		if (num_maze > 9) filename = "MAZE_" + to_string(num_maze) + ".txt";
		else filename = "MAZE_0" + to_string(num_maze) + ".txt";

		Game game(filename);	// initializes the object game for the choosen maze

		time_t start = time(NULL); 
		win = game.play();
		time_t end = time(NULL); 
		int time = difftime(end, start); //calculates the game duration

		if(win) { // in case the player doesn't win the cycle continues to the next iteration and shows the menu
			if(!game.scoreboard(num_maze, time)) continue; // if the user types CTRL-Z this function will return false, meaning it exits this game and shows the menu
		}
	}	
	return 0;
}