
#include <iostream>

using namespace std;

class Surpriser
{
public:
    virtual void SurpriseMe(void) const {}
};

class Print : public Surpriser
{
public:
    void SurpriseMe(void) const { cout << "Print" << endl; }
    void P() const{ cout << "special p" << endl;};
};

class System : public Surpriser
{
public:
    void SurpriseMe(void) const  { cout << "System" << endl; }
    void S() const{ cout << "special s" << endl;};
};

class CreateFile : public Surpriser
{
public:
    void SurpriseMe(void) const { cout << "CreateFile" << endl; }
    void C() const{ cout << "special c" << endl;};

};

Surpriser *GetRandomSurprise(void)
{
    int res = rand() % 3;

    if (0 == res)
    {
        return new Print;
    }
    else if (1 == res)
    {
        return new System;
    }

    return new CreateFile;
}


int main()
{
    for (size_t i = 0; i < 10; i++)
	{
		Surpriser *todaysSurprise = GetRandomSurprise();

		todaysSurprise->SurpriseMe();
        Print* p = dynamic_cast<Print*>(todaysSurprise);
        System* s = dynamic_cast<System*>(todaysSurprise);
        CreateFile* c = dynamic_cast<CreateFile*>(todaysSurprise);
        if (p)
        {
            p->P();
        }
        else if (s)
        {
            s->S();
        }
        else
        {
            c->C();
        }
        
		delete[] todaysSurprise;
	}

    return 0;
}


