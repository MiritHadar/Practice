/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "inheritance.hpp"

int main(void)
{
	Base *b1 = new Base;
	Base *b2 = new Derived; //why?
	Derived *b3 = new Derived; //why?

	std::cout <<std::endl << "main b1:"<<std::endl;
	b1->Print1();
	b1->Print2();
	b1->Print3();

	std::cout <<std::endl << "main b2:"<<std::endl;
	b2->Print1();
	b2->Print2();
	b2->Print3();

	Derived* d = static_cast<Derived*>(b2);

	std::cout << std::endl << "main d;"<<std::endl;
	d->Print2();
	b2->Print2(); //run time
	/* std::cout << "b1: " << sizeof(Base) <<std::endl;
	std::cout << "b2: " << sizeof(Derived) <<std::endl;
	
	delete b1;
	delete b2;
	delete b3; */

	return 0;
}

