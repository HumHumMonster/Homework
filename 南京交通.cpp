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
int dist[5200]; // �����㵽i�����̾���
int vis[5200]; // ����Ƿ���ʹ�
int p[5200]; // ���·��

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
    printf("����վ�����󣬻���վ��վֱ���޷�����\n") ;
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
    printf("����վ�����󣬻���վ��վֱ���޷�����\n") ;
}

int st , ar ;

void Least_stand()
{
    dijkstra(st , ar) ;

    printf("����Ҫ%dվ\n" , dist[ar]) ;
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
        cout << "��   " ;
        cout << id[last] ;
        printf ("   ��%d·��  " , road_num[next][last]) ;
        cout << id[next] << endl ;
        last = next ;
    }
}

void Minimum_transfer()
{
    BFS(st , ar) ;
    printf("\n���ٻ���Ϊ\n") ;
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
        cout << "��   " ;
        cout << id[last] ;
        printf ("   ��%d·��  " , road_num[next][last]) ;
        cout << id[next] << endl ;
        last = next ;
    }

}

int main ()
{
    for (int i = 0 ; i < 5200 ; ++i)
        for (int j = 0 ; j < 5200 ; ++j)
            len[i][j] = INF ;
    FILE *fp = fopen("�Ͼ�������·.txt" , "rt") ;
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
        printf("��������ʼ������վ:") ;
        cin >> sta ;
        printf("�����뵽�﹫����վ:") ;
        cin >> arr ;
        st = M[sta] ;
        ar = M[arr] ;
        printf("��ѡ��·��:\n1����������վ\n2�����ٴλ���\n") ;
        int op ;
        cin >> op ;
        if (op == 1)
            Least_stand() ;
        else
            Minimum_transfer() ;
        printf ("\n") ;
    }

}
