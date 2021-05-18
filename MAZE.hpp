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

#include "POST.hpp"

#ifndef MAZE_H
#define MAZE_H

struct Position
{
 int row, col;
};


class Maze {
public:
 Maze(int numRows, int numCols);
 bool addPost(const Post& post, const Position& position);
 int getnumRows() const;
 int getnumCols() const;
 // other methods
private:
 int numRows, numCols;
 vector <vector <char>> maze; //(numRows,vector<char>(numCols))
 // data structure that represents the posts
};

#endif
