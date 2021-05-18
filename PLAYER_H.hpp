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

#ifndef PLAYER_H
#define PLAYER_H

struct Movement
{
 int dRow, dCol; // displacement, taking into account the chosen movement
};

class Player {
public:
 Player(int row, int col, char symbol);
 int getRow() const;
 int getCol() const;
 char getSymbol() const;
 bool isAlive() const;
 void setAsDead();
 bool move(Movement delta);
private:
 int row, col;
 bool alive;
 char symbol;
};

#endif