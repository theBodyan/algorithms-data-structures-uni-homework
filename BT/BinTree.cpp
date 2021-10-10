#include "BinTree.h"

BinTree::BinTree()
{
    root = nullptr;
    numOfElem = 0;
}

BinTree::BinTree(int n)
{
    numOfElem = 1;
    root = new Node;
    root->parent = nullptr;
    root->key = rand()%90 + 9;
    for(int i = 1; i < n; i++)
    {
        Add(rand()%90 + 9, root);
    }
}

BinTree::BinTree(int *a, int n) // int *a - an array of keys, int n is the number of keys
{
    numOfElem = 1;
    root = new Node;
    root->parent = nullptr;
    root->key = a[0];

    for(int i = 1; i < n; i++)
    {
        Add(a[i], root);
    }
}

Node* BinTree::ReachDeepestLeaf(Node *startNode)
{
    Node* deepestNode;
    if(startNode->left != nullptr)
    {
        deepestNode = ReachDeepestLeaf(startNode->left);
    }
    if(startNode->right != nullptr)
    {
        deepestNode = ReachDeepestLeaf(startNode->right);
    }
    if(startNode->right == nullptr && startNode->left == nullptr)
    {
        deepestNode = startNode;
    }
    return deepestNode;
}

BinTree::~BinTree()
{
    // left branch deletion
    while(root->left != nullptr)
    {
        Del(root->left);
    }

    // right branch deletion
    while(root->right != nullptr)
    {
        Del(root->right);
    }
    DelRoot();
}

Node::Node (int k, Node *L, Node *R, Node *P) : key(k), left(L), right(R), parent(P) {}

int Node::GetKey()
{
    return key;
}

Node* Node::GetLeft()
{
    return left;
}

Node* Node::GetRight()
{
    return right;
}

Node * BinTree::Tree(int n, Node *p)
            //построение идеально сбалансированного дерева
            //с n вершинами, p - предок вершины дерева
{
    if(n==0)
    {
        return nullptr;
    }
    Node *q = new Node(rand()%50);
    int nL, nR;
    nL=(n-1)/2;
    nR=n-nL;
    q->left=Tree(nL, q);
    q->right=Tree(nR, q);
    q->parent=p;
    return q;
}

void BinTree::Copy(Node *q, Node *p, int f)
            //копирование дерева с корнем q, p - узел, к которому
            //присоединяется копия
            //f=0 - копируемое дерево будет левым потомком для p;
            //f=1 - копируемое дерево будет правым потомком для p.
{
    if(q==nullptr)
    {
        return;
    }
    Node *t=new Node(q->key);
    t->parent=p;
    if(f==0)
    {
        p->left=t;
    }
    else
    {
        p->right=t;
    }
    Copy(q->left, t, 0);
    Copy(q->right, t, 1);
}



BinTree::BinTree(const BinTree &T)
{
    if(T.root==nullptr)
    {
        root=nullptr;
    }
    else
    {
        root=new Node(T.root->key);
        Copy(T.root->left, root, 0);
        Copy(T.root->right, root, 1);
    }
}

void BinTree::PrintTree(Node *p, int k)
        //вывод дерева на консоль,
        //k - отступ от левой границы консоли
{
    if(p == nullptr)
    {
        return;
    }
    PrintTree(p->right, k+5);
    for(int i=0; i<k; i++)
    {
        std::cout << ' ';
    }
    std::cout << p->key << std::endl;
    PrintTree(p->left, k+5);
}

void BinTree::Add(int k, Node *p)
            //добавление узла с ключом k в дерево с корнем p
{
    if(p->left==nullptr)
    {
        numOfElem++;
        Node *q=new Node(k);
        p->left=q;
        q->parent=p;
        return;
    }
    if(p->right==nullptr)
    {
        numOfElem++;
        Node *q=new Node(k);
        p->right=q;
        q->parent=p;
        //другой вариант:
        //Node *q=new Node (k, nullptr, nullptr, p);
        //p->right=q;
        return;
    }
    if(rand()%2)
    {
        Add(k, p->left);
    }
    else
    {
        Add(k, p->right);
    }

}

void BinTree::Del(Node *p)         //удаление узла p
{
    numOfElem--;
    Node *q=p->parent;
    //удаление листа
    if(p->left==nullptr && p->right==nullptr)
    {
        if(q->left==p)
        {
            q->left = nullptr;
        }
        else
        {
            q->right = nullptr;
        }
        delete p;
        return;
    }
    //у p нет левой ветви
    if(p->left==nullptr && p->right!=nullptr)
    {
        if(q->left==p)
        {
            q->left=p->right;
        }
        else
        {
            q->right=p->right;
        }
         p->right->parent=q;
         delete p;
         return;
    }
    //у p нет правой ветви
    if(p->left!=nullptr && p->right==nullptr)
    {
        if(q->left==p)
        {
            q->left=p->left;
        }
        else
        {
            q->right=p->left;
        }
        p->left->parent=q;
        delete p;
        return;
    }

    //у p есть оба поддерева
    Node *t=p;
    while(t->left!=nullptr)
    {
        t=t->left;
    }

    //вырезаем t из дерева
    if(t->right==nullptr)
    {
        t->parent->left=nullptr;
    }
    else
    {
        t->parent->left=t->right;
        t->right->parent=t->parent;
    }

    //заменяем p узлом t
    t->left=p->left;
    t->right=p->right;
    t->parent=q;

    if(q->left==p)
    {
        q->left=t;
    }
    else
    {
        q->right=t;
    }

    if(p->left!=nullptr)
    {
        p->left->parent=t;
    }

    p->right->parent=t;
    delete p;
    return;
}

