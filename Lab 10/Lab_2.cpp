#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
 
using namespace std;
 
vector <pair<int, int>> Graph;
vector <double> MinWeight;
vector <char> SpanTree;
 
struct Pair
{
    int first = 0;
    int second = 0;
};
 
double Weight(int v1, int v2)
{
    double x_2 = (Graph[v1].first - Graph[v2].first) * (Graph[v1].first - Graph[v2].first);
    double y_2 = (Graph[v1].second - Graph[v2].second) * (Graph[v1].second - Graph[v2].second);
    return sqrt(x_2 + y_2);
}
 
void BuildGraph()
{
    int input;
    cin >> input;
 
    Graph.resize(input);
    MinWeight.resize(input, INT_MAX);
    MinWeight[0] = 0;
    SpanTree.resize(input, false);
 
    for (int i = 0; i < input; i++)
    {
        Pair input1;
        cin >> input1.first >> input1.second;
        Graph[i].first = input1.first;
        Graph[i].second = input1.second;
    }
}
 
void MinSpanTree()
{
    for (int i = 0; i < Graph.size(); i++)
    {
        int v = -1;
 
        for (int j = 0; j < Graph.size(); j++)
            if (!SpanTree[j] && (v == -1 || MinWeight[j] < MinWeight[v]))
                v = j;
 
        SpanTree[v] = true;
 
        for (int k = 0; k < Graph.size(); k++)
            if (!SpanTree[k] && Weight(v, k) < MinWeight[k])
                MinWeight[k] = Weight(v, k);
    }
}
 
int main()
{
    freopen("spantree.in",  "r", stdin);
    freopen("spantree.out", "w", stdout);
 
    BuildGraph();
    MinSpanTree();
 
    double MinPathWeight = 0;
    for (double i : MinWeight)
        MinPathWeight += i;
    cout << setprecision(15) << MinPathWeight;
 
    return 0;
}
