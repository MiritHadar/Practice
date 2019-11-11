/******************************************************************************/
/* author: 		Ori Michaeli											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 04-11-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_SERVICE_LOCATOR
#define ILRD_RD6768_SERVICE_LOCATOR

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <map>					// 	map

#include "uncopyable.hpp"		// 	For inaccessible CCtor and assign operator
#include "sharedPtr.hpp"		//	SharedPtr header

namespace ilrd
{
template<typename KEY>
class ServiceLocator
{
private:
    class Service 
    {
    public: 
        // explicit Service() = default;
        virtual ~Service(){}

    };// Service

    template<typename T>
    class ServiceHolder : public Service
    {
    public:
        ServiceHolder(T &service_) 
            : m_service(service_)
        {}
        //~ServiceHolder() = default;

        //member functions
        T &Get()
        {
            return m_service;
        }

    private:
        T &m_service;

    };// ServiceHolder

public:
    //Constructors
    // explicit ServiceLocator() = default;
    ~ServiceLocator();

    //member functions
    template<typename T>
    void Add(KEY key_, T &service_);

    template<typename T>
    T &Get(KEY key_);

private:
    //Member variables
    std::map<KEY, Service *> m_keyToService;
};//ServiceLocator 

template<typename KEY>
ServiceLocator<KEY>::~ServiceLocator()
{
    //TODO : delete
}

template<typename KEY>
template<typename T>
void ServiceLocator<KEY>::Add(KEY key_, T &service_)
{
    m_keyToService[key_] = new ServiceHolder<T>(service_);
}

template<typename KEY>
template<typename T>
T &ServiceLocator<KEY>::Get(KEY key_)
{
    return (dynamic_cast<ServiceHolder<T> *>(m_keyToService[key_]))->Get();
}

}//namespace ilrd

#endif  //ILRD_RD6768_SERVICE_LOCATOR
