/*
美团25毕业秋招第三题，做题时间2024 8 10

有一根无限长度、颜色循环的彩带，彩带的颜色为N，对彩带进行 k次剪裁，求每次剪裁下来的彩带中颜色的个数

6 3（彩带长为6，进行3次剪裁）
1 2 3 4 1 4 （彩带颜色）
L 2 第一次剪裁：从左边开始，剪裁长度为2
L 3 第二次剪裁：从左边开始，剪裁长度为3
R 12 第三次剪裁：从右边开始，剪裁长度为12

印象中 N k 都是1e9
别的条件不记得了
*/

/*
莫队算法离线查询区间问题，知道L和R可以O(1)推出(L+1,R),(L-1,R),(L,R+1),(L,R-1)的值的问题都可以用莫队算法排序后离线求解
*/
#include <cstdio>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
const int MAXN = 2e6 + 7;
int x[MAXN], block[MAXN];
struct zp
{
    int l, r, id;
} query[MAXN];

int cmp(zp a, zp b) // 按照莫队算法的排序方式可将区间查询的平均复杂度优化为n*sqrt(n)
{
    if (block[a.l] != block[b.l])
        return a.l < b.l;
    else
        return a.r < b.r;
}

int vis[MAXN]; // vis[i]表示 当前区间内数字i出现的个数
int ans[MAXN]; // 结果

void solve(int k) // 暴力求解 k次查询
{
    memset(vis, 0, sizeof(vis));
    int l = query[0].l, r = query[0].l;
    vis[x[l]] = 1;
    int sum = 1;
    for (int i = 0; i < k; i++)
    {
        // 删除操作：删除是先将指针所指的值删除，再将指针移动
        while (l < query[i].l)
        {
            vis[x[l]]--;
            if (vis[x[l]] == 0)
                sum--;
            l++;
        }
        // 加入操作：是先移动指针，再将指向的值加入
        while (l > query[i].l)
        {
            l--;
            if (vis[x[l]] == 0)
                sum++;
            vis[x[l]]++;
        }
        // 加入操作：是先移动指针，再将指向的值加入
        while (r < query[i].r)
        {
            r++;
            if (vis[x[r]] == 0)
                sum++;
            vis[x[r]]++;
        }
        // 删除操作：删除是先将指针所指的值删除，再将指针移动
        while (r > query[i].r)
        {
            vis[x[r]]--;
            if (vis[x[r]] == 0)
                sum--;
            r--;
        }
        ans[query[i].id] = sum;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    // while (~scanf("%d", &n))
    // {
    cin >> n;
    const int sqt = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
        block[i] = (i - 1) / sqt; // 分块
    }

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) // 存储离线查询
    {
        cin >> query[i].l >> query[i].r;
        query[i].id = i;
    }

    sort(query, query + k, cmp); // 莫队算法的关键所在

    solve(k); // 暴力求解

    for (int i = 0; i < k; i++)
        printf("%d\n", ans[i]);
    // }
}