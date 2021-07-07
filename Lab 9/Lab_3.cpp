#include <iostream>
#include <vector>
 
using namespace std;
 
vector <vector<int>> Graph;
vector <char> Color;
 
struct Pair
{
    int first;
    int second;
};
 
 
void BuildGraph()
{
    Pair input;
    cin >> input.first >> input.second;
 
    Graph.resize(input.first);
    for (int i = 0; i < input.second; i++)
    {
        Pair tmp;
        cin >> tmp.first >> tmp.second;
        tmp.first--; tmp.second--;
        Graph[tmp.first].push_back(tmp.second);
        Graph[tmp.second].push_back(tmp.first);
    }
}
 
void DFS(int v, char c)
{
    Color[v] = c;
    for (int i : Graph[v])
    {
        if (Color[i] == 0)
            DFS(i, c == 1 ? 2 : 1);
        else if (Color[i] == c)
        {
            cout << "NO";
            exit(0);
        }
    }
}
 
void DefineBipartite()
{
    Color.resize(Graph.size(), 0);
 
    for (int i = 0; i < Graph.size(); i++)
    {
        if (Color[i] == 0)
            DFS(i, 1);
    }
 
    cout << "YES";
}
 
int main()
{
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
 
    BuildGraph();
    DefineBipartite();
 
    return 0;
}
