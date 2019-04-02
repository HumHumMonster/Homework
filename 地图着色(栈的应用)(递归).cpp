/*
地图着色(栈的应用)(递归).cpp

*/


#include <stdio.h>


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

bool fillColor(int now)
{
    if (now > N)
        return true ;
    for (int i = 0 ; i < M ; ++i)
    {
        color[now] = i ;
        if (anyConflict(now))
        {
            if (fillColor(now + 1))
                return true ;
        }
    }
    return false ;
}

int main ()
{
    if (fillColor(1))
    {
        printf("YES\n") ;
        Show() ;
    }
    else
        printf ("NO") ;
}

/*
i     = :   1   2   3   4   5   6   7
color = :  紫  黄  红  黄  绿  红  紫
*/
