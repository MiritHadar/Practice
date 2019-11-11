/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_stack
#define __OL67_stack

#include <cstddef>  /*size_t*/
#include "../utils/detail.hpp"

template <class T>
class Stack
{
public:
    explicit Stack();
    ~Stack();

    void Push(T data);
    void Pop();
    T Top() const;
    size_t Count() const;
    bool IsEmpty() const;

    class Node
    {
    public:
        explicit Node();
        explicit Node(T data, Node *next);
        T GetData() const;
        bool HasNext() const;
        const Node &GetNext() const;
    
        const T m_data;
        mutable const Node* m_next;
    };

    Node m_dummy;
};//class stack

template <class T>
Stack<T>::Node::Node()
    : m_data(0), m_next(Deadbeef<Node>())
{
    ;
}

template <class T>
Stack<T>::Node::Node(T data, Node* next)
    : m_data(data), m_next(next)
{
    ;
}

template <class T>
T Stack<T>::Node::GetData() const
{
    return m_data;
}

template <class T>
bool Stack<T>::Node::HasNext() const
{
    return (Deadbeef<Node>() != m_next);
}

template <class T>
const class Stack<T>::Node& Stack<T>::Node::GetNext() const
{
    return *m_next;
}

template <class T>
Stack<T>::Stack()
    : m_dummy(Node())
{
    ;
}

template <class T>
Stack<T>::~Stack()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

template <class T>
void Stack<T>::Push(T data)
{
    m_dummy.m_next = new Node(data, const_cast<Node*>(m_dummy.m_next));
}

template <class T>
void Stack<T>::Pop()
{
    if (Deadbeef<Node>() == m_dummy.m_next)
    {
        return;
    }

    const Node *toRemove = m_dummy.m_next;
    m_dummy.m_next = &m_dummy.GetNext().GetNext();

    delete toRemove;
}

template <class T>
T Stack<T>::Top() const
{
    return m_dummy.GetNext().GetData();
}

template <class T>
size_t Stack<T>::Count() const
{
    size_t counter = 0;
    Node *runner = (Node*)m_dummy.m_next;

    while (Deadbeef<Node>() != runner)
    {
        ++counter;
        runner = (Node*)runner->m_next;
    }
    
    return counter;
}

template <class T>
bool Stack<T>::IsEmpty() const
{
    return !m_dummy.HasNext();
}

#endif /* __OL67_stack */


 