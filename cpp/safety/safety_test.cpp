/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************




 void Fishi()
{
	cout << "Fishi" << endl;
}

void Bar(int *arr2)
{
	cout << "Bar" << endl;
}

void Dodo()
{
	cout << "Dodo" << endl;
}


void Foo(bool goKaboomEarly)
{
	int* arr1 = new int[10];
	if (goKaboomEarly)
	{
		Bar(arr1);
	}

	int* arr2 = new int[100];

	Fishi();
	Bar(arr2);
	Dodo();

	throw 10;

	delete[] arr2;
	delete[] arr1;
}

int main(void)
{
	set_unexpected(Fishi);
	set_terminate(Dodo);
	Foo(true);

	return 0;
}
 */
#include <iostream>
#include <typeinfo>

using namespace std;

int Foo(int) { throw bad_alloc(); }

void Bar() { throw bad_cast(); }
class X
{
public:
	~X()
	{
		cerr << Foo(m_a) << endl;
	}

private:
	int m_a;
};

void Fishi()
{
	X x1;
	Bar();
}

int main()
{
	try
	{
		/* code */
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	Fishi();

	return 0;
}