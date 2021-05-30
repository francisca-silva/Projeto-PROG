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
#include <map>

using namespace std;

#include "PLAYER.hpp"
#include "ROBOTS.hpp"
#include "POST.hpp"
#include "MAZE.hpp"
#include "GATE.hpp"

class Game {
public:
 Game(const string &filename);
 bool play();
 bool isValid();
 bool scoreboard(const int num_maze,const int time);
private:
 void NewRobotPosition(Robot& robot);
 int NewPlayerPosition(); 
 void showGameDisplay();
private:
 bool valid;
 Maze maze;
 Player player;
 vector<Robot> robots;
 vector<Gate> gates;
};

#endif