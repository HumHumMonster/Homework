#include <stdio.h>
#include <algorithm>
using namespace std ;

#define LL long long

const LL mod = 99997867 ;

const int MAXN = 1000000 + 10 ;
LL n , d ;
LL num[MAXN] ;

LL res ;
LL u ;
int main ()
{
    FILE *fw ;
    FILE *fr ;
    fw = fopen("C:\\Users\\14714\\Desktop\\省赛题目\\数据\\中秋月饼\\12.out" , "w") ;
    fr = fopen("C:\\Users\\14714\\Desktop\\省赛题目\\数据\\中秋月饼\\12.in" , "r") ;
    fscanf (fr , "%lld%lld" , &n , &d) ;
    for (LL i = 1 ; i <= n ; ++i)
    {
        fscanf (fr , "%lld" , &num[i]) ;
    }
    sort (num + 1 , num + 1 + n) ;
    for (LL i = 1 ; i <= n ; ++i)
    {
        LL now = num[i] + d ;
        LL id = upper_bound(num + i + 1 , num + 1 + n , now) - num ;
        --id ;
        //printf ("i = %lld  num = %lld  id = %lld\n" , i , num[i] , id) ;
        id = id - i ;
        if (id >= 2)
        {
            res += id * (id - 1) / 2 ;
            res %= mod ;
        }

    }
    fprintf (fw , "%lld" , res) ;
}
