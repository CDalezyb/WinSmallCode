#include <iostream>
#include <vector>
using namespace std;
//  0-1 bag 2D array solution
int bag_01_2DArray()
{
    int m, bagWeight;
    cin >> m >> bagWeight;
    vector<int> weight(m), value(m);
    for (int i = 0; i < m; i++)
        cin >> weight[i];
    for (int i = 0; i < m; i++)
        cin >> value[i];

    // initialize
    // vector<vector<int>> dp(m, vector<int>(bagWeight + 1, 0));
    vector<int> dp(bagWeight + 1, 0);

    for (int i = 0; i < m; i++)
    {
        // when j < weight[i], we do not change the value , so the loop ends
        for (int j = bagWeight; j >= weight[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    cout << dp[bagWeight] << endl;

    return 0;
}

//  0-1 bag roll array solution
int bag_01_rollArray()
{
    int m, bagWeight;
    cin >> m >> bagWeight;
    vector<int> weight(m), value(m);
    for (int i = 0; i < m; i++)
        cin >> weight[i];
    for (int i = 0; i < m; i++)
        cin >> value[i];

    // initialize
    vector<vector<int>> dp(m, vector<int>(bagWeight + 1, 0));
    for (int j = weight[0]; j <= bagWeight; j++)
        dp[0][j] = value[0];

     for (int i = 1; i < m; i++)
    {
        for (int j = bagWeight; j >= 0; j--)
        {
            if (j < weight[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
        }
    }

    cout << dp[m - 1][bagWeight] << endl;
    return 0;
}

int main()
{
    bag_01_rollArray();
    return 0;
}