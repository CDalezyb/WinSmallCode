#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int N, M;
vector<vector<int>> Grid;
vector<vector<bool>> visited;
unordered_map<int, int> grid2Area; // 标号为first的岛屿，对应的面积是多少

int Step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(const int i, const int j, int GridId, int &area)
{
    if (visited[i][j])
        return;

    visited[i][j] = true;
    Grid[i][j] = GridId;
    area++;
    for (int step = 0; step < 4; step++)
    {
        int ti = i + Step[step][0];
        int tj = j + Step[step][1];
        if (ti < 0 || ti >= N || tj < 0 || tj >= M)
            continue;
        if (!visited[ti][tj] && Grid[ti][tj] > 0)
            dfs(ti, tj, GridId, area);
    }
}

int main()
{
    cin >> N >> M;
    Grid.resize(N, vector<int>(M, 0));
    visited.resize(N, vector<bool>(M, false));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cin >> Grid[i][j];
    }

    int GridId = 2;
    int area = 0;
    bool isAllLand = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (Grid[i][j] == 0)
                isAllLand = false;
            else if (!visited[i][j])
            {
                area = 0;
                dfs(i, j, GridId, area);
                grid2Area[GridId] = area;
                GridId++;
            }
        }
    }

    if (isAllLand)
    {
        cout << N * M << endl;
        return 0;
    }

    int ans = 0;
    unordered_set<int> visitedGridId;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {

            if (Grid[i][j] == 0)
            {
                area = 1;
                visitedGridId.clear();

                for (int step = 0; step < 4; step++)
                {
                    int ti = i + Step[step][0];
                    int tj = j + Step[step][1];
                    if (ti < 0 || ti >= N || tj < 0 || tj >= M || Grid[ti][tj] == 0)
                        continue;

                    if (visitedGridId.find(Grid[ti][tj]) != visitedGridId.end())
                        continue;

                    area += grid2Area[Grid[ti][tj]];
                    visitedGridId.insert(Grid[ti][tj]);
                }

                ans = max(ans, area);
            }
        }
    }

    cout << ans << endl;
    return 0;
}