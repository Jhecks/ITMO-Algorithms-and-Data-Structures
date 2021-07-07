#include <iostream>
#include <fstream>
#include <vector>
  
struct Pair
{
    int first;
    int second;
};
  
using namespace std;
  
int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
  
    int CountVertex = 0;
    int CountEdge = 0;
    cin >> CountVertex >> CountEdge;
    vector<struct Pair> Graph;
    Graph.resize(CountEdge);
    for (int i = 0; i < CountEdge; i++)
        cin >> Graph[i].first >> Graph[i].second;
  
    vector<vector<int>> AdjacencyMatrix;
    AdjacencyMatrix.resize(CountVertex);
  
    for (int i = 0; i < CountVertex; i++)
    {
        AdjacencyMatrix[i].resize(CountVertex);
        for (int j = 0; j < CountVertex; j++)
            AdjacencyMatrix[i][j] = 0;
    }
  
  
    for (int i = 0; i < CountEdge; i++)
        AdjacencyMatrix[Graph[i].first - 1][Graph[i].second - 1] = 1;
  
    for (int i = 0; i < CountVertex; i++)
    {
        for (int j = 0; j < CountVertex; j++)
            cout << AdjacencyMatrix[i][j] << ' ';
        cout << endl;
    }
  
    cin.close();
    cout.close();
    return 0;
}
