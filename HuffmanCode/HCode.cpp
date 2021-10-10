#include "HCode.h"

Code::Code(char *p)
{
    type=0;
    //создание массива букв и их частот
    int i, TAB[256]={0};
    for(i=0; p[i]; i++)
        TAB[p[i]]++;

    //поиск 1-го (по ASCII) символа из p и создание головы списка
    char s[2]; s[1]='\0';
    for(i=0; i<256 && TAB[i]==0; i++);

    if(i==256)
    {
        puts("string is empty");
        head=NULL;
        return;
    }
    s[0]=i;
    head=new Node(s, TAB[i]) ;
    i++;

    //формирование упорядоченного по частоте линейного
    //списка символов строки p
    for( ;i<256; i++)
        if(TAB[i]!=0)
        {s[0]=i;
            if(TAB[i]<head->freq) AddToHead(s, TAB[i]);
            else{Node *t=head;
                while(t->next && t->next->freq<TAB[i])
                    t=t->next;
                if(t->next==NULL) AddToTail(s, TAB[i]);
                else AddAfter(t, s, TAB[i]);
            }
        }
}




void Code::FormTree()    //преобразование списка в дерево
{
    if(head==NULL)
    {
        puts("list is empty");
        return;
    }

    type=1;
    Node *q, *p1, *p2, *t;
    int n1, n2, fr;
    char *s;

    while(head->next != 0)
    {//создание нового узла
        p1=head;
        p2=head->next;
        n1=strlen(p1->str);
        n2=strlen(p2->str);
        s = new char[n1+n2+1];
        strcpy(s, p1->str);
        strcat(s, p2->str);
        fr=p1->freq + p2->freq;
        q=new Node(s, fr, NULL, p1, p2);
        head=p2->next;
        delete []s;

        //размещение q в списке;
        t=head;
        if(t==NULL)
        {
            head=q;
        }
        else
        {
            while(t->next && t->next->freq < fr)
                t=t->next;
            if(t->next==NULL)
            {
                AddToTail(q);
            }
            else
            {
                AddAfter(t, q);
            }
        }
    }
}

void Code::CodeText(char s[], char code[], int n)      //кодирование строки s
{
    if(type==0)
    {
        puts("coding is impossible");
        return;
    }

    //создание массива букв и их частот
    int i, TAB[256]={0};
    for(i=0; s[i]; i++)
        TAB[s[i]]++;

    //создание кодовой таблицы
    char CodeTAB[256][10];
    Node *t;
    for(i=0; i<256; i++)
        CodeTAB[i][0]='\0';

    for(i=0; i<256; i++) {
        if (TAB[i] != 0) {
            t = head;
            while (t->left || t->right)
            {
                if (t->left && Find(i, t->left->str))
                {
                    strcat(CodeTAB[i], "0");
                    t = t->left;
                }
                else
                {
                    strcat(CodeTAB[i], "1");
                    t = t->right;
                }
            }
        }
    }
//формирование закодированного текста:
    code[0]='\0';
    for(i=0; s[i]; i++)
    {
        strcat(code, CodeTAB[s[i]]);
    }

}

bool Code::Find(char ch, char p[])
{
    for(int i =0; i < strlen(p); i++)
    {
        if(p[i] == ch)
        {
            return true;
        }
    }
    return false;
}

