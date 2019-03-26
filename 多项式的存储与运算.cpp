#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std ;

#define eps 1e-8

template <typename ElemType>

struct Node         //节点类
{
    ElemType data ;
    Node *next = NULL ;
    Node(){}
    Node(ElemType d)
    {
        data = d ;
    }
};

template <typename ElemType>

struct LinkList     //链表类
{
    typedef Node<ElemType> Node ;
    Node header ;
    void insert (ElemType e)
    {
        Node *p = new Node() ;
        p -> data = e ;
        p -> next = header.next ;
        header.next = p ;
    }
};

struct Monomial     //单项式类
{
    double coef ;
    int exp ;
    Monomial(){}
    Monomial(double c , int e)
    {
        coef = c ;
        exp = e ;
    }
    void output()
    {
        printf ("%.f" , fabs(coef)) ;
        if(exp)
        printf (" x^%d" , exp) ;
    }
    Monomial add(Monomial a)
    {
        a.exp += exp ;
        return a ;
    }
};

struct Polynomial:public LinkList<Monomial>     //多项式类
{
    void output()
    {
        Node *p = header.next ;
        p -> data.output() ;
        p = p -> next ;
        while (p)
        {
            if (p -> data.coef > 0)
                printf (" + ") ;
            else
                printf (" - ") ;
            p -> data.output() ;
            p = p -> next ;
        }
        printf ("\n") ;
    }
    Polynomial operator + (Polynomial &other)
    {
        Polynomial *result = new Polynomial() ;
        Node *p = header.next ;
        Node *q = other.header.next ;
        Node *t = &result -> header ;
        Node *neww ;
        while (p && q)
        {
            if (p -> data.exp < q->data.exp)
            {
                neww = new Node ;
                neww -> next = NULL ;
                neww -> data.coef = p -> data.coef ;
                neww -> data.exp = p -> data.exp ;
                t -> next = neww ;
                t = neww ;
                p = p -> next ;
            }
            else if (p -> data.exp > q->data.exp)
            {
                neww = new Node ;
                neww -> next = NULL ;
                neww -> data.coef = q -> data.coef ;
                neww -> data.exp = q -> data.exp ;
                t -> next = neww ;
                t = neww ;
                q = q -> next ;
            }
            else
            {
                if (fabs(p -> data.coef + q -> data.coef) > eps)        //如果两数相加不等于0
                {
                    neww = new Node ;
                    neww -> next = NULL ;
                    neww -> data.coef = p -> data.coef + q -> data.exp ;
                    neww -> data.exp = p -> data.exp ;
                    t -> next = neww ;
                    t = neww ;
                }
                p = p -> next ;
                q = q -> next ;
            }
        }
        while (p)
        {
            neww = new Node ;
            neww -> next = NULL ;
            neww -> data.coef = p -> data.coef ;
            neww -> data.exp = p -> data.exp ;
            t -> next = neww ;
            t = neww ;
            p = p -> next ;
        }
        while (q)
        {
            neww = new Node ;
            neww -> next = NULL ;
            neww -> data.coef = q -> data.coef ;
            neww -> data.exp = q -> data.exp ;
            neww -> next = NULL ;
            t -> next = neww ;
            t = neww ;
            q = q -> next ;
        }
        return *result ;
    }
};

int main ()
{
    Polynomial A ;
    A.insert(Monomial(-6 , 7)) ;
    A.insert(Monomial(5 , 3)) ;
    A.insert(Monomial(3 , 0)) ;
    A.output() ;

    Polynomial B ;
    B.insert(Monomial(-7 , 9)) ;
    B.insert(Monomial(6 , 7)) ;
    B.insert(Monomial(3 , 3)) ;
    B.output() ;

    Polynomial C = A + B ;
    C.output() ;
    return 0 ;
}


/*
3 + 5 x^3 - 6 x^7
3 x^3 + 6 x^7 - 7 x^9
3 + 8 x^3 - 7 x^9
*/
