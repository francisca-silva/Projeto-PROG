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

/*
Player::Player(int r, int c, char s)
{
    row = r;
    col = c;
    symbol = s;
    alive = true;
}
*/

Player::Player()
{
    alive = true;
    symbol = 'H';
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
    symbol = 'h';
}

void Player::move(Movement delta)
{
    row += delta.dRow;
    col += delta.dCol;
}

void Player::setPosition(int r, int c)
{
    row = r;
    col = c;
}



void Player::setSymbol(char s)
{
    symbol = s;
}