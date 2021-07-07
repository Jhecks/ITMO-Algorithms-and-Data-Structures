#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
vector <vector<int>> Graph;
vector <int> Seq;
vector <char> Color;
 
int StartVertex, EndVertex;
bool HaveCycle;
 
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
 
 
bool DFS(int v)
{
    Color[v] = 1;
    for (int i : Graph[v])
    {
        if (Color[i] == 0)
        {
            Seq[i] = v;
            if (DFS(i))
                return true;
        }
        else if (Color[i] == 1)
        {
            StartVertex = i;
            EndVertex = v;
            HaveCycle = true;
            return true;
        }
    }
    Color[v] = 2;
    return false;
}
 
void FindCycle()
{
    Color.resize(Graph.size(), 0);
    Seq.resize(Graph.size());
    for (int i = 0; i < Graph.size(); i++)
    {
        if (DFS(i))
            break;
    }
 
    if (HaveCycle)
    {
        cout << "YES" << '\n';
        vector <int> CycleVertex;
        for (int i = EndVertex; i != StartVertex; i = Seq[i])
            CycleVertex.push_back(i);
 
        CycleVertex.push_back(StartVertex);
        reverse(CycleVertex.begin(), CycleVertex.end());
 
        for (int i : CycleVertex)
            cout << i + 1 << ' ';
    }
    else
        cout << "NO";
}
 
int main() {
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);
 
    BuildGraph();
    FindCycle();
 
    return 0;
}
