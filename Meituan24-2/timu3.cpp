#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
using Type = unsigned long long;

const Type MOD = 1e9 + 7;

void just(Type &a, Type &b, Type &c)
{
    if (a > b)
        swap(a, b);
    if (a > c)
        swap(a, c);

    if (c < b)
        swap(c, b);

    a %= MOD, b %= MOD, c %= MOD;
}

Type mymin(Type a, Type b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    Type a, b, c, k;
    cin >> a >> b >> c >> k;
    just(a, b, c);
    while (1)
    {
        if (a == b && b == c)
        {
            if (k >= 3)
            {
                Type add = k / 3;
                a += add, b += add, c += add, k -= 3 * add;
            }
            else if (k == 2)
                a++, b++, k -= 2;
            else if (k == 1)
                a++, k--;
        }
        else if (a == b)
        {
            if (k >= 2)
            {
                Type n = k / 2;
                Type cha = c - b;
                Type add = mymin(n, cha);
                a += add, b += add, k -= 2 * add;
            }
            else
                a++, k--;
        }
        else if (a < b)
        {
            Type cha = b - a;
            Type add = mymin(k, cha);
            a += add;
            k -= add;
        }

        just(a, b, c);

        if (k <= 0)
            break;
    }

    cout << ((a * b) % MOD) * c % MOD << endl;

    return 0;
}
