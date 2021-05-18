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

#include "MAZE.hpp"
#include "POST.hpp"


Maze::Maze(int numRows, int numCols)
{
    this->numRows = numRows;
    this->numRows = numRows;
}

bool Maze::addPost(const Post& post, const Position& position)
{
    return true; // FALTA FAZER TUDOOO
}

inline int Maze::getnumRows() const
{
    return numRows;
}

inline int Maze::getnumCols() const
{
    return numCols;
}