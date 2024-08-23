#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SegmentTree
{
    vector<int> tree;
    vector<int> lazy;
    int n;

    SegmentTree(int size) : n(size), tree(4 * size, 0), lazy(4 * size, 0) {}

    void updateRange(int start, int end, int value, int node = 1, int l = 0, int r = n - 1)
    {
        if (lazy[node] != 0)
        {
            tree[node] += lazy[node] * (r - l + 1);
            if (l != r)
            {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > r || end < l)
            return;
        if (start <= l && r <= end)
        {
            tree[node] += value * (r - l + 1);
            if (l != r)
            {
                lazy[node * 2] += value;
                lazy[node * 2 + 1] += value;
            }
            return;
        }
        int mid = (l + r) / 2;
        updateRange(start, end, value, node * 2, l, mid);
        updateRange(start, end, value, node * 2 + 1, mid + 1, r);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    bool checkRange(int start, int end, int threshold, int node = 1, int l = 0, int r = n - 1)
    {
        if (start > r || end < l)
            return false;
        if (lazy[node] != 0)
        {
            tree[node] += lazy[node] * (r - l + 1);
            if (l != r)
            {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start <= l && r <= end)
        {
            return tree[node] > threshold * (r - l + 1);
        }
        int mid = (l + r) / 2;
        bool left = checkRange(start, end, threshold, node * 2, l, mid);
        if (left)
            return true;
        return checkRange(start, end, threshold, node * 2 + 1, mid + 1, r);
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    SegmentTree st(n);

    vector<int> anger(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> anger[i];
    }

    int lastVersion = -1;
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        cin >> l >> r;
        st.updateRange(l - 1, r - 1, 1);

        if (st.checkRange(0, n - 1, *max_element(anger.begin(), anger.end())))
        {
            lastVersion = i - 1;
            break;
        }
    }

    if (lastVersion == -1)
    {
        lastVersion = m;
    }

    cout << lastVersion << endl;
    return 0;
}