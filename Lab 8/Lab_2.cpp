#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
 
    int CountVertex = 0;
     
    cin >> CountVertex;
 
    vector<vector<int>> AdjacencyMatrix;
    AdjacencyMatrix.resize(CountVertex);
 
    for (int i = 0; i < CountVertex; i++)
    {
        AdjacencyMatrix[i].resize(CountVertex);
        for (int j = 0; j < CountVertex; j++)
        {
            cin >> AdjacencyMatrix[i][j];
            if (i == j && (AdjacencyMatrix[i][j] == 1))
            {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
 
    for (int i = 0; i < CountVertex; i++)
        for (int j = 0; j < CountVertex; j++)
            if (AdjacencyMatrix[i][j] == 1)
                if (AdjacencyMatrix[j][i] == 0)
                {
                    cout << "NO" << endl;
                    return 0;
                }
 
    cout << "YES" << endl;
    cin.close();
    cout.close();
    return 0;
}
