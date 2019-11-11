/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include "factory.hpp"

using namespace std;
using namespace ilrd;

class Key
{
public:
friend bool operator<(const Key &left_, const Key &right_);
	Key(int idNum_ = 0)
		: m_idNum(idNum_)
	{
		;
	}

private:
	int m_idNum;
};


bool operator<(const Key &left_, const Key &right_)
{
	return left_.m_idNum < right_.m_idNum;
}

class Shape
{
public:
	static SharedPtr<Shape> Create()
	{
		SharedPtr<Shape> ptr = new Shape; 
		cout << "Create a Shape" << endl;
		return ptr;
	}
	//virtual ~Shape();
	Key GetID() { return m_key;}
private:
	Key m_key;
};

class Circle : public Shape
{
public:
	Circle(int numId_) : m_key(numId_ = 1) {}
	static SharedPtr<Shape> Create()
	{
		SharedPtr<Shape> ptr = new Shape; 
		cout << "Create a Circle" << endl;
		return ptr;
	}
private:
	Key m_key;
};

class Rect : public Shape
{
public:
	Rect(int numId_) : m_key(numId_ = 2) {}
	static SharedPtr<Shape> Create()
	{
		SharedPtr<Shape> ptr = new Shape; 
		cout << "Create a Rect" << endl;
		return ptr;
	}
private:
	Key m_key;
};

/***********************************************************************************/

int main(void)
{
	Factory<Key, Shape> f;
	Key key(4);
	f.Learn(key, &Circle::Create); 
	f.Create(key);

	return 0;
}

