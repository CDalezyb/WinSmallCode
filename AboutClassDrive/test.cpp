#include <iostream>
using namespace std;

struct Base
{
    Base()
    {
        cout << "Base constructed" << endl;
        echo();
        
    }

    virtual ~Base()
    {
        cout << "Base deconstructed" << endl;
        echo();
        
    }
    virtual void echo() const
    {
        cout << "Base" << endl;
    }
};

struct Derived : Base
{
    Derived()
    {
        cout << "Derived constructed" << endl;
        echo();
        
    }

    ~Derived()
    {
        cout << "Derived deconstructed" << endl;
        echo();
        
    }

    void echo() const override
    {
        cout << "Derived" << endl;
    }
};

void f(const Derived &d)
{
    const Base &b1 = d;
    const Base *b2 = &d;
    const Base b3 = d;
    b1.echo();
    b2->echo();
    b3.echo();
}

void Do()
{
    Derived d;
}

int main()
{
    // Derived d;
    Do();
    // cout << "-------------------------------" << endl;
    // f(d);
    // int a = 0;
    // cout << "-------------------------------" << endl;
    return 0;
}