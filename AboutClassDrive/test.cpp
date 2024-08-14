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

    void new_func()
    {
        cout << " Derived new function." << std::endl;
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

    b1.new_func();
    b2->new_func();
    b3.new_func();
}

void Do()
{
    Derived d;
}

int main()
{

    Do();
    cout << "-------------------------------" << endl;
    Derived d;
    f(d);
    // int a = 0;
    // cout << "-------------------------------" << endl;
    return 0;
}