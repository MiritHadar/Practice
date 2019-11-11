/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/


#ifndef ILRD_RD6768_THREAD
#define ILRD_RD6768_THREAD

#include <iostream>         //   cout    
#include <pthread.h>        //  Threads  
#include <cassert>          //  assert   
#include <errno.h>          //  EINVAL
#include "uncopyable.hpp"

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

namespace ilrd
{

template <typename ClassWithFunc, typename FuncFromClass>
class Wrapper
{
public:
    explicit Wrapper(ClassWithFunc obj_, FuncFromClass func_) : m_obj(obj_), m_func(func_){};
    ClassWithFunc m_obj;
    FuncFromClass m_func;
};

class Thread : private Uncopyable
{
public:
    typedef void(*FuncT)(void);
    //Constructors
    //regular
    explicit Thread(FuncT(f_));

    //Functor
    template <typename Functor>
    static void *ActivateFunctor(void *arg);
    
    template <typename Functor>
    explicit Thread(Functor& f_);
    
    //Memeber Function
    template <typename ClassWithFunc, typename FuncFromClass>
    explicit Thread(ClassWithFunc &obj_, FuncFromClass func_);

    void Detach();
    void Join() const;
    //Thread(const Thread& other_) = delete;
    ~Thread()noexcept;

    //Operators
    //Thread& operator=(const Thread& other_) = default    

private:
    //Member variables
    pthread_t m_thread;
    mutable int m_IsJoined;
};

struct Thread_error : public std::exception
{
    // all Ctors + Dtor generated
};

class Functor
{
public:
    explicit Functor() {}
    void operator()()
    {
        std::cout << "This is a stupuid operator func!" << std::endl;
    }

private:
    
};

//Functor implementation
template <typename Functor>
void *Thread::ActivateFunctor(void *arg)
{
    Functor *PtrFunc = reinterpret_cast<Functor*>(arg);
    (*PtrFunc)();

    return nullptr;
}

template <typename Functor>
Thread::Thread(Functor& f_)
{
    int status = pthread_create(&m_thread, nullptr,
                ActivateFunctor<Functor>, (static_cast<void*>(&f_)));
    assert(EINVAL != status); //Invalid settings in attr

    if (0 != status)
    {
        throw Thread_error();
    }
}

//Member Function implementation
template <typename ClassWithFunc, typename FuncFromClass>
void *MemberFuncForThread(void *args)
{
    Wrapper<ClassWithFunc, FuncFromClass> *func_ptr =
                    static_cast< Wrapper<ClassWithFunc, FuncFromClass> *>(args);
    (func_ptr->m_obj.*func_ptr->m_func)();

    delete func_ptr;
    return nullptr;
}

template <typename ClassWithFunc, typename FuncFromClass>
Thread::Thread(ClassWithFunc &obj_, FuncFromClass func_)
{
    Wrapper<ClassWithFunc, FuncFromClass> *wrapperInfo =
                                new Wrapper<ClassWithFunc, FuncFromClass>(obj_, func_);

    int status = pthread_create(&m_thread, nullptr,
                        MemberFuncForThread<ClassWithFunc, FuncFromClass>, wrapperInfo);
    assert(EINVAL != status); //Invalid settings in attr

    if (0 != status)
    {
        throw Thread_error();
    }
}

}//namespace ilrd

#endif  /*ILRD_RD6768_THREAD*/
