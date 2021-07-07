#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
vector <vector<int>> Graph;
vector<int> Comp;
int CountComp = 0;
 
struct Pair
{
    int first;
    int second;
};
 
void SearchComp(int NumVertex) 
{
    if (Comp[NumVertex] == 0) 
    {
        Comp[NumVertex] = CountComp;
        for (int i = 0; i < Graph[NumVertex].size(); i++) 
            SearchComp(Graph[NumVertex][i]);
    }
}
 
int main()
{
    ifstream cin("components.in");
    ofstream cout("components.out");
    int CountVertex = 0;
    int CountEdge = 0;
    cin >> CountVertex >> CountEdge;
 
    Comp.resize(CountVertex+1);
    Graph.resize(CountVertex+1);
 
    Pair temp;
 
    for (int i = 0; i < CountEdge; i++) 
    {
        cin >> temp.first >> temp.second;
        Graph[temp.first].push_back(temp.second);
        Graph[temp.second].push_back(temp.first);
    }
 
    for (int i = 1; i < CountVertex+1; i++) 
    {
        if (Comp[i] == 0) 
        {
            CountComp++;
            SearchComp(i);
        }
    }
 
    cout << CountComp << endl;
 
    for (int i = 1; i < CountVertex+1; i++) 
    {
        cout << Comp[i] << ' ';
    }
         
    cin.close();
    cout.close();
    return 0;
}
