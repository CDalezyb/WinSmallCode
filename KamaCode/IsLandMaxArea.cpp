#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
using namespace std;

int ans;
int N, M;

const int dir[4][4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
void bfs(int i, int j, int &area, const vector<vector<int>> &A, vector<vector<bool>> &visited);
void dfs(int i, int j, int &area, const vector<vector<int>> &A, vector<vector<bool>> &visited);
bool isValid(const int N, const int M, int i, int j)
{
    return i >= 0 && i < N && j >= 0 && j < M;
}

void solve(vector<vector<int>> &A, vector<vector<bool>> &visited)
{
    int area = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (A[i][j] == 1 && visited[i][j] == false)
            {
                area = 0;

                // bfs
                bfs(i, j, area, A, visited);
                ans = max(area, ans);
                

                // dfs
                // dfs(i, j, area, A, visited);
                // ans = max(area, ans);

                int a = 0;
            }
        }
    }
}

void dfs(int cur_x, int cur_y, int &area, const vector<vector<int>> &A, vector<vector<bool>> &visited)
{
    visited[cur_x][cur_y] = true;
    area++;
    for (int i = 0; i < 4; i++)
    {
        int try_x = cur_x + dir[i][0];
        int try_y = cur_y + dir[i][1];
        if (isValid(N, M, try_x, try_y) && A[try_x][try_y] == 1 && !visited[try_x][try_y])
        {
            dfs(try_x, try_y, area, A, visited);
        }
    }
}

void bfs(int i, int j, int &area, const vector<vector<int>> &A, vector<vector<bool>> &visited)
{
    queue<pair<int, int>> que;

    que.push(pair<int, int>(i, j));
    while (!que.empty())
    {
        pair<int, int> cur = que.front();
        que.pop();
        int cur_x = cur.first;
        int cur_y = cur.second;
        visited[cur_x][cur_y] = true;
        area++;
        for (int i = 0; i < 4; i++)
        {
            int try_x = cur_x + dir[i][0];
            int try_y = cur_y + dir[i][1];
            if (isValid(N, M, try_x, try_y) && A[try_x][try_y] == 1 && !visited[try_x][try_y])
            {
                que.push(pair<int, int>(try_x, try_y));
                visited[try_x][try_y] = true;
            }
        }
    }
}

int main()
{

    cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(M, 0));
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> A[i][j];

    ans = 0;
    solve(A, visited);
    cout << ans << endl;

    return 0;
}