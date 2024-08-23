#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> H;
vector<vector<bool>> oneReach;
vector<vector<bool>> twoReach;
int Step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool isValid(int i, int j)
{
    return i >= 0 && i < N && j >= 0 && j < M;
}

// visit from bottom to top
void dfs(vector<vector<bool>> &visited, int i, int j)
{
    if (visited[i][j])
        return;

    visited[i][j] = true;

    for (int step = 0; step < 4; step++)
    {
        int try_i = i + Step[step][0];
        int try_j = j + Step[step][1];

        if (!isValid(try_i, try_j) || H[i][j] > H[try_i][try_j])
            continue;

        dfs(visited, try_i, try_j);
    }
}

int main()
{
    cin >> N >> M;
    H.resize(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> H[i][j];

    oneReach.resize(N, vector<bool>(M, false));
    twoReach.resize(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++)
    {
        dfs(oneReach, i, 0);
        dfs(twoReach, i, M - 1);
    }

    for (int j = 0; j < M; j++)
    {
        dfs(oneReach, 0, j);
        dfs(twoReach, N - 1, j);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            if (oneReach[i][j] && twoReach[i][j])
                cout << i << " " << j << endl;
    }

    return 0;
}