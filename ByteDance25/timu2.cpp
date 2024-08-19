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
    // vector<vector<int>> dp(n, vector<int>(m, 0));

    queue<pair<int, int>> que;
    que.push(pair<int, int>(0, 0));
    int loopmaxGold = 0;
    for (int i = 0; i < n; i++)
    {
        int size = que.size();
        loopmaxGold = -1;
        for (int j = 0; j < size; j++)
        {
            int stone = que.front().first;
            int gold = que.front().second;

            if (stone >= x[i])
            {
                que.push(pair<int, int>(stone - x[i], gold + y[i]));
            }

            if (stone + z[i] >= m)
            {
                if (gold <= loopmaxGold)
                    continue;
                else
                    loopmaxGold = gold;
            }
            stone = min(m, stone + z[i]);
            que.push(pair<int, int>(stone, gold));

            que.pop();
        }
    }

    int maxGold = -1;
    for (int i = 0; i < que.size(); i++)
    {
        int stone = que.front().first;
        int gold = que.front().second;
        maxGold = max(maxGold, stone + gold);
        que.pop();
    }

    cout << maxGold << endl;

    return 0;
}