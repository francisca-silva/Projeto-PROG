#include "ROBOTS.hpp"

int Robot::robotCounter = 0;

Robot::Robot(int row, int col)
{
    this -> row = row;
    this -> col = col;
    alive = true;
    //0State = ALIVE;
    id = ++robotCounter;
}

int Robot::getID() const
{
    return id;
}

char Robot::getSymbol() const
{
    if(STUCK) return 'R' ;
    if (alive) return 'R';
    else return 'r';
} // get char representation of robot (R if alive, r if dead)

int Robot::getRow() const
{
    return row;
}

int Robot::getCol() const
{
    return col;
}

Position Robot::getPosition() const
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