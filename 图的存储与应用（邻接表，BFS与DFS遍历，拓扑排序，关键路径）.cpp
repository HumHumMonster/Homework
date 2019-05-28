#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std ;
#define INF 0x3f3f3f3f

//弧节点
struct ArcNode
{
    int  adjvex ;
    ArcNode *nextarc ;
    int info ;
    ArcNode(int adj , int w)
    {
        adjvex = adj ;
        info = w ;
        nextarc = NULL ;
    }
    void output()
    {
        printf (" -> (adj = %d , w = %d)" , adjvex , info) ;
    }
};


//顶点节点
struct VexNode
{
    char data ;
    ArcNode *firstarc ;
    VexNode()
    {
        firstarc = NULL ;
    }
    //析构函数释放链表
    ~VexNode()
    {
        ArcNode *cp = firstarc ;
        ArcNode *np ;
        while (cp != NULL)
        {
            np = cp -> nextarc ;
            delete cp ;
            cp = np ;
        }
        firstarc = NULL ;
    }

    void output()
    {
        printf ("顶点%c" , data) ;
        ArcNode *p = firstarc ;
        while (p)
        {
            p -> output() ;
            p = p -> nextarc ;
        }
        printf ("\n") ;
    }

    void addArc(int adj , int w)
    {
        ArcNode *p = new ArcNode(adj , w) ;
        p -> nextarc = firstarc ;
        firstarc = p ;
    }
};

struct ALGraph
{
    VexNode *vertices ;
    int vexnum ;    //顶点数量
    int kind ;      //图的种类，0-无限图，1-有向图
    //传入字符串，根据其中字符为每个节点命名
    ALGraph(char *names , int k = 1)
    {
        kind = k ;
        vexnum = strlen(names) ;
        vertices = new VexNode [vexnum] ;
        for (int i = 0 ; i < vexnum ; ++i)
            vertices[i].data = names[i] ;
    }
    ~ALGraph()
    {
        delete vertices ;      //delete数组的方法
        vexnum = 0 ;
    }
    void output()
    {
        for (int i = 0 ; i < vexnum ; ++i)
            vertices[i].output() ;
    }

    void addArc(int tail , int head , int w = 0)
    {
        vertices[tail].addArc(head , w) ;
        if (kind == 0)  //如果是无向图
            vertices[head].addArc(tail , w) ;
    }
};
#define MAX_VERTEX_NUM 8
bool visited[MAX_VERTEX_NUM] ;
void visit(ALGraph &G , int v)
{
    visited[v] = true ;
    printf ("v%c ->" , G.vertices[v].data) ;
}

void DFS(ALGraph &G , int v)
{
    visit(G , v) ;
    for (ArcNode* i = G.vertices[v].firstarc ; i != NULL ; i = i -> nextarc)
    {
        int now = i -> adjvex ;
        if (visited[now])
            continue ;
        DFS(G , now) ;
    }
}

void DFSTraverse(ALGraph &G)
{
    memset(visited , false , sizeof (visited)) ;
    DFS(G , 0) ;
    printf ("\n") ;
}

void BFSTraverse(ALGraph &G)
{
    memset (visited , false , sizeof (visited)) ;
    queue <int> Q ;
    Q.push(0) ;
    visited[0] = true ;
    int v ;
    while (!Q.empty())
    {
        v = Q.front() ;
        Q.pop() ;
        visit(G , v) ;
        for (ArcNode* i = G.vertices[v].firstarc ; i != NULL ; i = i -> nextarc)
        {
            int now = i -> adjvex ;
            if (visited[now])
                continue ;
            Q.push(now) ;
            visited[now] = true ;
        }
    }
}

void findInDegree(ALGraph &G , int *in)
{
    memset (in , 0 , sizeof (in)) ;
    for (int v = 0 ; v < G.vexnum ; ++v)
    {
        for (ArcNode* i = G.vertices[v].firstarc ; i != NULL ; i = i -> nextarc)
        {
            int now = i -> adjvex ;
            ++in[now] ;
        }
    }
}

int in[MAX_VERTEX_NUM] ;

void topSort(ALGraph &G)
{
    findInDegree(G , in) ;
    int v , cnt = 0 ;
    queue <int> Q ;
    for (int i = 0 ; i < G.vexnum ; ++i)
        if (in[i] == 0)
            Q.push(i) ;
    while (!Q.empty())
    {
        ++cnt ;
        v = Q.front() ;
        Q.pop() ;
        visit(G , v) ;
        for (ArcNode* i = G.vertices[v].firstarc ; i != NULL ; i = i -> nextarc)
        {
            int now = i -> adjvex ;
            --in[now] ;
            if (in[now] == 0)
                Q.push(now) ;
        }
    }
    if (cnt != G.vexnum)
        printf ("该图有回路") ;
    printf ("\n") ;
}

