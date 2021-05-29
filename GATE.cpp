#include "GATE.hpp"

Gate::Gate(int r, int c)
{
    row = r;
    col = c;
}

int Gate::getRow() const
{
    return row;
}

int Gate::getCol() const
{
    return col;
}
