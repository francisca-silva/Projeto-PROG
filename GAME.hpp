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

#include "PLAYER_H.hpp"
#include "ROBOTS.hpp"
#include "POST.hpp"
#include "MAZE.hpp"

#ifndef GAME_H
#define GAME_H



class Game {
public:
 Game(const string &filename);
 // This constructor should initialize the Maze, the vector of Robots, and the Player,
 // using the chars read from the file
 bool play(); // implements the game loop; returns true if player wins, false otherwise
 bool isValid();
private:
 void NewRobotPosition(Robot& robot);
 bool NewPlayerPosition();
 void showGameDisplay() const;
 bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
 bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
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

#endif