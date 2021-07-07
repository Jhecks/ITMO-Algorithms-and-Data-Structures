#include <iostream>
#include <vector>
#include <set>
 
using namespace std;
 
vector <vector <pair <int, int>>> Graph;
vector <int> MinWeight;
vector <char> SpanTree;
set <pair <int, int>> Queue;
const int INF = (1 << 31) - 1;
 
void BuildGraph()
{
    int n, m;
    cin >> n >> m;
 
    Graph.resize(n);
    MinWeight.resize(n, INF);
    MinWeight[0] = 0;
    Queue.insert(make_pair(0, 0));
    SpanTree.resize(n, false);
 
    for (int i = 0; i < m; i++) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        v1--; v2--;
        Graph[v1].push_back(make_pair(v2, w));
        Graph[v2].push_back(make_pair(v1, w));
    }
}
 
void MinSpanTree()
{
    for (int i = 0; i < Graph.size(); i++)
    {
        int v = Queue.begin()->second;
        Queue.erase(Queue.begin());
        SpanTree[v] = true;
 
        for (int j = 0; j < Graph[v].size(); j++)
        {
            int ToVertex = Graph[v][j].first;
            int ToEdgeWeight = Graph[v][j].second;
 
            if (!SpanTree[ToVertex] && ToEdgeWeight < MinWeight[ToVertex])
            {
                Queue.erase(make_pair(MinWeight[ToVertex], ToVertex));
                MinWeight[ToVertex] = ToEdgeWeight;
                Queue.insert(make_pair(MinWeight[ToVertex], ToVertex));
            }
 
        }
    }
}
 
void PrintSpanTreePathWeight()
{
    long long MinPathWeight = 0;
    for (int i : MinWeight)
        MinPathWeight += i;
    cout << MinPathWeight;
}
 
int main()
{
    freopen("spantree3.in", "r", stdin);
    freopen("spantree3.out", "w", stdout);
 
    BuildGraph();
    MinSpanTree();
    PrintSpanTreePathWeight();
 
    return 0;
}
