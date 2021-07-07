#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int main()
{
    ifstream cin ("input.txt");
    ofstream cout ("output.txt");
 
    pair<int, int> graph;
    vector<int> Vertex;
    int CountVertex = 0;
    int CountEdge = 0;
    cin >> CountVertex >> CountEdge;
    Vertex.resize(CountVertex);
    for (int i = 0; i < CountEdge; i++)
    {
        cin >> graph.first >> graph.second;
        Vertex[graph.first-1]++;
        Vertex[graph.second-1]++;
    }
    for (int i = 0; i < CountVertex; i++)
        cout << Vertex[i] << ' ';
    cout << endl;
 
    cin.close();
    cout.close();
    return 0;
}
