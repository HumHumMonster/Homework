/*
地图着色(栈的应用)(数组).cpp

*/

#include <iostream>
#include <cstdio>
using namespace std ;

#define N 7
#define M 4

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
    int now = 1 ;
    while (now > 0 && now <= N)
    {
        if (color[now] == M)
        {
            color[now] = 0 ;
            --now ;
            ++color[now] ;
            continue ;
        }
        if (anyConflict(now))
        {
            ++now ;
        }
        else
        {
            ++color[now] ;
        }
    }
    if (now == 0)
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
