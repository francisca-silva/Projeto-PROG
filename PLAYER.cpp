//T04_G12
#include "PLAYER.hpp"

Player::Player()
{
    alive = true;
    symbol = 'H';
    row = -1;   // this will be helpful to see if the player has already been initialized or not
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



