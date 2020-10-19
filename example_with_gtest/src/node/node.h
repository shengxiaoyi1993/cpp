#ifndef NODE_H
#define NODE_H

#include<iostream>
using namespace std;

struct LinkNode
{
    int _data;
    LinkNode *_next;
    LinkNode(const int& data)
        :_data(data)
        ,_next(NULL)
    {}
};

class Link
{
public:
    Link()
        :pHead(new LinkNode(0))
    {}
    void PushBack(const int& data)
    {
        if(pHead == NULL)
            return ;
        LinkNode *newNode=new LinkNode(data);
        if(pHead->_next == NULL){  //第一次插入结点
            pHead->_next=newNode;
        }
        else{  //找到最后一个结点直接尾插
            LinkNode *cur=pHead->_next;
            while(cur->_next){
                cur=cur->_next;
            }
            cur->_next=newNode;
        }
    }

    void PopBack()
    {
        if(pHead == NULL)
            return ;
        LinkNode *cur=pHead;
        LinkNode *prev=NULL;
        while(cur->_next)
        {
            prev=cur;
            cur=cur->_next;
        }
        prev->_next=NULL;
        delete cur;
    }

    LinkNode *FindNode(const int& data)
    {
        if(pHead == NULL)
            return NULL;
        LinkNode *cur=pHead->_next;
        while(cur)
        {
            if(cur->_data == data)
                return cur;
            cur=cur->_next;
        }
        return NULL;
    }

    bool Delete(int data)
    {
        LinkNode *pos=FindNode(data);
        if(pos == NULL)
            return false;
        LinkNode *cur=pHead->_next;
        while(cur->_next != pos)
        {
            cur=cur->_next;
        }
        cur->_next=pos->_next;
        delete pos;
        return true;
    }

    void Destroy()
    {
        if(pHead == NULL)
            return;
        LinkNode *cur=pHead->_next;
        while(cur)
        {
            LinkNode *del=cur;
            cur=cur->_next;
            delete del;
            del=NULL;
        }
        delete pHead;  //删除头结点
    }
    LinkNode *pHead;
};

#endif 