void BinTree::DelRoot()
{
    numOfElem--;
    if(root->right == nullptr && root->left == nullptr)
    {
        delete root;
    }
    else if(root->left != nullptr) // substitute the root with a left branch's leaf
    {
        Node *next = root;
        next = ReachDeepestLeaf(next->left);
        root->key = next->key;
        Del(next);
    }
    else if(root->right != nullptr) // substitute the root with a left branch's leaf
    {
        Node *next = root;
        next = ReachDeepestLeaf(next->right);
        root->key = next->key;
        Del(next);
    }
}

void BinTree::TreeTraversal_LCR (Node *p)
            //обход дерева с корнем p, в глубину по принципу
            //лево-корень-право, ключи выводятся на консоль

{
    if(p==nullptr)
    {
        return;
    }
    if(p->left != nullptr)
    {
        TreeTraversal_LCR(p->left);
    }
    std::cout << p->key << ' ';
    if(p->right != nullptr)
    {
        TreeTraversal_LCR(p->right);
    }
}

void BinTree::TreeTraversal_LRC (Node *p)
{
    if(p == nullptr)
    {
        return;
    }
    if(p->left != nullptr)
    {
        TreeTraversal_LRC(p->left);
    }
    if(p->right != nullptr)
    {
        TreeTraversal_LRC(p->right);
    }
    std::cout << p->key << ' ';
}

void BinTree::TreeTraversal_RLC (Node *p)
{
    if(p == nullptr)
    {
        return;
    }
    if(p->right != nullptr)
    {
        TreeTraversal_LRC(p->right);
    }
    if(p->left != nullptr)
    {
        TreeTraversal_LRC(p->left);
    }
    std::cout << p->key << ' ';
}

void BinTree::WidthTraversal (Node *p)
{
    std::queue<Node*> nextToVisit;
    nextToVisit.push(p);
    while(!nextToVisit.empty())
    {
        Node* nextNode = nextToVisit.front();
        nextToVisit.pop();

        std::cout << nextNode->key << ' ';

        if(nextNode->left != nullptr)
        {
            nextToVisit.push(nextNode->left);
        }
        if(nextNode->right != nullptr)
        {
            nextToVisit.push(nextNode->right);
        }
    }
    std::cout << std::endl;
}

Node* BinTree::FindKey(int k, Node *p)
{
    if(p == nullptr || p->key == k)
    {
        return p;
    }
    Node *found = nullptr;
    if(p->right != nullptr)
    {
        found = FindKey(k, p->right);
    }
    if(p->left != nullptr && found == nullptr)
    {
        found = FindKey(k, p->left);
    }
    if(p->key == k)
    {
        found = p;
    }
    return found;
}

Node* BinTree::FindMax(Node *p)
{
    if(p == nullptr)
    {
        return p;
    }
    Node *max = root;
    Node *tmp;
    if(p->right != nullptr)
    {
        tmp = FindMax(p->right);
        if(tmp->key > max->key)
        {
            max = tmp;
        }
    }
    if(p->left != nullptr)
    {
        tmp = FindMax(p->left);
        if(tmp->key > max->key)
        {
            max = tmp;
        }
    }
    if(p->key > max->key)
    {
        max = p;
    }
    return max;
}

Node* BinTree::FindMin(Node *p)
{
    if(p == nullptr)
    {
        return p;
    }
    Node *min = root;
    Node *tmp;
    if(p->right != nullptr)
    {
        tmp = FindMax(p->right);
        if(tmp->key < min->key)
        {
            min = tmp;
        }
    }
    if(p->left != nullptr)
    {
        tmp = FindMax(p->right);
        if(tmp->key < min->key)
        {
            min = tmp;
        }
    }
    if(p->key < min->key)
    {
        min = p;
    }
    return min;
}

void BinTree::CountHeights(Node *p, int counter, int *heights, int &leafCounter)
{
    counter++;
    if(p->left != nullptr)
    {
        CountHeights(p->left, counter, heights, leafCounter);
    }
    if(p->right != nullptr)
    {
        CountHeights(p->right, counter, heights, leafCounter);
    }
    if(p->right == nullptr && p->left == nullptr)
    {
        heights[leafCounter] = counter;
        leafCounter++;
    }
}

int BinTree::FindHeight(Node *p)
{
    int maxHeight = 0;
    int counter = 0;
    int leafCounter = 0;
    int *heights = new int[this->CountAllNodes(root)];

    CountHeights(p, counter, heights, leafCounter);

    maxHeight = heights[0];
    for(int i = 1; i <= leafCounter; i++)
    {
        if(maxHeight < heights[i])
        {
            maxHeight = heights[i];
        }
    }

    delete[] heights;
    return maxHeight;
}

int BinTree::CountAllNodes(Node *p)
{
    /*if(p == nullptr)
    {
        return 0;
    }
    int c = 1;
    if(p->right != nullptr)
    {
        c = CountAllNodes(p->right);
    }
    if(p->left != nullptr)
    {
        c = CountAllNodes(p->left);
    }
    return c;*/
    return numOfElem;
}

Node* BinTree::GetRoot()
{
    return root;
}

void BinTree::Clear()
{
    while(root->left != nullptr)
    {
        Del(root->left);
    }

    // right branch deletion
    while(root->right != nullptr)
    {
        Del(root->right);
    }
}

BinTree & BinTree::operator=(const BinTree & cpyBT)
{
    this->Clear();
    this->DelRoot();
    if(cpyBT.root ==nullptr)
    {
        root=nullptr;
    }
    else
    {
        numOfElem = cpyBT.numOfElem;
        root=new Node(cpyBT.root->key);
        Copy(cpyBT.root->left, root, 0);
        Copy(cpyBT.root->right, root, 1);
    }
    return *this;
}
