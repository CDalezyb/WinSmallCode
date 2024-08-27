#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
using namespace std;

int m, n;

int Step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int zhouchang(vector<vector<short>> Grid, int i, int j)
{
    int ans = 0;

    for (int step = 0; step < 4; step++)
    {
        int ti = i + Step[step][0];
        int tj = j + Step[step][1];

        if (ti < 0 || ti >= m || tj < 0 || tj >= n)
            continue;
        if (Grid[ti][tj] == 0)
        {

            ans++;
            // if (i == 3 && j == 2)
            // {
            //     cout << "add:" << ti << " " << tj << endl;
            // }
        }
    }
    return ans;
}

int main()
{

    cin >> m >> n;

    vector<vector<short>> Grid(m + 2, vector<short>(n + 2, 0));
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> Grid[i + 1][j + 1];
    }

    m+=2, n+=2;

    long long ans = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            if (Grid[i][j] == 1)
            {
                int add = zhouchang(Grid, i, j);
                ans += add;
                // cout << "i j add :" << i << " " << j << " " << add << endl;
            }
    }

    cout << ans << endl;

    return 0;
}