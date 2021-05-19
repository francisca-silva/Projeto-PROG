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

struct Movement
{
 int dRow, dCol; // displacement, taking into account the chosen movement
};


class Maze {
public:
 Maze();
 void addPost(const Post& post);
 int getnumRows() const;
 int getnumCols() const;
 int getnumPosts() const;
 void setnumCols(int c);
 void setnumRows(int c);
 Post getPost(int id);
 // other methods
private:
 int numRows, numCols;
 vector <vector <char>> maze; //(numRows,vector<char>(numCols))
 vector <Post>& posts;
 // data structure that represents the posts
};

#endif
