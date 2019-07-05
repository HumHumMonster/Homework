/*
大二小学期写的一个数据结构作业，词频统计
给100w个单词放入字典树

*/


#include <stdio.h>
#include <string.h>

const int MAXN = 28 ;   //26个字母加上-和’

FILE* fpr ;     //读入文件指针
FILE* fpw ;     //输出文件指针

int word_cnt = 0 ;      //总共的单词数量

struct Node     //字典树节点
{
    int deep ;              //深度
    char ch ;               //字符
    Node* next[MAXN] ;      //后继节点
    bool is_word ;          //是否是一个单词的结尾
    int cnt ;               //如果是单词的结尾，统计单词的数量
};

Node* root ;    //字典树的根节点

Node* New_node(char ch , int deep)      //申请一个新的字典树节点，字符为ch，深度为deep
{
    Node* p = new Node() ;
    p -> is_word = false ;              //不为单词结尾
    p -> cnt = 0 ;                      //单词数量为0
    for (int i = 0 ; i < MAXN ; ++i)
        p -> next[i] = NULL ;           //后继节点都是空
    p -> ch = ch ;                      //节点字符
    p -> deep = deep ;                  //节点深度
    return p ;
}

void Insert(Node* p , char str[] , int l , int r)       //插入一个单词，从p节点后面 继续插入 字符串str的l到r - 1
{
    for (int i = l ; i < r ; ++i)
    {
        //把字符转化为0到27的整数
        int id = str[i] - 'a' ;
        if (str[i] == '-')
            id = 26 ;
        if (str[i] == '\'')
            id = 27 ;

        p -> next[id] = New_node(str[i] , p -> deep + 1) ;      //申请一个新节点，字符为str[i] , 深度为deep + 1
        p = p -> next[id] ;         //跳到后继节点，继续准备插入
    }
    p -> is_word = true ;           //标记为一个单词
    p -> cnt = 1 ;                  //单词个数为 1
    return ;
}

void Solve(char str[] , int l , int r)              //处理字符串str
{
    Node* p = root ;                //从根节点开始向下查找
    for (int i = l ; i < r ; ++i)
    {
        //把字符转化为0到27的整数
        if (str[i] <= 'Z' && str[i] >= 'A')
            str[i] += 32 ;
        int id = str[i] - 'a' ;
        if (str[i] == '-')
            id = 26 ;
        if (str[i] == '\'')
            id = 27 ;

        //如果下一个对应的节点为空，则说明现在查找的单词不在树中
        if (p -> next[id] == NULL)
        {
            Insert(p , str , i , r) ;       //插入该单词
            return ;                        //插入后返回
        }
        p = p -> next[id] ;
    }
    //查找到该单词
    ++(p -> cnt) ;                  //单词数加一
    if (!(p -> is_word))            //如果该还不是单词，则设置为单词
        p -> is_word = true ;

}

char word[100] ;                    //存放要输出的单词

void DFS(Node* p)                   //从根节点开始向下DFS
{
    word[p -> deep] = p -> ch ;     //要输出的字符串数组的deep位置赋为当前节点的字符
    if (p -> is_word)               //如果当前节点是一个单词的结尾，就输出该单词，并输出次数
    {
        for (int i = 1 ; i <= p -> deep ; ++i)
        {
            fprintf (fpw , "%c" , word[i]) ;
        }
        fprintf (fpw , "   次数为%d\n" , p -> cnt) ;
        word_cnt += p -> cnt ;
    }
    //向26个子节点再深度优先搜索
    for (int i = 0 ; i < MAXN ; ++i)
    {
        if (p -> next[i] != NULL)
        {
            DFS(p -> next[i]) ;
        }
    }
    return ;
}

void Show()             //展示函数
{
    DFS(root) ;
}

char str[100] ;

int main ()
{
    //给文件指针赋值
    fpr = fopen("C:\\Users\\14714\\Desktop\\homework\\Harry Potter and the Sorcerer's Stone.txt" , "r") ;
    fpw = fopen("C:\\Users\\14714\\Desktop\\homework\\out.txt" , "w") ;
    //给根节点赋值，根节点深度为0
    root = New_node('@' , 0) ;
    while (fscanf (fpr , "%s" , str) != EOF)        //读入一个小段
    {
        int l , r = -1 ;
        int len = strlen(str) ;
        //把小段分割出单词，分别处理
        while (1)
        {
            //l代表从上一次的r之后第一个为字母的位置
            for (l = r + 1 ; l < len ; ++l)
            {
                if ((str[l] <= 'z' && str[l] >= 'a') || (str[l] <= 'Z' && str[l] >= 'A'))
                    break ;
            }
            if (l == len)
                break ;
            //r代表从这一次l之后第一个不属于单词该有的字符的位置
            for (r = l + 1 ; r < len ; ++r)
            {
                if (!((str[r] <= 'z' && str[r] >= 'a') || (str[r] <= 'Z' && str[r] >= 'A') || str[r] == '-' || str[r] == '\''))
                    break ;
            }
            Solve(str , l , r) ;
            if (r == len)
                break ;
        }
    }
    Show() ;
    fprintf (fpr , "总单词数为 ：%d\n" , word_cnt) ;
    printf ("%d" , word_cnt) ;
}
