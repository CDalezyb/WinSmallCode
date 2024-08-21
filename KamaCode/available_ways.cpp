#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
using namespace std;

vector<vector<int>> Rec;
unordered_map<int, vector<int>> vert;
int NodeNum, VertNum;
vector<int> path;
unordered_set<int> visited;

void dfs()
{
    if (path[path.size() - 1] == NodeNum)
    {
        Rec.push_back(path);
        return;
    }
    // if (visited.size() == NodeNum)
    //     return;

    // bool valid_wad = false;
    vector<int> &available_node = vert[path.back()];
    for (int i = 0; i < available_node.size(); i++)
    {
        if (visited.find(available_node[i]) == visited.end())
        {
            // valid_wad = true;
            path.push_back(available_node[i]);
            visited.insert(available_node[i]);
            dfs();

            path.pop_back();
            visited.erase(available_node[i]);
        }
    }
}

int main()
{

    cin >> NodeNum >> VertNum;
    while (VertNum--)
    {
        int s, t;
        cin >> s >> t;
        vert[s].push_back(t);
        // vert[t].push_back(s);
    }

    visited.insert(1);
    path.push_back(1);
    dfs();

    for (int i = 0; i < Rec.size(); i++)
    {
        for (int j = 0; j < Rec[i].size(); j++)
        {
            cout << Rec[i][j];

            if (j < Rec[i].size() - 1)
                cout << " ";
        }
        cout << endl;
    }

    if (Rec.empty())
        cout << -1 << endl;

    return 0;
}