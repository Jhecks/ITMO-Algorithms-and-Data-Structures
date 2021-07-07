#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
vector <char> Color;
vector <int> OrderList;
vector <int> Component;
int ComponentNum, Count = 0;
 
void BuildGraph(vector <vector <pair <int, int>>> &Graph)
{
    int VertexNum, EdgeNum;
    cin >> VertexNum >> EdgeNum;
 
    Graph.resize(VertexNum);
    Color.assign(Graph.size(), 0);
 
    for (int i = 0; i < EdgeNum; i++)
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        v1--; v2--;
        Graph[v1].push_back(make_pair(v2, w));
    }
}
 
int DFS(vector <vector <pair <int, int>>>& Graph, int v)
{
    Color[v] = 1;
    for (auto i : Graph[v])
        if (Color[i.first] == 0)
            DFS(Graph, i.first);
    return ++Count;
}
 
int DFS(vector <vector <int>> &Graph, int v)
{
    Color[v] = 1;
    for (int i : Graph[v])
        if (Color[i] == 0)
            DFS(Graph, i);
    return ++Count;
}
 
void DFS_C(vector <vector <int>> &Graph, int v)
{
    Color[v] = 1;
    for (int i : Graph[v])
        if (Color[i] == 0)
            DFS_C(Graph, i);
    OrderList.push_back(v);
}
 
void DFST_C(vector <vector <int>> &GraphT, int v)
{
    Color[v] = 1;
    Component.push_back(v);
    for (int i : GraphT[v])
        if (Color[i] == 0)
            DFST_C(GraphT, i);
}
 
vector <vector <int>> Transpose(vector <vector <int>> &Graph)
{
    vector <vector <int>> GraphT(Graph.size());
    for (int i = 0; i < Graph.size(); i++)
        for (int j : Graph[i])
            GraphT[j].push_back(i);
    return GraphT;
}
 
void CreateOrderList(vector <vector <int>> &Graph)
{
    Color.assign(Graph.size(), 0);
 
    for (int i = 0; i < Graph.size(); i++)
        if (Color[i] == 0)
            DFS_C(Graph, i);
}
 
 
void DefineComponents(vector <vector <int>> &GraphT, vector <int> &NewComponents)
{
    Color.assign(GraphT.size(), 0);
 
    for (int i = 0; i < GraphT.size(); i++)
    {
        int v = OrderList[GraphT.size() - 1 - i];
        if (Color[v] == 0)
        {
            DFST_C(GraphT, v);
            ComponentNum++;
            for (int j : Component)
                NewComponents[j] = ComponentNum - 1;
            Component.clear();
        }
    }
}
 
vector <int> Condensation(vector <vector <int>> &Graph)
{
    ComponentNum = 0;
    vector <vector <int>> GraphT = Transpose(Graph);
    vector <int> NewComponents(Graph.size());
    CreateOrderList(Graph);
    DefineComponents(GraphT, NewComponents);
    OrderList.clear();
    return NewComponents;
}
 
long long FindMST(vector <vector <pair <int, int>>> &Graph, int VertexNum, int Root)
{
    long long Result = 0;
    vector <int> MinEdge(VertexNum, INT_MAX);
 
    for (auto & i : Graph)
        for (auto j : i)
            MinEdge[j.first] = min(j.second, MinEdge[j.first]);
 
    for (int i = 0; i < Graph.size(); i++)
        if (i != Root)
            Result += MinEdge[i];
 
    vector <vector <int>> ZeroEdges(VertexNum);
    for (int i = 0; i < Graph.size(); i++)
        for (auto j : Graph[i])
            if (j.second == MinEdge[j.first])
                ZeroEdges[i].push_back(j.first);
 
    Color.assign(ZeroEdges.size(), 0);
    Count = 0;
    if (DFS(ZeroEdges, Root) == ZeroEdges.size())
        return Result;
 
 
    vector <int> NewComponents(Graph.size());
    NewComponents = Condensation(ZeroEdges);
 
    vector <vector <pair <int, int>>> NewGraph(ComponentNum);
    for (int i = 0; i < Graph.size(); i++)
        for (auto j : Graph[i])
            if (NewComponents[i] != NewComponents[j.first])
                NewGraph[NewComponents[i]].push_back(make_pair(NewComponents[j.first], j.second - MinEdge[j.first]));
 
    Result += FindMST(NewGraph, ComponentNum, NewComponents[Root]);
    return Result;
}
 
int main()
{
    freopen("chinese.in", "r", stdin);
    freopen("chinese.out", "w", stdout);
    vector <vector <pair <int, int>>> Graph; // first - vertex, second - weight
 
    BuildGraph(Graph);
 
    if (DFS(Graph, 0) != Graph.size())
        cout << "NO";
    else
        cout << "YES\n" << FindMST(Graph, Graph.size(), 0);
 
    return 0;
}
