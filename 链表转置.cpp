#include <iostream>
using namespace std ;

template <typename ElemType>

struct Node
{
    ElemType data ;
    Node* next = NULL ;
    Node(){}
    Node(ElemType d)
    {
        data = d ;
    }
    void release()
    {
        if (next)
        {
            next->release() ;
            delete next ;
        }
    }
};

template<typename ElemType>
struct LinkList
{
    typedef Node <ElemType> Node ;
    Node header ;
    int length = 0 ;
    ~LinkList()
    {
        header.release() ;
    }
    void insert(ElemType e)
    {
        Node *p = new Node() ;
        p -> data = e ;
        p -> next = header.next ;
        header.next = p ;
        length++ ;
    }
    Node* get(int index)
    {
        Node *p = header.next ;
        while (p != NULL && index > 0)
        {
            p = p -> next ;
            index-- ;
        }
        // ("%d" , p -> data) ;
        return p ;
    }

    void output()
    {
        Node *p = header.next ;
        cout << "header->" ;
        while (p)
        {
            cout << p -> data << "->" ;
            p = p -> next ;
        }
        cout << "^" << endl ;
    }

    Node *find(ElemType e)
    {
        Node *p = header.next ;
        while (p)
        {
            if (p -> data == e)
                break ;
            p = p -> next ;
        }
        return p ;
    }

    void deleteAfter(Node *p)
    {
        if (p == NULL)
            return ;
        Node * q = p -> next ;
        if (q == NULL)
            return ;
        p -> next = q -> next ;
        delete
        q ;
        length-- ;
    }

//    void ReverseList()
//    {
//        if (header.next == NULL)
//            return ;
//        Node* dummy = new Node() ;
//        dummy -> next = header.next ;
//        Node* pre = dummy -> next ;
//        Node* lat = pre -> next ;
//        while (lat != NULL)
//        {
//            pre -> next = lat -> next ;
//            lat -> next = dummy -> next ;
//            dummy -> next = lat ;
//            lat = pre -> next ;
//        }
//        header.next = dummy -> next ;
//    }

//递归写法
    Node* Reverse(Node* p)
    {
        if (p -> next == NULL)
        {
            header.next = p ;
            return p ;
        }
        return Reverse(p -> next) -> next = p ;
    }

    void ReverseList()
    {
        Node* p = header.next ;
        Reverse(p) ;
        p -> next = NULL ;
    }

};



int main ()
{
    LinkList<int> L ;
    L.insert(1) ;
    L.insert(2) ;
    L.insert(3) ;
    L.insert(4) ;
    L.insert(5) ;
    L.insert(6) ;

    printf ("%d\n" , L.get(3)->data ) ;

    L.output() ;
    L.ReverseList() ;
    L.output() ;
}
