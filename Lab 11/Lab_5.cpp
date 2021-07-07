#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
struct Edge
{
    int from;
    int to;
    long long weight;
 
    Edge(int from_, int to_, long long weight_) : from(from_), to(to_), weight(weight_) {}
};
 
vector <Edge> Graph;
vector <int> Parent;
vector <long long> MinDistance;
int VertexNum, EdgeNum = 0;
const long long INF = 1e5;
 
void BuildGraph()
{
    cin >> VertexNum;
 
    Parent.resize(VertexNum, -1);
    MinDistance.resize(VertexNum, INF);
    MinDistance[0] = 0;
 
    for (int i = 0; i < VertexNum; i++)
        for (int j = 0; j < VertexNum; j++)
        {
            long long w;
            cin >> w;
            if (w != 1e9)
            {
                Graph.push_back(Edge(i, j, w));
                EdgeNum++;
            }
        }
}
 
void BellmanFordNegCycleCheck()
{
    int Check;
    for (int i = 0; i < VertexNum; i++)
    {
        Check = -1;
        for (int j = 0; j < EdgeNum; j++)
            if (MinDistance[Graph[j].to] > MinDistance[Graph[j].from] + Graph[j].weight)
            {
                MinDistance[Graph[j].to] = MinDistance[Graph[j].from] + Graph[j].weight;
                Parent[Graph[j].to] = Graph[j].from;
                Check = Graph[j].to;
            }
    }
 
    if (Check == -1)
    {
        cout << "NO";
        exit(0);
    }
    else
        {
        int Source = Check;
        for (int i = 0; i < VertexNum; i++)
            Source = Parent[Source];
 
        vector <int> CyclePath;
        int Current = Source;
 
        while (Current != Source || CyclePath.size() == 0)
        {
            CyclePath.push_back(Current);
            Current = Parent[Current];
        }
        reverse(CyclePath.begin(), CyclePath.end());
 
        cout << "YES\n" << CyclePath.size() + 1 << '\n';
        for (int i : CyclePath)
            cout << i + 1 << ' ';
        cout << CyclePath[0] + 1;
    }
}
 
int main()
{
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);
 
    BuildGraph();
    BellmanFordNegCycleCheck();
 
    return 0;
}
