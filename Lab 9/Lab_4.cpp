#include <iostream>
#include <vector>
 
using namespace std;
 
vector<vector <int>> Graph, GraphT;
vector<int> OrderList, Component;
vector<bool> Visited;
size_t componentCount = 1;
 
void BuildGraph()
{
    size_t n, m;
    cin >> n >> m;
    Graph.resize(n);
    GraphT.resize(n);
    Component.resize(n);
    Visited.resize(n, false);
 
    for (size_t i = 0; i < m; i++)
    {
        int first, second;
        cin >> first >> second;
        Graph[first - 1].push_back(second - 1);
        GraphT[second - 1].push_back(first - 1);
    }
}
 
void dfs(size_t &v)
{
    Visited[v] = true;
    for (size_t i = 0; i < Graph[v].size(); i++)
    {
        size_t temp = Graph[v][i];
        if (!Visited[temp])
            dfs(temp);
    }
    OrderList.push_back(v);
}
 
void dfst(size_t &v)
{
    Visited[v] = true;
    Component[v] = componentCount;
    for (size_t i = 0; i < GraphT[v].size(); i++)
    {
        size_t temp = GraphT[v][i];
        if (!Visited[temp])
            dfst(temp);
    }
}
 
void FindComponents()
{
    for (size_t i = 0; i < Graph.size(); i++)
        if (!Visited[i])
            dfs(i);
    Visited.assign(Graph.size(), false);
 
    for (size_t i = 0; i < Graph.size(); i++) {
        size_t v = OrderList[Graph.size() - 1 - i];
        if (!Visited[v])
        {
            dfst(v);
            componentCount++;
        }
    }
}
 
int main()
{
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);
 
    BuildGraph();
    FindComponents();
 
    cout << componentCount - 1 << endl;
    for (size_t i = 0; i < Graph.size(); i++)
        cout << Component[i] << " ";
    return 0;
}
