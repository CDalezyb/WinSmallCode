#include <iostream>
#include <vector>
using namespace std;
/*
https://kamacoder.com/problempage.php?pid=1066
*/
int main()
{

    int BagWeight, N;
    cin >> BagWeight >> N;
    vector<int> weight(N, 0), value(N, 0), Num(N, 0);
    for (int i = 0; i < N; i++)
        cin >> weight[i];
    for (int i = 0; i < N; i++)
        cin >> value[i];
    for (int i = 0; i < N; i++)
        cin >> Num[i];

    vector<int> dp(BagWeight + 1, 0);
    for (int i = 0; i < N; i++) // 物品
    {
        for (int j = BagWeight; j >= weight[i]; j--) // 容量
        {
            for (int k = 1; k <= Num[i] && j - k * weight[i] >= 0; k++) // 数目
            {
                dp[j] = max(dp[j], dp[j - k * weight[i]] + k * value[i]);
            }
        }
    }

    cout << dp[BagWeight] << endl;

    return 0;
}