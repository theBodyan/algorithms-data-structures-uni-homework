#pragma once
#include "BinTree.h"
/*VIRTUAL FUNCTIONS*/
/* Virtual functions help support the concept of polymorphism & implicit conversions
 * I haven't got a chance to really understand how the following works:
 * Base* baseEntity; Derived* derivedEntity;
 * Base* dbEntity = derivedEntity; -- what happens here? Does it make sense to do it?
 * Does it make sense to pass a derived entity to a function that accepts the base class?
 * Is it implicit conversion that's happening? Is there something else going on?
 * What virtual functions do is they make calls to appropriate functions in such cases.
 * You're telling the compiler that it may need to search for a particular implementation of a function.
 * Example:
 * void function(Base* entity) {entity->Method();}
 * ... main() {Base* baseEntity; Derived* derivedEntity; function(baseEntity); function(derivedEntity); }
 * -- the latter function call wouldn't work as you'd expect if Base::Method() is not virtual*/

class BST: public BinTree
{
public:
    BST(): BinTree() {};
    explicit BST(int n);
    //n - количество ключей, ключи случайны
    BST(int *a, int n);
    //a - массив ключей, n - количество ключей
    BST(const BST&);
    BST & operator= (const BST&);

    virtual ~ BST() {};

    virtual void Add(int k, Node *p) override;
    //добавление узла с ключом k в дерево с корнем p

    virtual void DelRoot() override;             //удаление корня

    virtual Node *FindKey(int k, Node *p) override;
    //поиск узла с ключом k в дереве с корнем p
    virtual Node *FindMax(Node *p) override;
    //поиск узла с max ключом в дереве с корнем p
    virtual Node *FindMin(Node *p) override;
        //поиск узла с min ключом в дереве с корнем
private:
    Node* ReachLeftmostLeaf(Node *startNode);
    Node* ReachRightmostLeaf(Node *startNode);
};
