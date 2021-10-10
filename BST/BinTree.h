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
    friend class BST;

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
    virtual ~BinTree();

    virtual void Add(int k, Node *p);

    virtual void Del(Node *p);
    virtual void DelRoot();

    void TreeTraversal_LCR (Node *p);

    void TreeTraversal_LRC (Node *p);

    void TreeTraversal_RLC (Node *p);

    void WidthTraversal (Node *p);

    virtual Node *FindKey(int k, Node *p);

    virtual Node *FindMax(Node *p);

    virtual Node *FindMin(Node *p);

    int FindHeight(Node *p);

    int CountAllNodes(Node *p);

    Node *GetRoot();
    void Clear();

    void PrintTree(Node *p, int k);

protected:
    Node* root;

    int numOfElem;

    Node* Tree(int n, Node *p);

    void Copy(Node *q, Node *p, int f);

    Node* ReachDeepestLeaf(Node *next);

    void CountHeights(Node *p, int counter, int *heights, int &leafCounter);
};
