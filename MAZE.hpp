#include <vector>

#include "POST.hpp"

#ifndef MAZE_H
#define MAZE_H

using namespace std;


class Maze {
public:
 Maze();
 Maze(int r, int c);
 void addPost(const Post& post);
 int getnumRows() const;
 int getnumCols() const;
 int getnumPosts() const;
 Post getPost(int id);
 // other methods
private:
 int numRows, numCols;
 vector <vector <char>> maze;
 vector <Post> posts;
};

#endif
