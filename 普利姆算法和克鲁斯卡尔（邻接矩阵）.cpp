利用普利姆算法和克鲁斯卡尔算法实现最小生成树问题。
[基本要求]
（1）自行建立图的数据文件，第一行是顶点个数，然后依次是顶点名，接下来是边，用float表示边的权值；
（2）以邻接矩阵表示图；
（3）分别利用prim和Kruskal算法实现最小生成树；
（4）输出最小生成树的权值之和，及所用的边。


#include <stdio.h>
#include <algorithm>
using namespace std ;

const float INF = 9999999 ;
float edge[20][20] ;
int n , m ;
int id[20] ;
int name[20] ;
int a , b ;
float c ;

float lowcost[20];
int nearvex[20];

void Prim(int s)
{
    float ans = 0 ;
    for (int i = 1 ; i <= n ; ++i)
    {
        lowcost[i] = edge[s][i] ;
        nearvex[i] = s ;
    }
    nearvex[s] = -1 ;
    for (int i = 1 ; i < n ; ++i)
    {
        float minx = INF ;
        int v = -1 ;
        for(int j = 1;j<=n;j++)
        {
            if(nearvex[j]!=-1&&lowcost[j]<minx)
            {
                v=j;
                minx=lowcost[j];
            }
        }
        if(v!=-1)//表示没找到权值最小的边
        {
            printf("%d %d %f\n" , name[nearvex[v]] , name[v] , lowcost[v]);   //依次输出选择的边 边的顶点和权值
            nearvex[v] = -1 ;
            ans += lowcost[v] ;
            for(int j = 1 ; j <= n ; j++)
            {
                if(nearvex[j] != -1 && edge[v][j] < lowcost[j])
                {
                    lowcost[j] = edge[v][j] ;
                    nearvex[j] = v ;
                }
            }
        }
    }
    printf("ans %f\n" , ans);
}

int father[20] ;

int fa(int x)
{
    if(x!=father[x])
        father[x]=fa(father[x]);
    return father[x];
}

void Kruscal()
{
    for (int i = 1 ; i <= n ; ++i)
    {
        father[i] = i ;
    }
    float ans = 0 ;
    for (int i = 1 ; i < n ; ++i)
    {
        float minx = INF ;
        int mina ;
        int minb ;
        for (int i = 1 ; i <= n ; ++i)
        {
            for (int j = 1 ; j < i ; ++j)
            {
                if (fa(i) != fa(j) && edge[i][j] < minx)
                {
                    minx = edge[i][j] ;
                    mina = i ;
                    minb = j ;
                }
            }
        }
        int p = fa(mina) ;
        int q = fa(minb) ;
        father[p] = q ;
        printf("%d %d %f\n" , name[mina] , name[minb] , minx) ;   //依次输出选择的边 边的顶点和权值
        ans += minx ;
    }
    printf("ans %f\n" , ans);
}


int main ()
{
    printf ("输入点的个数为:") ;

    scanf ("%d" , &n) ;
    for (int i = 1 ; i <= n ; ++i)
    {
        scanf ("%d" , &name[i]) ;
        id[name[i]] = i ;
    }
    for (int i = 1 ; i <= n ; ++i)
    {
        for (int j = 1 ; j < i ; ++j)
        {
            edge[i][j] = edge[j][i] = INF ;
        }
    }
    printf ("输入边的个数为:") ;
    scanf ("%d" , &m) ;
    for (int i = 1 ; i <= m ; ++i)
    {
        scanf ("%d%d%f" , &a , &b , &c) ;
        int ida = id[a] ;
        int idb = id[b] ;
        edge[ida][idb] = edge[idb][ida] = c ;
    }
    printf ("开始Prim算法:\n") ;
    Prim(1) ;
    printf ("开始Kruscal算法:\n") ;
    Kruscal() ;
}


/*

6
1 2 3 4 5 6
10
1 3 1
1 4 5
1 2 6
2 3 5
3 4 5
2 5 3
3 5 6
3 6 4
4 6 2
5 6 6


*/
