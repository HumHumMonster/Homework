#pragma once
#include <cstring>
#include <iostream>
using namespace std ;
static char screen[40][80] ;

struct BinTree
{
    char data ;
    BinTree *lchild , *rchild ;
    BinTree(char d)
    {
        data = d ;
        lchild = NULL ;
        rchild = NULL ;
    }

    ~BinTree()
    {
        if (lchild) delete lchild ;
        if (rchild) delete rchild ;
    }

    static BinTree* create (char *str , int &index)
    {
        char ch = str[index++] ;
        if (ch == '#')
            return NULL ;
        BinTree *node = new BinTree(ch) ;
        node -> lchild = create(str , index) ;
        node -> rchild = create(str , index) ;
        return node ;
    }
    int deep()
    {
        int ldeep = (lchild == NULL) ? 0 : lchild -> deep() ;
        int rdeep = (rchild == NULL) ? 0 : rchild -> deep() ;
        return 1 + (ldeep > rdeep ? ldeep : rdeep) ;
    }
    BinTree* create()
    {
        char ch ;
        scanf ("%c" , &ch) ;
        if (ch == '#')
            return NULL ;
        BinTree *node = new BinTree(ch) ;
        node -> lchild = create() ;
        node -> rchild = create() ;
        return node ;
    }

    void output()
    {
        memset (screen , ' ' , sizeof(screen)) ;
        draw(0 , 0 , NULL) ;
        int height = deep() * 2 ;
        for (int i = 0 ; i < height ; ++i)
        {
            screen[i][40] = '\0' ;
            printf ("%s\n" , screen[i]) ;
        }
    }
    int draw(int startx , int y , BinTree *parent)
    {
        int endx = startx ;
        if (lchild)
            endx = lchild -> draw (startx , y + 2 , this) + 1 ;
        int centerx = endx ;
        screen[y][endx++] = data ;
        if (rchild)
            endx = rchild -> draw (endx , y + 2 , this) + 1 ;

        if (parent)
        {
            if (parent -> lchild == this)
            {
                for (int x = centerx ; x <= endx ; ++x)
                    screen[y - 1][x] = '-' ;
                screen[y - 1][centerx] = '/' ;
            }
            else
            {
                for (int x = startx ; x <= centerx ; ++x)
                    screen[y - 1][x] = '-' ;
                screen[y - 1][centerx] = '\\' ;
            }
        }
        return endx ;
    }

    void preOrder()
    {
        printf ("%c" , data) ;
        if (lchild) lchild -> postOrder() ;
        if (rchild) rchild -> postOrder() ;
    }

    void postOrder()
    {
        if (lchild) lchild -> postOrder() ;
        if (rchild) rchild -> postOrder() ;
        printf ("%c" , data) ;
    }

    static BinTree * rebuildByPreIn(char* PreOrder , char* InOrder , int Len)
    {
        if (Len == 0)
            return NULL ;
        char r = PreOrder[0] ;
        BinTree *R = new BinTree(r) ;
        int pos = 0 ;
        while (pos < Len)
        {
            if (InOrder[pos] == r)
                break ;
            ++pos ;
        }
        R -> lchild = rebuildByPreIn(PreOrder + 1 , InOrder , pos) ;
        ++pos ;
        R -> rchild = rebuildByPreIn(PreOrder + pos , InOrder + pos , Len - pos) ;
        return R ;
    }
};


int main ()
{
    BinTree *tree ;
    int index = 0 ;
    tree = tree->create("AB##CDF###E##" , index) ;
    tree->output() ;
    printf ("后序遍历顺序为：") ;
    tree -> postOrder() ;
    delete tree ;
    printf ("\n") ;
    tree = BinTree::rebuildByPreIn("abdgcefh" , "dgbaechf" , 8) ;
    tree -> output() ;
    delete tree ;
    return 0 ;
}

