#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main()
{
    int n;
    cin >> n;

    vector<int> up(n, 0), down(n, 0);
    vector<int> pure(n, 0);
    for (int i = 0; i < n; i++)
        cin >> up[i];
    for (int i = 0; i < n; i++)
        cin >> down[i];
    for (int i = 0; i < n; i++)
        pure[i] = up[i] - down[i];

    sort(pure.begin(), pure.end());
    long long fu = 0;
    long long zheng = 0;
    for (int i = 0; i < n; i++)
    {
        if (pure[i] < 0)
            fu += pure[i];
        if (pure[i] > 0)
            zheng += pure[i];
    }
    cout << max(abs(fu), zheng) << endl;
    return 0;
}