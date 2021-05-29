#include "MAZE.hpp"
#include "POST.hpp"


Maze::Maze()
{
    numRows = 0;
    numCols = 0;
}

Maze::Maze(int r, int c)
{
    numRows = r;
    numCols = c;
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

Post Maze::getPost(int id)
{
    return posts[id];
}

int Maze::getnumPosts() const
{
    return posts.size();
}

