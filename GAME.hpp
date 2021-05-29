#ifndef GAME_H
#define GAME_H

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

#include "PLAYER.hpp"
#include "ROBOTS.hpp"
#include "POST.hpp"
#include "MAZE.hpp"
#include "GATE.hpp"

class Game {
public:
 Game(const string &filename);
 ~Game();
 // This constructor should initialize the Maze, the vector of Robots, and the Player,
 // using the chars read from the file
 bool play(); // implements the game loop; returns true if player wins, false otherwise
 bool isValid();
 bool scoreboard(const int num_maze,const int time);
private:
 void NewRobotPosition(Robot& robot);
 int NewPlayerPosition();
 void showGameDisplay();
 //bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
 //bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
 // other methods, for example:
 // to check if player is trying to move to a valid place
 // to apply a valid play and check collisions
 // to check if two robots collide (and possibly set them as dead)
 // etc.
private:
 bool valid;
 Maze maze;
 Player player;
 vector<Robot> robots;
 vector<Gate> gates;
 //other attributes
};

#endif