#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> x(n, 0), y(n, 0), z(n, 0);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i] >> z[i];

    // int coins = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (j > x[i])
        }
    }

    dp[i][j] = max(dp[i - 1][j + x[i]] + y[i], dp[i - 1][j - z[i]]);

    cout << maxGold << endl;

    return 0;
}