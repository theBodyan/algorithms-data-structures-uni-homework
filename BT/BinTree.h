#pragma once
#include <iostream>
#include <queue>

class Node
{
public:
    explicit Node (int k=0, Node *L=NULL, Node *R=NULL, Node *P=NULL);

    int GetKey();

    Node* GetLeft();

    Node* GetRight();

    friend class BinTree;

private:
    int key;
    Node *left, *right, *parent;
};


class BinTree
{
public:
    BinTree();
    // NOTE: the explicit keyword disallows implicit conversions with single argument constructors
    explicit BinTree(int n);
    BinTree(int *a, int n);
    BinTree(const BinTree &);
    BinTree & operator=(const BinTree &);
    ~ BinTree();

    void Add(int k, Node *p);

    void Del(Node *p);
    void DelRoot();

    void TreeTraversal_LCR (Node *p);

    void TreeTraversal_LRC (Node *p);

    void TreeTraversal_RLC (Node *p);

    void WidthTraversal (Node *p);

    Node *FindKey(int k, Node *p);

    Node *FindMax(Node *p);

    Node *FindMin(Node *p);

    int FindHeight(Node *p);

    int CountAllNodes(Node *p);

    Node *GetRoot();
    void Clear();

    void PrintTree(Node *p, int k);

private:
    Node* root;

    int numOfElem;

    Node* Tree(int n, Node *p);

    void Copy(Node *q, Node *p, int f);

    Node* ReachDeepestLeaf(Node *next);

    void CountHeights(Node *p, int counter, int *heights, int &leafCounter);
};
