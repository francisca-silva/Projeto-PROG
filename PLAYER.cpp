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


int Player::getRow() const
{
    return row;
}

int Player::getCol() const
{
    return col;
}

char Player::getSymbol() const
{
    return symbol;
}

bool Player::isAlive() const
{
    return alive;
}

void Player::setAsDead()
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