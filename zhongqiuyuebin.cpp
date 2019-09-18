#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <set>
using namespace std ;
#define LL long long
const int MAXN = 1e5 + 10 ;

set <LL> S ;
LL n , k ;
LL num[MAXN] ;


int main ()
{
    FILE *fw ;
    FILE *fr ;
    fw = fopen("C:\\Users\\14714\\Desktop\\省赛题目\\数据\\中秋月饼\\10.in" , "w") ;
    srand(time(NULL)) ;
    n = 100000 ;
    k = rand() * rand() ;
    k %= (100000 + 1) ;
    printf ("%lld %lld" , n , k) ;
    fprintf (fw , "%lld %lld\n" , n , k) ;
    for (int i = 1 ; i <= n ; ++i)
    {
        num[i] = rand() * rand() ;
        num[i] %= (1000000 + 1) ;
        if (S.count(num[i]))
        {
            --i ;
            continue ;
        }
        fprintf (fw , "%lld\n" , num[i]) ;
    }
}





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
