#include<iostream>
#include<string>
using namespace std;


int main()
{
    string a = "FrrnlhKdqKrdq";
    for (int i = 0; i < a.size(); i++)
    {
        a[i] = a[i] - 3;
    }
    cout << a;
    return 0;
}