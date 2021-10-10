#pragma once
#include "BST.h"

class OBST : public BST
{
public:
    OBST(): BST(){};
    OBST(int *d, int *p, int *q, int n);
    OBST(const OBST&);
    OBST& operator= (const OBST&);
    virtual ~OBST(){};

private:
    void CreateMatrix(int *p, int *q, int n, int **W, int **C, int **R);
    Node *OTree (int *d, int i, int j, int **R, Node* q);
};