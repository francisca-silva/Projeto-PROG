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

#ifndef POST_H
#define POST_H

class Post {
public:
 Post(int row, int col, char type);
 int getRow() const;
 int getCol() const;
 char getSymbol() const; // get char representation of Post
 bool isElectrified() const;
 //other methods
private:
 int row, col;
 char type; // '*' - electrified; '+'- non-electrified
 // other attributes (?)
 // could also have a state, like the robot(?)
};


#endif