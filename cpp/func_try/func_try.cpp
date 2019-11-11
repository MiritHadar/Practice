
#include <bits/stdc++.h> 
#include <iostream>

using namespace std;

class Func
{
public:
    Func(int n) : m_num(n) {}
    int operator () (int to_add) const
    {
        return m_num + to_add;
    }
private:
    int m_num;
};

class Base
{

};


int main()
{
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int to_add = 5;

    transform(arr, arr + n, arr, Func(to_add));

    for (int i=0; i<n; i++) 
        cout << arr[i] << " "; 
    cout << endl;

    return 0;
}