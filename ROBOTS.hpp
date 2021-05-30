#ifndef ROBOTS_H
#define ROBOTS_H

using namespace std;

struct Position
{
 int row, col;
};

class Robot {
public:
 Robot(int row, int col);
 int getID() const;
 char getSymbol() const; // get char representation of robot (R if alive, r if dead)
 int getRow() const;
 int getCol() const;
 Position getPosition() const;
 bool isAlive() const;
 void setRow(int x);
 void setCol(int y);
 void setPosition(const Position &pos);
 void setAsDead();
private:
 static int robotCounter; //used to attribute automatically the id to the robots
 int id;
 int row, col;
 bool alive;
};


#endif