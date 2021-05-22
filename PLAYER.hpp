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
 //Player(int row, int col, char symbol);
 Player();
 int getRow() const;
 int getCol() const;
 char getSymbol() const;
 bool isAlive() const;
 void setAsDead();
 void move(Movement delta);
 void setPosition(int row, int col);
 void setSymbol(char symbol);
private:
 int row, col;
 bool alive;
 char symbol;
};

#endif