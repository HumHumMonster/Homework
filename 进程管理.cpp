#include <windows.h>
#include <conio.h>
#include <list>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <queue>
using namespace std ;

int time = 1 ;//时间

vector <int> V ;    //运行历史记录

//进程控制块
struct PCB
{
    int PID ;                   //进程标识符PID
    int state ;                 //进程状态（0等待态、1就绪态、2运行态、3阻塞态)
    int arrival_time ;          //到达时间
    int run_time ;              //运行时间
    bool need_printer ;         //是否需要打印机
    int sjp ;                   //分配的时间片
    int yxj ;                   //优先级
    PCB(int pid , int at , int rt , bool np)
    {
        PID = pid ;
        state = 0 ;
        arrival_time = at ;
        run_time = rt ;
        need_printer = np ;
        sjp = 0 ;
    }
    PCB (){}
};

PCB Running ;             //运行指针
list <PCB> Hready ;       //高优先级就绪队列
list <PCB> Mready ;       //中优先级就绪队列
list <PCB> Lready ;       //低优先级就绪队列
list <PCB> Wait ;         //等待队列
list <PCB> :: iterator it , p ;  //迭代器

//信号量

int printer = 1 ;     //打印机

void wait(int &p)
{
    //如果资源不够，就一直循环等待
    while (p <= 0) ;
    --p ;
}

void signal (int p)
{
    ++p ;
}

//撤销PID进程
bool backout (int pid)
{
    if (Running.PID == pid)
    {
        Running.PID = -1 ;
        return true ;
    }
    for (it = Wait.begin() ; it != Wait.end() ; ++it)
    {
        if ((*it).PID == pid)
        {
            Wait.erase(it) ;
            return true ;
        }
    }
    for (it = Hready.begin() ; it != Hready.end() ; ++it)
    {
        if ((*it).PID == pid)
        {
            Hready.erase(it) ;
            return true ;
        }
    }
    for (it = Mready.begin() ; it != Mready.end() ; ++it)
    {
        if ((*it).PID == pid)
        {
            Mready.erase(it) ;
            return true ;
        }
    }
    for (it = Lready.begin() ; it != Lready.end() ; ++it)
    {
        if ((*it).PID == pid)
        {
            Lready.erase(it) ;
            return true ;
        }
    }
    return false ;
}

//插入
void Insert (PCB p)
{
    //插入到等待队列
    Wait.push_back(p) ;
    return ;
}

//把Wait中到达的进程调入就绪
void Wait_to_Ready()
{
    for (it = Wait.begin() ; it != Wait.end() ; )
    {
        if ((*it).arrival_time <= time)
        {
            p = it ;
            printf ("进程 %d 就绪    到达时间 = %d   当前时间 = %d\n" , (*p).PID , (*p).arrival_time , time) ;
            (*p).yxj = 1 ;
            (*p).state = 1 ;            //进入就绪状态
            Hready.push_back(*p) ;
            ++it ;
            Wait.erase(p) ;
        }
        else
        {
            ++it ;
        }
    }
}

//多级反馈队列调度算法

//选择运行的程序
//高优先级分配1个时间片
//中优先级分配2个时间片
//低优先级分配4个时间片

void choose_running()
{
    //当前无运行程序
    if (Running.PID == -1)
    {
        if (!Hready.empty())
        {
            Running = Hready.front() ;      //运行进程改为高优先级的队头
            Hready.pop_front() ;            //删除队头
            Running.sjp = 1 ;               //分配一个时间片
        }
        else if (!Mready.empty())
        {
            Running = Mready.front() ;      //运行进程改为高优先级的队头
            Mready.pop_front() ;            //删除队头
            Running.sjp = 2 ;               //分配两个时间片
        }
        else if (!Lready.empty())
        {
            Running = Lready.front() ;      //运行进程改为高优先级的队头
            Lready.pop_front() ;            //删除队头
            Running.sjp = 4 ;               //分配四个时间片
        }
    }
    else
    {
        if (Running.yxj == 2)
        {
            if (!Hready.empty())
            {
                Running.sjp = 0 ;                   //之前运行的进程时间片归零

                Mready.push_back(Running) ;         //放回中优先级
                Running = Hready.front() ;          //运行进程改为高优先级的队头
                Hready.pop_front() ;                //删除队头
                Running.sjp = 1 ;                   //分配一个时间片
            }
        }
        if (Running.yxj == 3)
        {
            if (!Hready.empty())
            {
                Running.sjp = 0 ;                   //之前运行的进程时间片归零
                Lready.push_back(Running) ;         //放回中优先级
                Running = Hready.front() ;          //运行进程改为高优先级的队头
                Hready.pop_front() ;                //删除队头
                Running.sjp = 1 ;                   //分配一个时间片
            }
            else if (!Mready.empty())
            {
                Running.sjp = 0 ;                   //之前运行的进程时间片归零
                Lready.push_back(Running) ;         //放回中优先级
                Running = Mready.front() ;          //运行进程改为中优先级的队头
                Mready.pop_front() ;                //删除队头
                Running.sjp = 2 ;                   //分配两个时间片
            }
        }
    }
    Running.state = 2 ;         //进入运行态
}

