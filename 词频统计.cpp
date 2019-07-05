#include <stdio.h>
#include <string.h>

const int MAXN = 28 ;

    FILE* fpr ;
    FILE* fpw ;

int word_cnt = 0 ;

struct Node
{
    int deep ;
    char ch ;
    Node* next[MAXN] ;
    int cnt ;
    bool is_word ;
};

Node* root ;

Node* New_node(char ch , int deep)
{
    Node* p = new Node() ;
    p -> is_word = false ;
    p -> cnt = 0 ;
    for (int i = 0 ; i < MAXN ; ++i)
        p -> next[i] = NULL ;
    p -> ch = ch ;
    p -> deep = deep ;
    return p ;
}

void Insert(Node* p , char str[] , int l , int r)
{
    for (int i = l ; i < r ; ++i)
    {
        int id = str[i] - 'a' ;
        if (str[i] == '-')
            id = 26 ;
        if (str[i] == '\'')
            id = 27 ;
        //printf ("Insert i = %d ch = %c  id = %d\n" , i , str[i] , id) ;
        p -> next[id] = New_node(str[i] , p -> deep + 1) ;
        p = p -> next[id] ;
    }
    p -> is_word = true ;
    p -> cnt = 1 ;
    return ;
}

void Search(char str[] , int l , int r)
{
    Node* p = root ;
    for (int i = l ; i < r ; ++i)
    {
        if (str[i] <= 'Z' && str[i] >= 'A')
            str[i] += 32 ;
        int id = str[i] - 'a' ;
        if (str[i] == '-')
            id = 26 ;
        if (str[i] == '\'')
            id = 27 ;
        //printf ("Search i = %d ch = %c  id = %d\n" , i , str[i] , id) ;
        if (p -> next[id] == NULL)
        {
            Insert(p , str , i , r) ;
            return ;
        }
        p = p -> next[id] ;
    }
    ++(p -> cnt) ;
    if (!(p -> is_word))
        p -> is_word = true ;

}

char word[100] ;

void DFS(Node* p)
{
    word[p -> deep] = p -> ch ;
    if (p -> is_word)
    {
        for (int i = 1 ; i <= p -> deep ; ++i)
        {
            fprintf (fpw , "%c" , word[i]) ;
        }
        fprintf (fpw , "   次数为%d\n" , p -> cnt) ;
        word_cnt += p -> cnt ;
    }
    for (int i = 0 ; i < MAXN ; ++i)
    {
        if (p -> next[i] != NULL)
        {
            DFS(p -> next[i]) ;
        }
    }
    return ;
}

void Show()
{
    DFS(root) ;
}

char str[100000000] ;

int main ()
{
    fpr = fopen("C:\\Users\\14714\\Desktop\\homework\\Harry Potter and the Sorcerer's Stone.txt" , "r") ;
    fpw = fopen("C:\\Users\\14714\\Desktop\\homework\\out.txt" , "w") ;
    root = New_node('@' , 0) ;
    while (fscanf (fpr , "%s" , str) != EOF)
    {
        //printf ("%s\n" , str) ;
//        if (str[0] == '@')
//            break ;
        int l , r = -1 ;
        int len = strlen(str) ;
        while (1)
        {
            for (l = r + 1 ; l < len ; ++l)
            {
                if ((str[l] <= 'z' && str[l] >= 'a') || (str[l] <= 'Z' && str[l] >= 'A'))
                    break ;
            }
            if (l == len)
                break ;
            for (r = l + 1 ; r < len ; ++r)
            {
                if (!((str[r] <= 'z' && str[r] >= 'a') || (str[r] <= 'Z' && str[r] >= 'A') || str[r] == '-' || str[r] == '\''))
                    break ;
            }
            //printf ("l = %d  r = %d\n" , l , r) ;
            Search(str , l , r) ;
            if (r == len)
                break ;
        }
    }
    Show() ;
    fprintf (fpr , "总单词数为 ：%d\n" , word_cnt) ;
    printf ("%d" , word_cnt) ;
}
