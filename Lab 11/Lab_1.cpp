#include <fstream>
#include <algorithm>
#include <vector>
 
#define MAX 2e18
 
using namespace std;
 
vector <vector <pair <long long, long long>>> Graph;
vector <long long> MinDistance;
vector <char> Found;
long long StartVertex, FinishVertex;
 
void BuildGraph()
{
    ifstream cin ("pathmgep.in");
 
    long long n;
    cin >> n >> StartVertex >> FinishVertex;
    StartVertex--;
    FinishVertex--;
 
    Graph.resize(n);
    Found.resize(n, 0);
    MinDistance.resize(n, MAX);
    MinDistance[StartVertex] = 0;
 
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
        {
            long long w;
            cin >> w;
            if (w != -1 && i != j)
                Graph[i].push_back(make_pair(j, w));
        }
    cin.close();
}
 
void Dijkstra()
{
    for (long long i = 0; i < Graph.size(); i++)
    {
        long long v = -1;
        for (long long j = 0; j < Graph.size(); j++)
            if (!Found[j] && (v == -1 || MinDistance[v] > MinDistance[j]))
                v = j;
        Found[v] = 1;
        for (auto j : Graph[v])
            MinDistance[j.first] = min(MinDistance[j.first], j.second + MinDistance[v]);
    }
}
 
int main()
{
    ofstream cout ("pathmgep.out");
 
    BuildGraph();
    Dijkstra();
 
    if (MinDistance[FinishVertex] != MAX)
        cout << MinDistance[FinishVertex] << endl;
    else
        cout << -1 << endl;
 
    return 0;
}
