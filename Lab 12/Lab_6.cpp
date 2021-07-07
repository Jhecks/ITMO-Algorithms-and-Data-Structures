#include <iostream>
#include <vector>
#include <string>
 
#define MAX 10000
 
using namespace std;
 
vector<int> dp(MAX + 2);
vector<int> weights(MAX);
vector<vector<int>> tree(MAX);
vector<bool> was(MAX, false);
 
int n;
int root = 0;
 
void input()
{
    cin >> n;
    for (int to = 0; to < n; ++to)
    {
        int from, w;
        cin >> from >> w;
        from--;
        if (from >= 0)
            tree[from].push_back(to);
        else
            root = to;
        weights[to] = w;
    }
}
 
int dfs(int v)
{
    int ans = weights[v];
    for (auto to: tree[v])
        for (auto toto : tree[to])
        {
            if (!was[toto])
                ans += dfs(toto);
            else
                ans += dp[toto];
        }
 
    int temp = 0;
 
    for (auto to : tree[v])
    {
        if (!was[to])
            temp += dfs(to);
        else
            temp += dp[to];
    }
 
    dp[v] = max(temp, ans);
    was[v] = true;
 
    return max(temp, ans);
}
 
int main()
{
    freopen("selectw.in",  "r", stdin);
    freopen("selectw.out", "w", stdout);
 
    input();
 
    cout << dfs(root);
}
