/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 04-11-2019					                                  */
/******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "service_locator.hpp"
using namespace ilrd;
using namespace std;


static void ServiceLocatorTest();
/******************************************************************************/

class X
{
public:
	X(int x_)
		: m_x(x_)
	{}

	int m_x;
};

class Y
{
public:
	Y(float y_)
		: m_y(y_)
	{}

	float m_y;
};

int main()
{
    ServiceLocatorTest();
    
    return (0);
}

static void ServiceLocatorTest()
{
 ServiceLocator<std::string> serviceLocator;

    X x(1);
    Y y(2.5);

    serviceLocator.Add("first", x);
    serviceLocator.Add("second", y);

    const X& result_1 = serviceLocator.Get<X>("first");
	if(1 != result_1.m_x)
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}

    const Y& result_2 = serviceLocator.Get<Y>("second");
	if(2.5 != result_2.m_y)
	{
		cout << "ERROR in line " << __LINE__ << endl;
	}
}
