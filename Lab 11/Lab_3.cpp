#include <iostream>
#include <vector>
#include <set>
 
using namespace std;
 
vector <vector <pair <int, int>>> Graph;    // first - edge weight, second - adjacent vertex
vector <long long> MinDistance;
set <pair <long long, int>> Queue; // first - MinDistance[Vertex], second - Vertex
 
struct Pair
{
    int first = 0;
    int second = 0;
};
 
 
void BuildGraph()
{
    Pair input;
    cin >> input.first >> input.second;
 
    Graph.resize(input.first);
    MinDistance.resize(input.first, LLONG_MAX);
    MinDistance[0] = 0;
 
    for (int i = 0; i < input.second; i++)
    {
        Pair tmp;
        int w;
        cin >> tmp.first >> tmp.second >> w;
        tmp.first--; tmp.second--;
        Graph[tmp.first].push_back(make_pair(w, tmp.second));
        Graph[tmp.second].push_back(make_pair(w, tmp.first));
    }
}
 
void Dijkstra()
{
    Queue.insert(make_pair(MinDistance[0], 0));
 
    while (!Queue.empty())
    {
        int v = Queue.begin()->second;
        Queue.erase(Queue.begin());
 
        for (auto j : Graph[v])
            if (MinDistance[j.second] > j.first + MinDistance[v])
            {
                Queue.erase(make_pair(MinDistance[j.second], j.second));
                MinDistance[j.second] = j.first + MinDistance[v];
                Queue.insert(make_pair(MinDistance[j.second], j.second));
            }
    }
 
    for (auto i : MinDistance)
        cout << i << ' ';
}
 
int main()
{
    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);
 
    BuildGraph();
    Dijkstra();
 
    return 0;
}
