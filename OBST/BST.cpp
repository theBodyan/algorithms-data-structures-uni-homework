#include "BST.h"

BST::BST(int n)        //n - количество ключей, ключи случайны
{
    numOfElem = n;
    if(n==0)
    {
        root=nullptr;
    }
    else
    {
        root= new Node(rand()%50);
        for (int i=1; i<n; i++)
        {
          Add(rand()%90+9, root);
        }
    }
}

BST::BST(int *a, int n)        //n - количество ключей, ключи случайны
{
    numOfElem = n;
    if(n==0)
    {
        root=nullptr;
    }
    else
    {
        root = new Node(a[n/2]);
        for (int i=0; i<n; i++) {
            if (i == n / 2)
            {
                continue;
            }
            Add(a[i], root);
        }
    }
}

BST::BST(const BST &T)
{
    if(T.root==nullptr)
    {
        root=nullptr;
    }
    else
    {
        numOfElem = T.numOfElem;
        root=new Node(T.root->key);
        Copy(T.root->left, root, 0);
        Copy(T.root->right, root, 1);
    }
}

BST & BST::operator=(const BST &cpyBST)
{
    this->Clear();
    this->DelRoot();
    if(cpyBST.root ==nullptr)
    {
        root=nullptr;
    }
    else
    {
        numOfElem = cpyBST.numOfElem;
        root=new Node(cpyBST.root->key);
        Copy(cpyBST.root->left, root, 0);
        Copy(cpyBST.root->right, root, 1);
    }
    return *this;
}

Node* BST::ReachLeftmostLeaf(Node *startNode)
{
    Node* leftmostLeaf;
    if(startNode->left != nullptr)
    {
        leftmostLeaf = ReachLeftmostLeaf(startNode->left);
    }
    else
    {
        leftmostLeaf = startNode;
    }
    return leftmostLeaf;
}

Node* BST::ReachRightmostLeaf(Node *startNode)
{
    Node* rightmostLeaf;
    if(startNode->right != nullptr)
    {
        rightmostLeaf = ReachRightmostLeaf(startNode->right);
    }
    else
    {
        rightmostLeaf = startNode;
    }
    return rightmostLeaf;
}


void BST::DelRoot()
{
    numOfElem--;
    if(root->right == nullptr && root->left == nullptr)
    {
        delete root;
    }
    else if(root->left != nullptr)
    {
        Node* tmp;
        tmp = ReachRightmostLeaf(root->left);
        root->key = tmp->key;
        Del(tmp);
    }
    else if(root->right != nullptr)
    {
        Node* tmp;
        tmp = ReachLeftmostLeaf(root->right);
        root->key = tmp->key;
        Del(tmp);
    }
}

void BST::Add(int k, Node *p)
            //добавление узла с ключом k в дерево с корнем p
{
    Node *q;
    if(k < p->key)
    {
        if (p->left == nullptr)
        {
            numOfElem++;
            q = new Node(k);
            p->left = q;
            q->parent = p;
        }
        else
        {
            Add(k, p->left);
        }
    }
    else if(p->right==nullptr)
    {
        numOfElem++;
        q=new Node(k);
        p->right=q;
        q->parent=p;
    }
    else
    {
        Add(k, p->right);
    }
}

Node* BST::FindKey(int k, Node *p)
{
    if(p == nullptr || p->key == k)
    {
        return p;
    }
    Node *found = nullptr;
    if(p->key < k)
    {
        if(p->right != nullptr)
        {
            found = FindKey(k, p->right);
        }
    }
    else if(p->key > k)
    {
        if(p->left != nullptr)
        {
            found = FindKey(k, p->right);
        }
    }
    if(p->key == k)
    {
        found = p;
    }
    return found;
}

Node* BST::FindMax(Node *p) {
    if (p == nullptr)
    {
        return p;
    }
    if(p->right != nullptr)
    {
        return ReachRightmostLeaf(p);
    }
    else
    {
        return p;
    }
}

Node* BST::FindMin(Node *p)
{
    if(p == nullptr)
    {
        return p;
    }
    if(p->left != nullptr)
    {
        return ReachLeftmostLeaf(p);
    }
    else
    {
        return p;
    }
}

/*
void BST::Del(Node *p)          //удаление узла p
{
    Node *q=p->parent;

    //удаление листа
    if(p->left==nullptr && p->right==nullptr)
    {
        if(q->left==p)
        {
            q->left==nullptr;
        }
        else
        {
            q->right==nullptr;
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
        p->right->parent = q;
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
    Node *t=p->left;
    if(t->right==nullptr)
    {
        t->parent=q;
        if(q->left==p) q->left=t;
        else q->right=t;
        t->right=p->right;
        p->right->parent=t;
    }
    else
    {
        while(t->right != nullptr)
        {
            t=t->right;
        }
        t->parent->right=t->left;
        if(t->left!=nullptr)
        {
            t->left->parent=t->parent;
        }

        t->left=p->left;
        t->right=p->right;
        p->left->parent=t;
        p->right->parent=t;

        t->parent=q;
        if(q->left==p)
        {
            q->left=t;
        }
        else
        {
            q->right=t;
        }
    }

    delete p;
}*/
