/*
地图着色(栈的应用)(自定义栈).cpp

*/


#include <iostream>
#include <cstdio>
using namespace std ;

#define N 7
#define M 4

template <typename ElemType>

struct Stack
{
    ElemType *items ;
    int capacity ;
    int top ;
    Stack(int c = 10)
    {
        top = 0 ;
        capacity = 10 ;
        items = new ElemType[capacity] ;
    }
    ~Stack()
    {

    }
    void output()
    {
        for (int i = 0 ; i < top ; ++i)
            cout << items[i] << " " ;
        cout << endl ;
    }
    void push(ElemType e)
    {
        items[top++] = e ;
    }
    ElemType peek()
    {
        return items[top - 1] ;
    }
    ElemType pop()
    {
        --top ;
        return items[top] ;
    }
};


bool map[][N + 1] = {
    {} ,
    {-1 , 0 , 1 , 1 , 1 , 1 , 1 , 0},

    {-1 , 1 , 0 , 0 , 0 , 0 , 1 , 0},

    {-1 , 1 , 0 , 0 , 1 , 1 , 0 , 0},

    {-1 , 1 , 0 , 1 , 0 , 1 , 1 , 0},

    {-1 , 1 , 0 , 1 , 1 , 0 , 1 , 0},

    {-1 , 1 , 1 , 0 , 1 , 1 , 0 , 0},

    {-1 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
} ;

int color[N + 1] ;
bool anyConflict(int r)
{
    for (int i = 1 ; i < r ; ++i)
    {
        if (map[i][r] && color[i] == color[r])
            return false ;
    }
    return true ;
}

char* colorName[] = {"紫" , "黄" , "红" , "绿"} ;

void Show()
{
    printf ("\n") ;
    printf ("i     = : ") ;
    for (int i = 1 ; i <= N ; ++i)
    {
        printf ("%3d " , i) ;
    }
    printf("\n") ;
    printf ("color = : ") ;
    for (int i = 1 ; i <= N ; ++i)
    {
        printf (" %s " , colorName[color[i]]) ;
    }
    printf ("\n") ;
}

void fillColor()
{
    Stack <int> S ;
    S.push(1) ;
    while (S.top > 0 && S.top <= 7)
    {
        int now = S.peek() ;
        if (color[now] == M)
        {
            color[now] = 0 ;
            S.pop() ;
            ++color[S.peek()] ;
            continue ;
        }
        if (anyConflict(now))
        {
            S.push(now + 1) ;
        }
        else
        {
            ++color[now] ;
        }
    }
    if (S.top == 0)
    {
        printf("失败\n") ;
    }
    else
    {
        printf ("成功\n") ;
        Show() ;
    }
}



int main ()
{
    for (int i = 1 ; i <= N ; ++i)
    {
        for (int j = 1 ; j <= N ; ++j)
            printf ("%2d" , map[i][j]) ;
        printf("\n") ;
    }
    fillColor() ;
}
