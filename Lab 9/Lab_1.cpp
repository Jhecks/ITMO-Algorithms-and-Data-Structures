#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
vector <vector <int>> Graph;
vector <int> TopSeq;
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
        Pair input1;
        cin >> input1.first >> input1.second;
        input1.first--;
        input1.second--;
        Graph[input1.first].push_back(input1.second);
    }
}
 
void DFS(int v) 
{
    Color[v] = 1;
    for (int i : Graph[v]) 
    {
        if (Color[i] == 0)
            DFS(i);
        else if (Color[i] == 1)
        {
            cout << -1;
            exit(0);
        }
    }
    TopSeq.push_back(v);
    Color[v] = 2;
}
 
void TopologicalSort() 
{
    Color.resize(Graph.size(), 0);
    for (int i = 0; i < Graph.size(); i++) 
    {
        if (Color[i] == 0)
            DFS(i);
    }
    reverse(TopSeq.begin(), TopSeq.end());
}
 
int main()
{
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);
 
    BuildGraph();
    TopologicalSort();
 
    for (int i : TopSeq)
        cout << i + 1 << ' ';
 
    return 0;
}
