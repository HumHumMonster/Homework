/*
计算器(栈的封装与应用).cpp

可以实现括号，括号套括号，幂运算。

*/

#include <iostream>
#include <cstdio>
using namespace std ;


template <typename ElemType>

struct Stack
{
    ElemType *items ;
    int capacity ;
    int top ;
    Stack(int c = 10)
    {
        top = 0 ;
        capacity = 10 ;
        items = new ElemType[capacity] ;
    }
    ~Stack()
    {

    }
    void output()
    {
        for (int i = 0 ; i < top ; ++i)
            cout << items[i] << " " ;
        cout << endl ;
    }
    void push(ElemType e)
    {
        items[top++] = e ;
    }
    ElemType peek()
    {
        return items[top - 1] ;
    }
    ElemType pop()
    {
        --top ;
        return items[top] ;
    }
};

/*
int main ()
{
    Stack <char> stack ;
    stack.push('A') ;
    stack.push('B') ;
    stack.push('C') ;
    stack.output() ;
    char t = stack.pop() ;
    cout << t << endl ;
    t = stack.peek() ;
    cout << t << endl ;
    stack.output() ;
    return 0 ;
}
*/

int getPriority(char opt)
{
    if (opt == '+')
        return 1 ;
    else if (opt == '-')
        return 1 ;
    else if (opt == '*')
        return 2 ;
    else if (opt == '/')
        return 2 ;
    else if (opt == '#')
        return 0 ;
    else if (opt == '^')
        return 3 ;
}

int compare(char optA , char optB)
{
    return getPriority(optA) - getPriority(optB) ;
}

double caculate(double v1 , double v2 , char opt) //v2在后，v1在前
{
    //求双目运算的值
    if (opt == '+')
        return v1 + v2 ;
    else if (opt == '-')
        return v1 - v2 ;
    else if (opt == '*')
        return v1 * v2 ;
    else if (opt == '/')
        return v1 / v2 ;
    else if (opt == '^')
    {
        double res = 1 ;
        int time = (int)v2 ;
        while (time--)
        {
            res *= v1 ;
        }
        return res ;
    }
}

int i = 0 ;

double evaluate(char *expression)
{
    Stack <double> values ;
    Stack <char> operators ;
    char ch ;
    int now_val = 0 ;
    while ((ch = expression[i]) != '\0')
    {
        printf ("i = %d  ch = %c \n" , i , ch) ;
        ++i ;
        if (ch == '(')
        {
            double yo = evaluate(expression) ;
            values.push(yo) ;
            continue ;
        }
        if (ch == ')')
        {
            values.push(now_val) ;
            if (operators.top > 0)
            {
                double a = values.pop() ;
                double b = values.pop() ;
                char op_now = operators.pop() ;
                values.push(caculate(b , a , op_now)) ;
            }
            return values.pop() ;
        }
        if (ch >= '0' && ch <= '9')
        {
            now_val *= 10 ;
            now_val += ch - '0' ;
        }
        else
        {
            if (expression[i - 2] != ')')
            {
                if (operators.peek() == '-' && operators.top - values.top == 1)
                    values.push(-now_val) ;
                else
                    values.push(now_val) ;
                now_val = 0 ;
            }
            while (operators.top > 0 && compare(ch , operators.peek()) <= 0)
            {
                double a = values.pop() ;
                double b = values.pop() ;
                char op_now = operators.pop() ;
                values.push(caculate(b , a , op_now)) ;
            }
            operators.push(ch) ;
        }

        values.output() ;
        operators.output() ;

    }
    return values.pop() ;
}

void init()
{
    i = 0 ;
}

int main ()
{
    /*
    cout << evaluate("3-4+5#") << endl ;
    cout << evaluate("4-4*2+5#") << endl ;
    cout << evaluate("5/4#") << endl ;
    cout << evaluate("6-4/5+2*6#") << endl ;
    cout << evaluate("77+20*75/15#") << endl ;
    cout << evaluate("321+893*234#") << endl ; //209283
    cout << evaluate("2^3+3^5#") << endl ;
    cout << evaluate("(1+2)+4*(1+2)#") << endl ;
    cout << evaluate("(1+2)*4-(1+2)#") << endl ;
    cout << evaluate("(((1+2)+3)+4)#") << endl ;
    cout << evaluate("(((1+2)+3)+4)+(((1+2)+3)+4)#") << endl ;
    */
    char str[10005] ;
    while (cin >> str)
    {
        init() ;
        cout << evaluate(str) << endl ;
    }
    return 0 ;
}
