#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std ;

typedef int ElemType ;

struct LNode
{
    ElemType data ;     //保存的数值
    LNode *next ; //指向下一个节点的指针
    LNode(int x = 0)
    {
        data = x ;
        next = NULL ;
    }
};


//初始化单链表
void InitList(LNode* &HL)
{
    HL = NULL ;     //置单链表为空
}

//删除单链表所有元素
void ClearList(LNode* &HL)
{
    LNode *cp ;     //将cp指向待处理的节点
    LNode *np ;     //将用np指向co的后继节点
    cp = HL ;
    while (cp != NULL)  //遍历单链表
    {
        np = cp -> next ;   //保存下一个节点的地址
        delete cp ;         //删除当前节点。即被处理的节点
        cp = np ;           //使下一个节点成为当前节点
    }
    HL = NULL ;      //置单链表为空
}

//得到单链表的长度
int LenthList(LNode *HL)
{
    int i = 0 ;
    while (HL != NULL)
    {
        ++i ;
        HL = HL -> next ;
    }
    return i ;
}

//检查单链表是否为空
bool EmptyList(LNode *HL)
{
    return HL == NULL ;
}

//得到单链表中第pos个节点的元素
ElemType GetList(LNode *HL , int pos)
{
    if (pos < 1)    //pos有错,退出运行
    {
        cerr << "pos is out range!" << endl ;
        exit(1) ;
    }
    int i = 0 ;
    while (HL != NULL)
    {
        ++i ;
        if (i == pos)
            break ;
        HL = HL -> next ;
    }
    if (HL != NULL)
        return HL -> data ;
    else
    {
        cerr << "pos is out range!" << endl ;
        exit(1) ;
    }
}

//遍历一个单链表
void TraverseList(LNode *HL)
{
    while (HL != NULL)
    {
        cout << HL -> data << " " ;
        HL = HL -> next ;
    }
    cout << endl ;
}

//从单链表中查找出等于给定值的第一个元素
bool FindList(LNode *HL , ElemType &item)
{
    while (HL != NULL)
    {
        if (HL -> data == item)
        {
            item = HL -> data ;
            return true ;
        }
        else
            HL = HL -> next ;
    }
    return false ;
}

bool UpdateList(LNode *HL , const ElemType& item)
{
    while (HL != NULL)      //查找元素
    {
        if (HL -> data == item)
            break ;
        HL = HL -> next ;
    }
    if (HL == NULL)     //没有被更新的元素
        return false ;
    else        //更新元素
    {
        HL -> data = item ;
        return true ;
    }
}

//向单链表中按给定条件插入一个元素
bool InsertList (LNode* &HL , ElemType item , int pos)
{
    //pos值小于-1返回假
    if (pos < -1)
    {
        cout << "pos值无效!" << endl ;
        return false ;
    }
    //为item元素建立新节点
    LNode *newptr ;
    newptr = new LNode ;
    newptr -> data = item ;
    LNode *cp = HL ;
    LNode *ap = NULL ;
    if (pos == 0)   //按值寻找插入位置
    {
        while (cp != NULL)
        {
            if (item < cp -> data)      //找到新元素插入位置，退出循环
                break ;
            ap = cp ;
            cp = cp -> next ;
        }
    }
    else if (pos == -1)     //把cp插到最后一个节点
    {
        while (cp != NULL)
        {
            ap = cp ;
            cp = cp -> next ;
        }
    }
    else
    {
        int i = 0 ;
        while (cp != NULL)
        {
            ++i ;
            if (i == pos)
                break ;
            ap = cp ;
            cp = cp -> next ;
        }
        if (cp == NULL && i + 1 < pos)
        {
            cout << "pos值超出单链表长度加1!" << endl ;
            return false ;
        }
    }
    //完成新节点插入
    if (ap == NULL)
    {
        newptr -> next = HL ;
        HL = newptr ;
    }
    else
    {
        newptr -> next = cp ;
        ap -> next = newptr ;
    }
    return true ;
}

//删除节点
bool DeleteList(LNode* &HL , ElemType item , int pos)
{
    //单链表为空。无法删除
    if (HL == NULL)
    {
        cerr << "单链表为空。删除操作无效!" << endl ;
        return false ;
    }
    //pos值小于-1返回假
    if (pos < -1)
    {
        cout << "pos值无效！" << endl ;
        return false ;
    }
    //寻找被删除的元素节点
    LNode *cp = HL ;        //用cp指向当前节点，初始为表头
    LNode *ap = NULL ;      //用ap指向cp的前驱节点
    if (pos == 0)      //按值查找被删除的节点
    {
        while (cp != NULL)
        {
            if (item == cp -> data)    //找到被删除节点cp。退出循环
                break ;
            ap = cp ;
            cp = cp -> next ;
        }
        if (cp == NULL)
        {
            cout << "单链表中没有相应的节点可以删除" << endl ;
            return false ;
        }
    }
    else if (pos == -1)     //查找表尾节点
    {
        while (cp -> next != NULL)
        {
            ap = cp ;
            cp = cp -> next ;
        }
    }
    else        //按序号查找节点的位置
    {
        int i = 0 ;
        while (cp != NULL)
        {
            i++ ;
            if (i == pos)
                break ;
            else
            {
                ap = cp ;
                cp = cp -> next ;
            }
        }
        if (cp == NULL)
        {
            cout << "pos值无效!" << endl ;
            return false ;
        }
    }
    //删除cp所指向的节点
    if (ap == NULL)     //删除表头节点
        HL = HL -> next ;
    else                //删除非表头节点
        ap -> next = cp -> next ;
    //收回被删除节点的存储空间
    delete cp ;
    //删除成功，返回真
    return true ;
}

LNode* ReverseList(LNode* HL)
{
        if (HL == NULL)
            return HL ;
        LNode* dummy = new LNode(-1);
        dummy -> next = HL;
        LNode* prev = dummy->next;
        LNode* pCur = prev->next;
        while (pCur != NULL) {
            prev->next = pCur->next;
            pCur->next = dummy->next;
            dummy->next = pCur;
            pCur = prev->next;
        }
        return dummy->next ;
}

LNode* L ;

int main ()
{
    InitList(L) ;
    InsertList (L , 1 , -1) ;
    InsertList (L , 2 , -1) ;
    InsertList (L , 3 , -1) ;
    InsertList (L , 4 , -1) ;
    InsertList (L , 5 , -1) ;
    InsertList (L , 6 , -1) ;
    TraverseList(L) ;
    L = ReverseList(L) ;
    TraverseList(L) ;
//    DeleteList (L , 1 , -1) ;
//    TraverseList(L) ;
//    DeleteList (L , 3 , 0) ;
//    TraverseList(L) ;
//    DeleteList (L , 3 , 1) ;
//    TraverseList(L) ;
//
//    TraverseList(L) ;
}
