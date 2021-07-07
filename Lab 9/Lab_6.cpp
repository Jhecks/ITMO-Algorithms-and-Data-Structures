#include <iostream>
#include <vector>
 
using namespace std;
 
vector <pair<int, vector<int>>> Graph;    // first: 0 - lose, 1 - win, 2 - empty; second - adjacent vertex
vector <char> Color;    // 0 - white, 1 - black
int StartVertex;
int IsWinVertex = 0;
 
struct Pair
{
    int first;
    int second;
};
 
 
void BuildGraph()
{
    Pair input;
    int v, e;
    cin >> input.first >> input.second >> StartVertex;
 
    Graph.resize(input.first);
    StartVertex--;
    for (int i = 0; i < input.first; i++)
        Graph[i].first = 2;
    for (int i = 0; i < input.second; i++)
    {
        Pair tmp;
        int v1, v2;
        cin >> tmp.first >> tmp.second;
        tmp.first--; tmp.second--;
        Graph[tmp.first].second.push_back(tmp.second);
    }
}
 
void InvertIsWinVertex()
{
    if (IsWinVertex == 0)
        IsWinVertex = 1;
    else
        IsWinVertex = 0;
}
 
void DFS(int v)
{
    Color[v] = 1;
    for (int i : Graph[v].second)
        if (Color[i] == 0)
            DFS(i);
    if (Graph[v].first == 2)
    {
        Graph[v].first = IsWinVertex;
        InvertIsWinVertex();
    }
    else
        Graph[v].first = 1;
}
 
void StartGame()
{
    Color.assign(Graph.size(), 0);
    DFS(StartVertex);
    for (int i = 0; i < Graph[StartVertex].second.size(); i++)
    {
        int ChildVertex = Graph[StartVertex].second[i];
        if (Graph[ChildVertex].first == 0)
        {
            cout << "First player wins";
            exit(0);
        }
    }
    cout << "Second player wins";
}
 
int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
 
    BuildGraph();
    StartGame();
 
 
    return 0;
}
