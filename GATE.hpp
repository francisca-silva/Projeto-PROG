#ifndef GATE_H
#define GATE_H

class Gate {
public:
 Gate(int row, int col);
 int getRow() const;
 int getCol() const;
private:
 int row, col;
};

#endif