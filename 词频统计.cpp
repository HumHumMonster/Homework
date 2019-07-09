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
            n
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

void Insert(Node* p , char str[] , int l , int r , int cnt)       //插入一个单词，从p节点后面 继续插入 字符串str的l到r - 1
{
    for (int i = l ; i < r ; ++i)
    {
        //把字符转化为0到27的整数
        int id = str[i] - 'a' ;
        if (str[i] == '-')
            id = 26 ;
        if (str[i] == '\'')
            id = 27 ;
        if (str[i] <= 'Z' && str[i] >= 'A')
            str[i] += 32 ;
        p -> next[id] = New_node(str[i] , p -> deep + 1) ;      //申请一个新节点，字符为str[i] , 深度为deep + 1
        p = p -> next[id] ;         //跳到后继节点，继续准备插入
    }
    p -> is_word = true ;           //标记为一个单词
    (p -> cnt) = cnt ;                  //单词个数为 1
    return ;
}


void Solve(char str[] , int l , int r , int cnt)              //处理字符串str
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
            Insert(p , str , i , r , cnt) ;       //插入该单词
            return ;                        //插入后返回
        }
        p = p -> next[id] ;
    }
    //查找到该单词
    (p -> cnt) += cnt ;                  //单词数加一
    if (!(p -> is_word))            //如果该还不是单词，则设置为单词
        p -> is_word = true ;

}

void Divide_word(char str[])
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
        Solve(str , l , r , 1) ;
        if (r == len)
            break ;
    }
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
        fprintf (fpw , "   次数为： %d\n" , p -> cnt) ;
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

void Search(char str[] , int l , int r)       //查找一个单词
{
    Node* p = root ;
    for (int i = l ; i < r ; ++i)
    {
        //把字符转化为0到27的整数
        int id = str[i] - 'a' ;
        if (str[i] <= 'Z' && str[i] >= 'A')
            id += 32 ;
        if (str[i] == '-')
            id = 26 ;
        if (str[i] == '\'')
            id = 27 ;
        //如果无查找的节点，说明没有这个单词，次数为0
        if (!(id >= 0 && id <= 27))
        {
            for (int j = l ; j < r ; ++j) printf ("%c" , str[j]) ;
            printf ("   次数为： 0\n") ;
            return ;
        }
        if (p -> next[id] == NULL)
        {
            for (int j = l ; j < r ; ++j) printf ("%c" , str[j]) ;
            printf ("   次数为： 0\n") ;
            return ;
        }
        p = p -> next[id] ;         //跳到后继节点，继续查找
    }
    for (int i = l ; i < r ; ++i) printf ("%c" , str[i]) ;
    printf ("   次数为： ") ;
    printf ("%d\n" , p -> cnt) ;
    return ;
}


char str[100] ;

char op[30] ;

char address[100] ;



int main ()
{
    root = New_node('@' , 0) ;
    while (1)
    {
        printf ("请输入操作符:\nQ.查询一个单词\nI.插入一个短文\nR.导入一个小说或者一份记录\nW.导出记录\n") ;
        scanf ("%s" , op) ;
        if (op[0] == 'Q')
        {
            printf ("请输入需要查找的单词：\n") ;
            scanf ("%s" , str) ;
            Search(str , 0 , strlen(str)) ;
        }
        else if (op[0] == 'I')
        {
            printf ("请输入需要插入的短文(以一个单独的@为结束)：\n") ;
            while(scanf ("%s" , str))
            {
                if (str[0] == '@')
                    break ;
                Divide_word(str) ;
            }
            printf ("插入完成！\n") ;
        }
        else if (op[0] == 'R')
        {
            printf ("请输入导入方式:\nN.导入一本小说\nR.导入一份记录\n") ;
            scanf ("%s" , op) ;
            printf ("请输入导入文件的位置:\n") ;
            getchar() ;
            gets(address) ;
            fpr = NULL ;
            fpr = fopen(address , "r") ;
            //C:\Users\14714\Desktop\homework\Harry Potter and the Sorcerer's Stone.txt
            //C:\Users\14714\Desktop\homework\out.txt
            if (fpr == NULL)
            {
                printf ("导入失败!文件地址有误！\n") ;
                continue ;
            }
            if (op[0] == 'N')
            {
                while (fscanf (fpr , "%s" , str) != EOF)
                    Divide_word(str) ;
                printf ("%s  导入成功！\n" , address) ;
            }
            else if (op[0] == 'R')
            {
                while (fscanf (fpr , "%s" , str) != EOF)
                {
                    fscanf (fpr , "%s" , op) ;
                    int cnt ;
                    fscanf (fpr , "%d" , &cnt) ;
                    //printf ("%s  %s  %d\n" , str , op , cnt) ;
                    Solve(str , 0 , strlen(str) , cnt) ;
                }
                printf ("%s  导入成功！\n" , address) ;
            }
            else
                printf ("操作符号有误!\n") ;
        }
        else if (op[0] == 'W')
        {
            printf ("请输入导出文件的位置:\n") ;
            getchar() ;
            gets(address) ;
            fpw = NULL ;
            fpw = fopen(address , "w") ;                //C:\Users\14714\Desktop\homework\out.txt
            if (fpw == NULL)
                printf ("导出失败!文件地址有误！\n") ;
            Show() ;
            printf ("导出成功！导出单词数量为%d\n" , word_cnt) ;
        }
        else
            printf ("操作符号有误!\n") ;
        printf ("\n") ;
    }
    Show() ;
    fprintf (fpr , "frequency of occurrence:%d\n" , word_cnt) ;
    printf ("%d\n" , word_cnt) ;
}
