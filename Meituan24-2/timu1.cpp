#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
// #include<pair>
using namespace std;
/*
 第一行：给你 (a, b)  (c,d) 两个坐标
 第二行：给你一个
*/

using Type = long long;
Type a, b, c, d;
Type n;

vector<pair<Type, Type>> pos;

struct Point
{
    Type x, y;

    Type distance(Point Tar)
    {
        return abs(x - Tar.x) + abs(y - Tar.y);
    }
};
struct Bottle
{
    Point pos;
    Type disStart, disEnd;
    Type add;
};

bool cmp(Bottle l, Bottle r)
{
    return l.add < r.add;
}

int main()
{
    Point start, end;
    cin >> start.x >> start.y >> end.x >> end.y;

    Type n;
    cin >> n;
    vector<Bottle> bottles(n);

    for (Type i = 0; i < n; i++)
    {
        cin >> bottles[i].pos.x >> bottles[i].pos.y;
        bottles[i].disStart = bottles[i].pos.distance(start);
        bottles[i].disEnd = bottles[i].pos.distance(end);
        bottles[i].add = bottles[i].disStart - bottles[i].disEnd;
    }

    sort(bottles.begin(), bottles.end(), cmp);

    long long ans = 0;
    ans += bottles[0].add;
    for (int i = 0; i < bottles.size(); i++)
    {
        ans += bottles[i].disEnd * 2;
    }

    cout << ans << endl;

    return 0;
}