void Code::Copy(Node *q, Node *p, int f)
{
    if(q==nullptr)
    {
        return;
    }
    Node *t=new Node(q->str, q->freq);
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

void Code::Del(Node *p, Node *parent)         //удаление узла p
{
    //удаление листа
    if(p->left==nullptr && p->right==nullptr)
    {
        if(parent->left==p)
        {
            parent->left = nullptr;
        }
        else
        {
            parent->right = nullptr;
        }
        delete p;
        return;
    }
    //у p нет левой ветви
    if(p->left==nullptr && p->right!=nullptr)
    {
        if(parent->left==p)
        {
            parent->left=p->right;
        }
        else
        {
            parent->right=p->right;
        }
        delete p;
        return;
    }
    //у p нет правой ветви
    if(p->left!=nullptr && p->right==nullptr)
    {
        if(parent->left==p)
        {
            parent->left=p->left;
        }
        else
        {
            parent->right=p->left;
        }
        delete p;
        return;
    }

    //у p есть оба поддерева
    Node *t=p;
    Node *t_parent;
    while(t->left!=nullptr)
    {
        t_parent = t;
        t=t->left;
    }

    //вырезаем t из дерева
    if(t->right==nullptr)
    {
        t_parent->left=nullptr;
    }
    else
    {
        t_parent->left=t->right;
        t = t_parent;
    }

    //заменяем p узлом t
    t->left=p->left;
    t->right=p->right;
    t_parent = parent;

    if(parent->left==p)
    {
        parent->left=t;
    }
    else
    {
        parent->right=t;
    }

    delete p;
    return;
}


Code::~Code()
{
    if(type == 0)
    {
        Node* tmp;
        while (head != nullptr)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    else if(type == 1)
    {
        while(head->left != nullptr)
        {
            Del(head->left, head);
        }

        // right branch deletion
        while(head->right != nullptr)
        {
            Del(head->right, head);
        }
        DelHead();
    }
}

Code::Code(const Code & cpyCode)
{
    if(cpyCode.type == 0)
    {
        head = new Node(cpyCode.head->str, cpyCode.head->freq);
        Node* cpyTmp = cpyCode.head->next;
        Node* tmp = head;
        while(cpyTmp != nullptr)
        {
            tmp->next = new Node(cpyTmp->str, cpyTmp->freq);
            tmp = tmp->next;
            cpyTmp = cpyTmp->next;
        }
    }
    else if(cpyCode.type == 1)
    {
        if(cpyCode.head==nullptr)
        {
            head=nullptr;
        }
        else
        {
            head=new Node(cpyCode.head->str, cpyCode.head->freq);
            Copy(cpyCode.head->left, head, 0);
            Copy(cpyCode.head->right, head, 1);
        }
    }
}

Code& Code::operator=(const Code & cpyCode)
{

    if(cpyCode.type == 0)
    {
        head = new Node(cpyCode.head->str, cpyCode.head->freq);
        Node* cpyTmp = cpyCode.head->next;
        Node* tmp = head;
        while(cpyTmp != nullptr)
        {
            tmp->next = new Node(cpyTmp->str, cpyTmp->freq);
            tmp = tmp->next;
            cpyTmp = cpyTmp->next;
        }
    }
    else if(cpyCode.type == 1)
    {
        if(cpyCode.head==nullptr)
        {
            head=nullptr;
        }
        else
        {
            head=new Node(cpyCode.head->str, cpyCode.head->freq);
            Copy(cpyCode.head->left, head, 0);
            Copy(cpyCode.head->right, head, 1);
        }
    }
    return *this;
}

void Code::AddToTail(char s[], int k)
{
    Node *t = head;
    Node *q = new Node(s, k, NULL, NULL, NULL);
    if (t == NULL)
    {
        head = q;
    }
    else
    {
        while (t->next != NULL)
            t = t->next;
        t->next = q;
    }
}

void Code::AddToTail(Node *p)
{
    Node *t = head;
    if (t == NULL)
    {
        head = p;
    }
    else
    {
        while (t->next != NULL)
            t = t->next;
        t->next = p;
        p->next = NULL;
    }
}
void Code::AddToHead(char s[], int k)
{
    Node *t = head;
    Node *q = new Node(s, k, NULL, NULL, NULL);
    if (t == NULL)
    {
        head = q;
    }
    else
    {
        q->next = head;
        head = q;
    }
}

void Code::AddToHead(Node *p)
{
    Node *t = head;
    if (t == NULL)
    {
        head = p;
    }
    else
    {
        p->next = head;
        head = p;
    }
}

void Code::AddAfter(Node *pr, char s[], int k)
{
    Node *q = new Node(s, k, NULL, NULL, NULL);
    q->next = pr->next;
    pr->next = q;
}

void Code::AddAfter(Node *pr, Node *p)
{
    p->next = pr->next;
    pr->next = p;
}

void Code::Clear()
{
    if (type == 0)
    {
        Node* tmp, *tmp_ = head->next;
        while (tmp_ != nullptr)
        {
            tmp = tmp_;
            tmp_ = tmp->next;
            delete tmp;
        }
    }
    else if (type == 1)
    {
        while (head->left != nullptr)
        {
            Del(head->left, head);
        }

        // right branch deletion
        while (head->right != nullptr)
        {
            Del(head->right, head);
        }
    }
}

void Code::Clear(Node *pr, Node *t)
{
    if(type == 0)
    {
        pr->next = nullptr;
    }
    else if(type == 1)
    {
        (pr->left == t ? pr->left = nullptr : pr->right = nullptr);

        while(t->left != nullptr)
        {
            Del(t->left, t);
        }
        while(t->right != nullptr)
        {
            Del(t->right, t);
        }
    }
}

bool Code::Empty()
{
    if(type == 0)
    {
        if(head->next == nullptr)
        {
            return true;
        }
        return false;
    }
    if(type == 1)
    {
        if(head->left == nullptr && head->right == nullptr)
        {
           return true;
        }
        return false;
    }
    return true;
}

void Code::PrintList()
{
    Node* tmp = head;
    int c = 0;
    while(tmp != nullptr)
    {
        std::cout << c << "->" << tmp->str << " ";
        c++;
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

void Code::PrintTree(int k, Node *p)
{
    if(p == nullptr)
    {
        return;
    }
    PrintTree(k+5, p->right);
    for(int i=0; i<k; i++)
    {
        std::cout << ' ';
    }
    std::cout << p->str << std::endl;
    PrintTree(k+5, p->left);
}

void Code::DelHead()
{
    Node *t = head;
    head = head->next;
    t->next = NULL;
    delete t;
}

Node* Code::GetHead()
{
    return head;
}

void Code::DecodeText(char code[], char s[], int n)
{
    if(type == 0)
    {
        std::cout << "We can't decode a linked list" << std::endl;
        return;
    }
    Node* tmp = head;
    for(int i =0; code[i]; i++)
    {
        if(code[i] == '0')
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }
        if(tmp->left == nullptr && tmp->right == nullptr)
        {
            strcat(s, tmp->str);
            tmp = head;
        }
    }
}
