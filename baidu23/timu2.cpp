#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    // n = 2, m = 3;
    vector<int> anger(n, 0);
    for (int i = 0; i < n; i++)
        cin >> anger[i];
    // anger[0] = anger[1] = 2;

    // vector<int> left = {1, 1, 2}, right = {1, 2, 2};
    int l, r;
    int ans = 0;
    bool initialized = false;
    for (int i = 0; i < m; i++)
    {
        // cin>>l[i]>>r[i];
        cin >> l >> r;
        // l = left[i], r = right[i];
        for (int people = l; people <= r; people++)
        {
            anger[people - 1]--;
            if (anger[people - 1] < 0)
            {
                cout << i << endl;
                return 0;
            }
        }
    }
    cout << m << endl;

    return 0;
}

