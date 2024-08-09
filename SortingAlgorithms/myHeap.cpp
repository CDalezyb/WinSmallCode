#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

// small above
template <class T>
struct myGreater
{
    bool operator()(const T &left, const T &right) { return left > right; }
};

// big above
template <class T>
struct myLess
{
    bool operator()(const T &left, const T &right) { return left < right; }
};

// default is big above heap
template <class T, class Compare = myLess<T>>
class myHeap
{
public:
    myHeap() = default;
    myHeap(vector<T> elems)
    {
        _array.reserve(elems.size());
        _array.assign(elems.begin(), elems.end());

        for (int i = _array.size() / 2 - 1; i >= 0; i--)
            AjustDown(i);
    }

    bool empty() const { return _array.empty(); }

    size_t size() const { return _array.size(); }

    T &top()
    {
        assert(!_array.empty());
        return _array[0];
    }

    void pop()
    {
        if (_array.empty())
            return;
        swap(_array[0], _array[_array.size() - 1]);
        _array.pop_back();
        AjustDown(0);
    }

    void push(T in)
    {
        _array.push_back(in);
        AjustUp(_array.size() - 1);
    }

private:
    void AjustDown(int parent)
    {
        int child = parent * 2 + 1;
        while (child < _array.size())
        {
            if (child + 1 < _array.size() && cmp(_array[child], _array[child + 1]))
                child = child + 1;

            if (cmp(_array[parent], _array[child]))
            {
                swap(_array[parent], _array[child]);
                parent = child;
                child = 2 * parent + 1;
            }
            else
                break;
        }
    }

    void AjustUp(int child)
    {
        int parent = (child - 1) / 2;
        while (parent >= 0)
        {
            if (cmp(_array[parent], _array[child]))
            {
                swap(_array[parent], _array[child]);
                child = parent;
                parent = (child - 1) / 2;
            }
            else
                break;
        }
    }

    vector<T> _array;
    Compare cmp;
};

template <class T>
using maxHeap = myHeap<T, myLess<T>>;

template <class T>
using minHeap = myHeap<T, myGreater<T>>;

int main()
{
    vector<int> a = {11, 10, 13, 12, 16, 18, 15, 17, 14, 19};
    myHeap<int> hp1(a);
    cout << hp1.top() << endl;
    hp1.push(90);
    hp1.push(900);
    cout << hp1.top() << endl;
    hp1.pop();
    hp1.pop();
    hp1.pop();
    hp1.pop();
    hp1.pop();
    hp1.pop();
    hp1.pop();

    // system("pause");
    return 0;
}
