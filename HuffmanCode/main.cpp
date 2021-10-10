#include <iostream>
#include "HCode.h"

int main()
{
    char message[]{"Mississippi River"};
    char decode[20]{0};
    char code[20]{0};
    Code dodo(message);
    dodo.PrintList();
    dodo.FormTree();
    dodo.PrintTree(5, dodo.GetHead());
    dodo.CodeText(message, code, 20);
    dodo.DecodeText(code, decode, 20);
    std::cout << decode << std::endl;
    return 0;
}
