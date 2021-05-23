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


Maze::Maze()
{
    numCols = 0;
    numRows = 0;
}

void Maze::addPost(const Post& post)
{
    posts.push_back(post);
}

int Maze::getnumRows() const
{
    return numRows;
}

int Maze::getnumCols() const
{
    return numCols;
}

void Maze::setnumCols(int c)
{
    numCols = c;
} 

void Maze::setnumRows(int d)
{
    numRows = d;
}


Post Maze::getPost(int id)
{
    return posts[id];
}

int Maze::getnumPosts() const
{
    return posts.size();
}

