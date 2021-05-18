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

#include "ROBOTS.hpp"

class Robot {
public:
 enum State { ALIVE, STUCK, DEAD };
 Robot(int row, int col);
 int getID() const;
 char getSymbol() const; // get char representation of robot (R if alive, r if dead)
 int getRow() const;
 int getCol() const;
 Position getPosition() const;
 bool isAlive() const;
 void setRow(int x);
 void setCol(int y);
 void setPosition(const Position &pos);
 void setAsDead();
 //other methods 
private:
 State s;
 static int robotCounter; //used to attribute automatically the id to the robots
 int id;
 int row, col;
 bool alive;
 char R, r;
 // other attributes (?)
};

struct Position
{
 int row, col;
};

Robot::Robot(int row, int col)
{
    this -> row = row;
    this -> col = col;
    robotCounter = 0;
    id = ++robotCounter;
}

int Robot::getID() const
{
    return id;
}

char Robot::getSymbol() const
{
    if(STUCK) return R ;
    if (alive) return R;
    else return r;
} // get char representation of robot (R if alive, r if dead)

int Robot::getRow() const
{
    return row;
}

int Robot::getCol() const
{
    return col;
}

inline Position Robot::getPosition() const
{
    //Position p = {row, col};
    return {row, col};
}

bool Robot::isAlive() const
{
    if(alive) return true;
    else return false;
}

void Robot::setRow(int x)
{
    row = x;
}

void Robot::setCol(int y)
{
    col = y;
}

void Robot::setPosition(const Position &pos)
{
    row = pos.row;
    col = pos.col;
}

void Robot::setAsDead()
{
    alive = false;
}