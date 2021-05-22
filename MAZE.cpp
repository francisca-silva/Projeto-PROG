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
    posts.pushback(post);
}

inline int Maze::getnumRows() const
{
    return numRows;
}

inline int Maze::getnumCols() const
{
    return numCols;
}

inline void Maze::setnumCols(int c)
{
    numCols = c;
} 

inline void Maze::setnumRows(int d)
{
    numRows = d;
}


inline Post Maze::getPost(int id)
{
    return posts[id];
}

inline int Maze::getnumPosts() const
{
    return posts.size();
}

