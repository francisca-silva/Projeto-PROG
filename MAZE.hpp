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
private:
 int numRows, numCols;
 vector <Post> posts;
};

#endif