void Run()
{
    V.push_back(Running.PID) ;
    if (Running.PID == -1)
    {
        printf ("当前无进程可执行!\n") ;
        return ;
    }
    printf ("当前进程 %d 运行   运行前剩余运行时间为%d   运行后剩余时间为%d\n" , Running.PID , Running.run_time , Running.run_time - 1) ;
    if (Running.need_printer)
        wait(printer) ;
    --Running.run_time ;
    --Running.sjp ;
    if (Running.need_printer)
        signal(printer) ;
    if (Running.run_time == 0)
    {
        printf("进程 %d 运行结束\n" , Running.PID) ;
        Running.PID = -1 ;
    }
    else if (Running.sjp == 0)
    {
        if (Running.yxj == 1)
        {
            Running.yxj = 2 ;
            Mready.push_back(Running) ;
        }
        else
        {
            Running.yxj = 3 ;
            Lready.push_back(Running) ;
        }
        Running.PID = -1 ;
    }

}

char op[2] ;
int main()
{
    Running.PID = -1 ;
    printf ("按任意键开始运行\n") ;
    getchar() ;
    while (1)
    {
        printf ("\n现在是第%d秒\n" , time) ;
        Sleep(500) ;
        if (_kbhit())
        {
            getch() ;
            while (1)
            {
                printf ("\n请输入操作符：A、添加进程 D、撤销进程 S、展示运行历史   其他、跳过\n") ;
                scanf ("%s" , &op) ;
                if (op[0] == 'A')
                {
                    printf ("请输入添加进程的信息\n") ;
                    printf ("进程的PID : ") ;
                    int pid ;
                    scanf ("%d" , &pid) ;
                    printf ("进程的到达时间 : ") ;
                    int at ;
                    scanf ("%d" , &at) ;
                    printf ("进程的运行时间 : ") ;
                    int rt ;
                    scanf ("%d" , &rt) ;
                    printf ("进程是否需要打印机（Y或N） : ") ;
                    char str[2] ;
                    bool np ;
                    scanf ("%s" , str) ;
                    if (str[0] == 'Y')
                        np = true ;
                    else
                        np = false ;
                    Insert(PCB(pid , at , rt , np)) ;
                }
                else if (op[0] == 'D')
                {
                    printf ("请输入撤销进程的PID\n") ;
                    printf ("进程的PID : ") ;
                    int pid ;
                    scanf ("%d" , &pid) ;
                    if (backout(pid))
                        printf ("撤销成功！\n") ;
                    else
                        printf ("需要撤销的进程不存在！\n") ;
                }
                else if (op[0] == 'S')
                {
                    for (int i = 0 ; i < V.size() ; ++i)
                    {
                        if (V[i] == -1)
                            printf("第 %d 秒 : 无进程\n" , i + 1) ;
                        else
                            printf("第 %d 秒 : 进程 %d\n" , i + 1 , V[i]) ;
                    }
                }
                else
                {
                    break ;
                }
            }
        }
        //把Wait中到达的进程调入就绪
        Wait_to_Ready() ;
        //选择运行的程序
        choose_running() ;
        //运行一个时间片
        Run() ;
        ++time ;
    }
}

/*
A
1
1
4
Y

A
2
2
4
Y

A
3
3
2
Y

A
4
3
5
Y

A
5
4
6
Y

*/
