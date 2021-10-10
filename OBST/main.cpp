#include <iostream>
#include "OBST.h"

int main()
{
    int da[]{0,10,20,30,40, 50};//,50,60,70,80};
    int pa[]{0,3,1,5,2,4};//,3,4,6,1};
    int qa[]{3,1,5,2,4,1};//,0,0,0,0};
    OBST a(da, pa, qa, 4);
    std::cout << "A: " << std::endl;
    a.PrintTree(a.GetRoot(), 5);

    int db[]{0,10,20,30,40};//,50,60,70,80};
    int pb[]{0,0,0,0,0};//,3,4,6,1};
    int qb[]{1,10,1,1,10};//,0,0,0,0};
    OBST b(db, pb, qb, 4);
    std::cout << "B: " << std::endl;
    b.PrintTree(b.GetRoot(), 5);

    OBST c(b);
    std::cout << "C: " << std::endl;
    c.PrintTree(c.GetRoot(), 5);

    OBST d = a;
    std::cout << "D: " << std::endl;
    d.PrintTree(d.GetRoot(), 5);
}