#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
const int M = 2 * N;

int n, m;
vector<int> Color(N, -1);
vector<vector<int>> edge(N, vector<int>());

// 对 point 染色为 color
// 并将与point 相连的点设置为
void dfs(int point, int color)
{
    Color[point] = color;
    if (color == 1)
        m++; // m 表示染色为1的数量
    for (int i = 0; i < edge[point].size(); i++)
    {
        int b = edge[point][i];
        if (Color[b] == -1)
        {
            dfs(b, 1 - color);
        }
    }
}

void bfs()
{
    queue<pair<int, int>> qPointColor;
    qPointColor.push(pair<int, int>(1, 1));

    while (!qPointColor.empty())
    {

        int point = qPointColor.front().first;
        int color = qPointColor.front().second;
        qPointColor.pop();

        Color[point] = color;
        if (color == 1)
            m++;

        for (int i = 0; i < edge[point].size(); i++)
        {
            int b = edge[point][i];
            if (Color[b] == -1)
            {
                qPointColor.push(pair<int, int>(b, 1 - color));
            }
        }
    }

    // for (int i = 1; i <= n; i++)
    // {

    //     cout << endl;
    // }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    // dfs(1, 1);
    bfs();
    cout << (long long)m * (n - m) - n + 1;
    return 0;
}

/*
给定一个 n 个节点的树。树的节点编号为 1∼n。
请你为这棵树增加一些边，要求增边后的图形仍是二分图，并且不含重边和自环.请问，最多可以增加多少条边。

输入格式
第一行包含整数 n，表示树的节点数量。
接下来 n−1 行，每行包含两个整数 a,b，表示节点 a 和节点 b 之间存在一条边。

输出格式
一个整数，表示可以增加的边的最大数量。

数据范围:前三个测试点满足 1≤n≤10。所有测试点满足 1≤n≤105，1≤a,b≤n。

*/