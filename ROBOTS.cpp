#include "ROBOTS.hpp"

int Robot::robotCounter = 1;

Robot::Robot(int row, int col)
{
    this -> row = row;
    this -> col = col;
    alive = true;
    //State = ALIVE;
    id = ++robotCounter;
}

int Robot::getID() const
{
    return id;
}

char Robot::getSymbol() const
{
    if (alive) return 'R';
    return 'r';
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
    return {row, col};
}

bool Robot::isAlive() const
{
    return alive;
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