//拓扑排序同时更新每个顶点的最早开始时间
int vl[MAX_VERTEX_NUM] ;//事件最晚开始
int ve[MAX_VERTEX_NUM] ;//事件最早开始
void topSort(ALGraph &G , stack<int> &T)
{
    memset (vl , 0 , sizeof (ve)) ;
    findInDegree(G , in) ;
    int v , cnt = 0 ;
    queue <int> Q ;
    for (int i = 0 ; i < G.vexnum ; ++i)
        if (in[i] == 0)
            Q.push(i) ;
    while (!Q.empty())
    {
        ++cnt ;
        v = Q.front() ;
        Q.pop() ;
        T.push(v) ;
        visit(G , v) ;
        for (ArcNode* i = G.vertices[v].firstarc ; i != NULL ; i = i -> nextarc)
        {
            int now = i -> adjvex ;
            if (ve[v] + i ->info > ve[now])
                ve[now] = ve[v] + i ->info ;
            --in[now] ;
            if (in[now] == 0)
                Q.push(now) ;
        }
    }
    if (cnt != G.vexnum)
        printf ("该图有回路") ;
    printf ("\n") ;
}

void cirticalPath(ALGraph &G)
{
    stack <int> T ;
    topSort(G , T) ;
    memset (vl , INF , sizeof (vl)) ;
    vl[T.top()] = ve[T.top()] ;
    T.pop() ;
    while (!T.empty())
    {
        int v = T.top() ;
        T.pop() ;
        for (ArcNode* i = G.vertices[v].firstarc ; i != NULL ; i = i -> nextarc)
        {
            int now = i -> adjvex ;
            vl[v] = vl[v] > vl[now] - (i -> info) ? vl[now] - (i -> info) : vl[v] ;
        }
    }
    for (int v = 0 ; v < G.vexnum ; ++v)
    {
        for (ArcNode* i = G.vertices[v].firstarc ; i != NULL ; i = i -> nextarc)
        {
            int now = i -> adjvex ;
            printf ("<%c , %c> = %d %d %d" , G.vertices[v].data , G.vertices[now].data , i ->info , ve[v] , vl[now] - (i ->info)) ;
            if (ve[v] == vl[now] - (i ->info))
                printf (" *") ;
            printf ("\n") ;
        }
    }
}

//测试图的邻接表封装
void test1()
{
    ALGraph g("ABCD") ;
    g.addArc(0 , 2) ;
    g.addArc(0 , 1) ;
    g.addArc(2 , 3) ;
    g.addArc(3 , 0) ;
    g.output() ;
}


//图的遍历
void test2()
{
    ALGraph G("12345678" , 0) ;
    G.addArc(0 , 2) ;
    G.addArc(0 , 1) ;
    G.addArc(1 , 4) ;
    G.addArc(1 , 3) ;
    G.addArc(2 , 6) ;
    G.addArc(2 , 5) ;
    G.addArc(3 , 7) ;
    G.addArc(4 , 7) ;
    DFSTraverse(G) ;
    BFSTraverse(G) ;
}
//拓扑排序
void test3()
{
    ALGraph G("123456789" , 1) ;
    G.addArc(0 , 1) ;
    G.addArc(0 , 2) ;
    G.addArc(0 , 3) ;
    G.addArc(1 , 4) ;
    G.addArc(2 , 4) ;
    G.addArc(3 , 5) ;
    G.addArc(4 , 6) ;
    G.addArc(4 , 7) ;
    G.addArc(5 , 7) ;
    G.addArc(6 , 8) ;
    G.addArc(7 , 8) ;
    try
    {
        topSort(G) ;
        G.addArc(6 , 1) ;
        topSort(G) ;
    }
    catch (char *exception)
    {
        printf ("%s\n" , exception) ;
    }
}

void test4()
{
    ALGraph G("123456" , 1) ;
    G.addArc(0 , 1 , 3) ;
    G.addArc(0 , 2 , 2) ;
    G.addArc(1 , 3 , 2) ;
    G.addArc(1 , 4 , 3) ;
    G.addArc(2 , 3 , 4) ;
    G.addArc(2 , 5 , 3) ;
    G.addArc(3 , 5 , 2) ;
    G.addArc(4 , 5 , 1) ;
    cirticalPath(G) ;
    return ;
}

int main ()
{
    //test1() ;
    //test2() ;
    //test3() ;
    test4() ;
}
