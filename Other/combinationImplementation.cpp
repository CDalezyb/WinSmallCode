#include <vector>
#include <iostream>
#include <string>
using namespace std;
// 用于计算 C(n,m)
long long myC(int n, int m, const int mod = 1);

int main()
{
    string str;
    cin >> str;
    vector<int> Count(26, 0);
    for (auto c : str)
        Count[c - 'a']++;

    for (auto c : Count)
        cout << c << " ";
    cout << endl;

    long long ans = 1;
    const long mod = (1e9 + 7);
    for (auto c : Count)
    {
        if (c == 0)
            continue;
        int sum = 0;
        for (int i = 0; i <= c; i += 2)
        {
            sum += myC(c, i);
        }
        ans *= sum;
        // cout << "sum:" << sum << endl;
        ans %= mod;
    }
    cout << ans - 1 << endl;

    return 0;
}

long long myC(int n, int m, const int mod)
{
    if (n == 0 || m == 0)
        return 1;
    // cout << "calculating:C(" << n << ", " << m << "):";
    m = min(m, n - m);

    int down = m;
    long long ans = 1;
    int count = m;
    while (count-- > 0)
    {
        ans *= n--;
        // for sure : ans>down
        while (down != 0 && ans % down == 0)
            ans /= down--;
    }

    // cout << ans << endl;

    return ans;
}