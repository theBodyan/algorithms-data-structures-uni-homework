#include <iostream>
#include <time.h>
#include "BST.h"

int main()
{
    srand(time(0));
    BST a();
    BST b(6);
    int c[]{1,2,3,4,5,6,7,8,9,10};
    BST d(c, 10);
    std::cout << "C: " << std::endl;
    b.PrintTree(b.GetRoot(), 5);
    std::cout << "D: " << std::endl;
    d.PrintTree(d.GetRoot(), 5);
    d.Clear();
    std::cout << "D: " << std::endl;
    d.PrintTree(d.GetRoot(), 5);
    d.Add(1, d.GetRoot());
    d.Add(2, d.GetRoot());
    d.Add(3, d.GetRoot());
    d.Add(21, d.GetRoot());
    d.Add(22, d.GetRoot());
    d.Add(23, d.GetRoot());
    d.Add(24, d.GetRoot());
    d.Add(25, d.GetRoot());
    d.Add(26, d.GetRoot());
    std::cout << "D: " << std::endl;
    d.PrintTree(d.GetRoot(), 5);

    std::cout << "D LCR: ";
    d.TreeTraversal_LCR(d.GetRoot());
    std::cout << std::endl;

    std::cout << "D LRC: ";
    d.TreeTraversal_LRC(d.GetRoot());
    std::cout << std::endl;

    std::cout << "D RLC: ";
    d.TreeTraversal_RLC(d.GetRoot());
    std::cout << std::endl;

    std::cout << "D width traversal: ";
    d.WidthTraversal(d.GetRoot());
    std::cout << std::endl;

    Node *foo = d.FindKey(21, d.GetRoot());
    std::cout << "FindKey 21 result: " <<  foo->GetKey() << std::endl;
    foo = d.FindMax(d.GetRoot());
    std::cout << "D max: " << foo->GetKey() << std::endl;
    foo = d.FindMin(d.GetRoot());
    std::cout << "D min: " << foo->GetKey() << std::endl;
    std::cout << "D's height is: " << d.FindHeight(d.GetRoot()) << std::endl;
    d = b;
    std::cout << "D: ";
    d.PrintTree(d.GetRoot(),5);
    std::cout << "D's height is: " << d.FindHeight(d.GetRoot()) << std::endl;
    BST dCpy(d);
    std::cout << "dCpy(d): ";
    dCpy.PrintTree(dCpy.GetRoot(), 5);

}
