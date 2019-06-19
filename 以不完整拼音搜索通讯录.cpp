#include <stdio.h>
#include <string.h>

const int MAXN = 26 ;


struct Trie
{
    int cnt ;           //经过该点的联系人个数
    int fa ;            //该点的父节点
    char ch ;           //该点的字符
    bool is_end ;       //该节点是否是一个联系人的末尾
    int next[MAXN] ;    //儿子节点们！
}trie[100000];

int tot = 0 ;       //目前有多少节点

int newTrie(int x , char c)     //新节点的建立
{
    trie[tot].fa = x ;
    trie[tot].cnt = 0 ;
    trie[tot].ch = c ;
    trie[tot].is_end = false ;
    for (int i = 0 ; i < 26 ; ++i)
        trie[tot].next[i] = -1 ;
    ++tot ;
    return tot - 1 ;
}

int root ;

void print(int x)   //输出该节点
{
    if (trie[x].fa != 0)
        print(trie[x].fa) ;
    printf ("%c" , trie[x].ch) ;
}

void Show(int x)    //输出该联系人
{
    if (x == -1)
        return ;
    if (trie[x].is_end == true)      //是个联系人
    {
        print(x) ;
        printf ("\n") ;
    }
    for (int i = 0 ; i < MAXN ; ++i)    //把之后的也输出
    {
        Show(trie[x].next[i]) ;
    }
}

void Insert(char* str)
{
    int len = strlen(str) ;
    int p = root ;
    for (int i = 0 ; i < len ; ++i)
    {
        int id = str[i] - 'a' ;
        if (trie[p].next[id] == -1)
            trie[p].next[id] = newTrie(p , str[i]) ;
        p = trie[p].next[id] ;
        ++trie[p].cnt ;
    }
    trie[p].is_end = true ;
}


void Search(char *str)
{
    int len = strlen(str) ;
    int p = root ;
    for (int i = 0 ; i < len ; ++i)
    {
        int id = str[i] - 'a' ;
        if (trie[p].next[id] == -1)
        {
            printf ("找到0个联系人\n") ;
            return ;
        }
        p = trie[p].next[id] ;
    }
    printf ("找到%d个联系人\n" , trie[p].cnt) ;
    Show(p) ;
}

int op ;
char str[10000] ;

int main ()
{
    root = newTrie(0 , '?') ;
    while (1)
    {
        //1为插入，2为查找
        printf ("请输入操作方式：") ;
        scanf ("%d" , &op) ;
        if (op == 1)
        {
            printf ("请输入插入的联系人姓名：") ;
            scanf ("%s" , str) ;
            Insert(str) ;
            printf ("插入成功！联系人列表如下\n") ;
            for (int i = 0 ; i < tot ; ++i)
            {
                if (trie[i].is_end == false)
                    continue ;
                print(i) ;
                printf ("\n") ;
            }
        }
        else if (op == 2)
        {
            printf ("请输入查找的联系人姓名：") ;
            scanf ("%s" , str) ;
            Search(str) ;
        }
        printf ("\n\n") ;
    }
}
