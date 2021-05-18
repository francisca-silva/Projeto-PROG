#include "POST.hpp"


Post::Post(int r, int c, char t)
{
    row = r;
    col = c;
    type = t;
}

inline int Post::getRow() const
{
    return row;
}

inline int Post::getCol() const
{
    return col;
}

inline char Post::getSymbol() const
{
    return type;
}

inline bool Post::isElectrified() const
{
    return (type == '*');
}