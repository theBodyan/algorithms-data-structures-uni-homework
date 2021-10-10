#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>

class Node
{
    char *str;
    int freq;
    Node *next, *left, *right;

public:
    Node()
    {
        str=new char[1];
        str[0]='\0';
        freq=0;
        next=left=right=NULL;
    }
    Node(char s[], int fr=0, Node *N=NULL, Node *L=NULL, Node *R=NULL)
    {
        int n=strlen(s);
        str=new char[n+1];
        strcpy(str, s);
        freq=fr;
        next=N;
        left=L;
        right=R;
    }
    ~Node()
    {
        delete []str;
    }

    friend class Code;
};

class Code
{
    Node *head;
    int type = 0;         //type==0 -- линейный список, type==1 -- дерево

    //вспомогательные функции
    void Del(Node *p, Node *parent = nullptr);
    bool Find(char ch, char p[]); //поиск символа ch в строке p;
    void Copy(Node *q, Node *p, int f);
    //копирование дерева с корнем q,
    //p - узел, к которому присоединяется копия
    //f=0 - копируемое дерево будет левым потомком для p;
    //f=1 - копируемое дерево будет правым потомком для p.

public:
    Code()
    {
        head=NULL;
        type=0;
    }
    explicit Code(char *p);        //создает список из символов строки
    ~Code();
    Code(const Code &);
    Code & operator= (const Code &);

    void AddToTail(char s[], int k);
    void AddToTail(Node *p);

    void AddToHead(char s[], int k);
    void AddToHead(Node *p);

    void AddAfter(Node *pr, char s[], int k);
    void AddAfter(Node *pr, Node *p);    //размещение узла p после узла pr

    void DelHead();
    void Clear();
    void Clear(Node *pr, Node *t);
    //t-- удаляемый узел, pr -- его родитель
    bool Empty();

    void PrintList();
    void PrintTree(int k, Node *p);

    Node* GetHead();

    void FormTree();        //преобразование списка в дерево
    void CodeText(char s[], char code[], int n);
    //кодирование строки s, n -- размер строки code
    void DecodeText(char code[], char s[], int n);
    //декодирование строки code, n -- размер строки s

};
