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

#include "PLAYER.hpp"

struct Movement
{
 int dRow, dCol; // displacement, taking into account the chosen movement
};


Player::Player(int r, int c, char s)
{
    row = r;
    col = c;
    symbol = s;
    alive = true;
}

inline int Player::getRow() const
{
    return row;
}

inline int Player::getCol() const
{
    return col;
}

inline char Player::getSymbol() const
{
    return symbol;
}

inline bool Player::isAlive() const
{
    return alive;
}

inline void Player::setAsDead()
{
    alive = false;
}

bool Player::move(Movement delta)
{
    row += delta.dRow;
    col += delta.dCol;

    validpos = true; //FALTA VER SE A POS É VALIDA

    return validpos;
}