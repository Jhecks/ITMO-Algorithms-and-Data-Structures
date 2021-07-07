#include <vector>
#include <queue>
#include <fstream>
 
using namespace std;
 
struct Pair
{
    int first;
    int second;
};
 
 
void BFS(const vector < vector < int > >& g, vector < int >& d) 
{
    vector < char > used(g.size(), false);
    queue < int > q;
    q.push(0);
    used[0] = true;
 
    while (!q.empty()) 
    {   
        int curr_v = q.front();
        q.pop();
        for (int i = 0; i < g[curr_v].size(); i++) 
        {
            int neig_curr_v = g[curr_v][i];
            if (!used[neig_curr_v]) 
            {
                used[neig_curr_v] = true;
                q.push(neig_curr_v);
                d[neig_curr_v] = d[curr_v] + 1;
            }
        }
    }
}
 
int main() 
{
    ifstream cin("pathbge1.in");
    ofstream cout("pathbge1.out");
 
    int CountVertex, CountEdge;
    cin >> CountVertex >> CountEdge;
 
    vector < vector < int > > graph(CountVertex);
    vector < int > distance(CountVertex);
 
    for (int i = 0; i < CountEdge; i++)
    {
        Pair temp;
        cin >> temp.first >> temp.second;
        temp.first--; temp.second--;
        graph[temp.first].push_back(temp.second);
        graph[temp.second].push_back(temp.first);
    }
 
    BFS(graph, distance);
 
    for (int i = 0; i < CountVertex; i++)
        cout << distance[i] << ' ';
 
    cin.close();
    cout.close();
}
