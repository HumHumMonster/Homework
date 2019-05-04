#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std ;

typedef int ElemType ;

struct BTreeNode
{
    ElemType data ;
    BTreeNode* left ;
    BTreeNode* right ;
};


void Insert(BTreeNode* &BST , const ElemType &item)
{
    if (BST == NULL)
    {
        BTreeNode* p = new BTreeNode ;
        p -> data = item ;
        p -> left = p -> right = NULL ;
        BST = p ;
    }
    else if (item < BST -> data)
        Insert (BST -> left , item) ;
    else
        Insert (BST -> right , item) ;
}

void Init(BTreeNode* &BST)
{
    BST = NULL ;
}

int Num_OneChildNode(BTreeNode* BST)
{
    if (BST == NULL)
        return 0 ;
    if (BST -> left == NULL && BST -> right == NULL)
        return 0 ;
    if (BST -> left == NULL)
    {
        return Num_OneChildNode(BST -> right) + 1 ;
    }
    else if (BST -> right == NULL)
    {
        return Num_OneChildNode(BST -> left) + 1 ;
    }
    else
        return Num_OneChildNode(BST -> left) + Num_OneChildNode(BST -> right) ;
}

int BiggestData(BTreeNode* BST)
{
    if (BST == NULL)
    {
        printf ("没有可查找元素") ;
        return 0 ;
    }
    if (BST -> right == NULL)
        return BST -> data ;
    else
        return BiggestData(BST -> right) ;
}

BTreeNode* root ;

int main ()
{

    Init (root) ;
    Insert(root , 5) ;
    Insert(root , 4) ;
    Insert(root , 6) ;
    Insert(root , 3) ;
    Insert(root , 2) ;
    Insert(root , 8) ;
    Insert(root , 7) ;
    printf ("最大值为 : %d\n" , BiggestData(root)) ;
    printf ("%d" , Num_OneChildNode(root)) ;
}
