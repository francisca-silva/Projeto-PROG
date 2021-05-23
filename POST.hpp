#ifndef POST_H
#define POST_H

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

class Post {
public:
 Post(int row, int col, char type);
 int getRow() const;
 int getCol() const;
 char getSymbol() const; // get char representation of Post
 bool isElectrified() const;
 int getID() const;
 //other methods
private:
 static int postCounter; //used to attribute automatically the id to the posts
 int id;
 int row, col;
 char type; // '*' - electrified; '+'- non-electrified
 // other attributes (?)
 // could also have a state, like the robot(?)
};


#endif