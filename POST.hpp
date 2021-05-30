//T04_G12
#ifndef POST_H
#define POST_H

class Post {
public:
 Post(int row, int col, char type);
 int getRow() const;
 int getCol() const;
 char getSymbol() const;
 bool isElectrified() const;
 int getID() const;
private:
 static int postCounter; //used to attribute automatically the id to the posts
 int id;
 int row, col;
 char type; // '*' - electrified; '+'- non-electrified
};


#endif