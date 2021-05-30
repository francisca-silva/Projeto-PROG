#ifndef PLAYER_H
#define PLAYER_H

struct Movement
{
 int dRow, dCol; // displacement, taking into account the chosen movement
};

class Player {
public:
 Player();
 int getRow() const;
 int getCol() const;
 char getSymbol() const;
 bool isAlive() const;
 void setAsDead();
 void move(Movement delta);
 void setPosition(int row, int col);
private:
 int row, col;
 bool alive;
 char symbol;
};

#endif