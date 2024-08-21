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
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <set>

#define int long long

using namespace std;

constexpr int MAXN = 2e6 + 7;

int n, q, colc;
int a[MAXN], ans[MAXN], hsh[MAXN], vis[MAXN];


// 查询区间 l r 和出现顺序 idx
vector<tuple<int, int, int>> qu;

int c[MAXN];

int lowbit(int x)
{
    return x & -x;
}

void update(int x, int k)
{
    for (int i = x; i < MAXN; i += lowbit(i))
    {
        c[i] += k;
    }
}

int getsum(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        sum += c[i];
    }
    return sum;
}

int main()
{

    // accelerate cout and cin
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // n为彩带长度，q为裁剪次数
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        hsh[i] = a[i];
    }
    // hsh是为了计算彩带中颜色个数 （len）
    sort(hsh + 1, hsh + n + 1);
    // unique作用：对于一个已经排序的数组，求出不同元素的个数，即代表彩带不同颜色
    int len = unique(hsh + 1, hsh + n + 1) - hsh - 1;

    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(hsh + 1, hsh + len + 1, a[i]) - hsh;
        a[n + i] = a[i];
    }

    int nl = 1, nr = n * 2;
    for (int i = 1; i <= q; i++)
    {
        char c;
        int x;
        cin >> c >> x;
        x = min(x, n);
        if (c == 'L')
        {
            if (nl > n)
            {
                nl -= n;
            }
            qu.emplace_back(nl, nl + x - 1, i);
            nl = nl + x;
        }
        else
        {
            if (nr <= n)
            {
                nr += n;
            }
            qu.emplace_back(nr - x + 1, nr, i);
            nr = nr - x;
        }
    }

    sort(qu.begin(), qu.end(), [](auto x, auto y)
         {
        auto [l1, r1, id1] = x;
        auto [l2, r2, id2] = y;
        return r1 < r2; });

    int cur = 1;
    for (auto [l, r, id] : qu)
    {

        for (int i = cur; i <= r; i++)
        {
            if (vis[a[i]])
            {
                update(vis[a[i]], -1);
            }
            update(i, 1);
            vis[a[i]] = i;
        }
        cur = r + 1;
        ans[id] = getsum(r) - getsum(l - 1);
    }

    for (int i = 1; i <= q; i++)
    {
        cout << ans[i] << endl;
    }

    return 0;
}