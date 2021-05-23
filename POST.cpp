#include "POST.hpp"

int Post::postCounter = 0;

Post::Post(int r, int c, char t)
{
    row = r;
    col = c;
    type = t;
    id = ++postCounter;
}

int Post::getRow() const
{
    return row;
}

int Post::getCol() const
{
    return col;
}

char Post::getSymbol() const
{
    return type;
}

int Post::getID() const
{
    return id;
}

bool Post::isElectrified() const
{
    return (type == '*');
}