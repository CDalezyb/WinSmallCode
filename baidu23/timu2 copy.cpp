#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool RedTemp(const vector<int> &anger, const vector<int> &diff)
{
    int cur_anger = 0;
    for (int i = 1; i < anger.size(); i++)
    {
        cur_anger += diff[i];
        if (cur_anger > anger[i])
            return true;
    }
    return false;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> anger(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> anger[i];

    int l, r;
    vector<pair<int, int>> operations(m + 1);
    for (int i = 1; i <= m; i++)
        cin >> operations[i].first >> operations[i].second;

    int left = 1, right = m, ans = m;
    vector<int> diff(n + 2, 0);
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        fill(diff.begin(), diff.end(), 0);
        for (int i = 1; i <= mid; i++)
        {
            l = operations[i].first, r = operations[i].second;
            diff[l]++;
            if (r + 1 <= n + 1)
                diff[r + 1]--;
        }

        if (RedTemp(anger, diff))
        {
            right = mid - 1;
            ans = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    cout << ans << endl;

    return 0;
}
