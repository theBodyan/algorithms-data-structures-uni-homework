#include "OBST.h"

OBST::OBST(int *d, int *p, int *q, int n)
{
    // init
    int **W = new int*[n + 1];
    int **C = new int*[n + 1];
    int **R = new int*[n + 1];
    root = new Node;
    for(int i = 0; i < n + 1; i++)
    {
        W[i] = new int[n+1];
        C[i] = new int[n+1];
        R[i] = new int[n+1];
    }

    CreateMatrix(p, q, n, W, C, R);
    root = nullptr;
    OTree(d, 0, n, R, root);

    // deletion
    for(int i = 0; i < n; i++)
    {
        delete[] W[i];
        delete[] C[i];
        delete[] R[i];
    }
    delete[] W;
    delete[] C;
    delete[] R;
}

OBST::OBST(const OBST& T)
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

OBST& OBST::operator=(const OBST& cpyOBST)
{
    this->BST::operator=(cpyOBST);
    /*this->Clear();
    this->DelRoot();
    if(cpyOBST.root ==nullptr)
    {
        root=nullptr;
    }
    else
    {
        numOfElem = cpyOBST.numOfElem;
        root=new Node(cpyOBST.root->key);
        Copy(cpyOBST.root->left, root, 0);
        Copy(cpyOBST.root->right, root, 1);
    }*/
    return *this;
}

void OBST::CreateMatrix (int *p, int *q, int n, int **W, int **C, int **R)
{
    int i, j, t;
    for (i=0; i<n+1; i++)
    {
        for(j=0; j<n+1; j++)
        {
            W[i][j]=C[i][j]=R[i][j]=-1;
        }
    }

    //заполнение главной (t=0) диагонали в W и C
    for(i=0; i<n+1; i++)
    {
        W[i][i]=C[i][i]=q[i];
    }

    //заполнение первой (t=1) диагонали в W, C и R
    for(i=0; i<n; i++)
    {
        j=i+1;
        W[i][j]=W[i][i]+p[j]+q[j];
        C[i][j]=W[i][j]+C[i][i]+C[j][j];
        R[i][j]=j;
    }

    int min;
    int k;
    int k_min;
    for(t=2; t<n+1; t++)
    {
        for(i=0; i<n+1-t; i++)
        {
            j=i+t;

            W[i][j]=W[i][j-1]+p[j]+q[j];

            min=C[i][i]+C[i+1][j];

            k_min=i+1;
            for(k=i+2; k<=j; k++) {
                if (C[i][k - 1] + C[k][j] < min)
                {
                    min = C[i][k - 1] + C[k][j];
                    k_min = k;
                }
            }
            C[i][j]=W[i][j]+min;
            R[i][j]=k_min;

        }
    }
    std::cout << C[2][n] << std::endl;
}

Node* OBST::OTree(int *d, int i, int j, int** R, Node* q)
{
    if(i >= j)
    {
        return nullptr;
    }
    int k = R[i][j];
    Node *p = new Node(d[k]);
    if(root == nullptr)
    {
        root = p;
    }
    p->left = OTree(d, i, k-1, R, p);
    p->right = OTree(d, k, j, R, p);
    p->parent = q;
    return p;
}

