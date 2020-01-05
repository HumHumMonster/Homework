#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include <string.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
using namespace std ;
const int INF = 0x3f3f3f3f ;
int a , b ;
char ch[5200] ;
int len[5200][5200] ;
int road_num[5200][5200] ;
string str , road ;
int road_now ;
int cnt = 1 ;
map <string , int> M ;
string id[52000] ;
string sta , arr ;
struct Edge{
    int u, v, w;
    Edge(int u, int v, int w):u(u),v(v),w(w) {}
};

struct Node {
    int d , u;
    Node(int d , int u):d(d),u(u) {}
    friend bool operator < (Node a, Node b) {
        return a.d > b.d;
    }
};

vector<Edge> edges;
vector<int> G[5200];
int dist[5200]; // 存放起点到i点的最短距离
int vis[5200]; // 标记是否访问过
int p[5200]; // 存放路径

void spilt(string s,char ch)
{
    s.push_back(ch);
    int start = 0 , end = 0 , size = s.size();
    vector<string> vs;

    for(int i = 0 ; i < size;i++)
    {
        if(s[i]==ch)
        {
            end = i;
            string temp = s.substr(start,end-start);
            start = i+1;
            vs.push_back(temp);
        }
    }
    for (int i = 0 ; i < vs.size() ; ++i)
    {
        if (M[vs[i]] == 0)
        {
            M[vs[i]] = cnt ;
            id[cnt] = vs[i] ;
            ++cnt ;
        }
        a = M[vs[i]] ;
        for (int j = 0 ; j < i ; ++j)
        {
            b = M[vs[j]] ;
            if (len[a][b] > i - j)
            {
                len[a][b] = len[b][a] = i - j ;
                road_num[a][b] = road_num[b][a] = road_now ;
//                cout << vs[i] << "   " << vs[j] ;
//                printf ("    %d\n" , len[a][b]) ;
            }
        }
    }
    return ;
}

void addedge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
    int sz = edges.size();
    G[u].push_back(sz - 1);
}

void init() {
    for(int i = 0 ; i <= cnt; i++) G[i].clear();
    edges.clear();
}

void dijkstra(int s , int e)
{
    priority_queue<Node> q;
    for (int i = 0; i <= cnt; i++)
        dist[i] = INF ;
    dist[s] = 0;
    memset(vis , 0 , sizeof(vis));
    q.push(Node(0, s));
    while (!q.empty()) {
        Node now = q.top(); q.pop();
        int u = now.u ;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 1 ; i <= cnt ; i++)
        {
            if (dist[i] > dist[u] + len[u][i]) {
                dist[i] = dist[u] + len[u][i] ;
                p[i] = u ;
                if (i == e)
                    return ;
                q.push(Node(dist[i], i));
            }
        }
    }
    printf("输入站名有误，或者站与站直接无法到达\n") ;
}

void BFS(int s , int e)
{
    queue <int> Q ;
    Q.push(s) ;
    memset(vis , 0 , sizeof(vis));
    vis[s] = 1 ;
    while (!Q.empty())
    {
        int now = Q.front() ;
        Q.pop() ;
        for (int i = 1 ; i < cnt ; ++i)
        {
            if (vis[i])
                continue ;
            if (len[now][i] != INF)
            {
                Q.push(i) ;
                p[i] = now ;
                vis[i] = 1 ;
                if (i == e)
                    return ;
            }
        }
    }
    printf("输入站名有误，或者站与站直接无法到达\n") ;
}

int st , ar ;

void Least_stand()
{
    dijkstra(st , ar) ;

    printf("最少要%d站\n" , dist[ar]) ;
    int now = ar ;
    stack <int> S ;
    while (now != st)
    {
        S.push(now) ;
        now = p[now] ;
    }
    int last = st , next ;
    while (!S.empty())
    {
        next = S.top() ;
        S.pop() ;
        cout << "从   " ;
        cout << id[last] ;
        printf ("   坐%d路到  " , road_num[next][last]) ;
        cout << id[next] << endl ;
        last = next ;
    }
}

void Minimum_transfer()
{
    BFS(st , ar) ;
    printf("\n最少换乘为\n") ;
    int now = ar ;
    stack <int> S ;
    while (now != st)
    {
        S.push(now) ;
        now = p[now] ;
    }
    int last = st , next ;
    while (!S.empty())
    {
        next = S.top() ;
        S.pop() ;
        cout << "从   " ;
        cout << id[last] ;
        printf ("   坐%d路到  " , road_num[next][last]) ;
        cout << id[next] << endl ;
        last = next ;
    }

}

int main ()
{
    for (int i = 0 ; i < 5200 ; ++i)
        for (int j = 0 ; j < 5200 ; ++j)
            len[i][j] = INF ;
    FILE *fp = fopen("南京公交线路.txt" , "rt") ;
    while (fscanf(fp , "%s" , ch) != EOF)
    {
        road = ch ;
        road = road.substr(0 , road.size() - 2) ;
        road_now = atoi( road.c_str() ) ;

        fscanf(fp , "%s" , ch) ;
        str = ch ;
        spilt(str , ',') ;
    }
    //printf("%d" , cnt) ;
    while (1)
    {
        printf("请输入起始公交车站:") ;
        cin >> sta ;
        printf("请输入到达公交车站:") ;
        cin >> arr ;
        st = M[sta] ;
        ar = M[arr] ;
        printf("请选择路径:\n1、经过最少站\n2、最少次换乘\n") ;
        int op ;
        cin >> op ;
        if (op == 1)
            Least_stand() ;
        else
            Minimum_transfer() ;
        printf ("\n") ;
    }

}
