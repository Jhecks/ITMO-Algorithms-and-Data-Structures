#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
vector <vector <long long>> MinDistance;
 
struct Pair
{
    int first = 0;
    int second = 0;
};
 
 
void BuildGraph()
{
    Pair input;
    cin >> input.first >> input.second;
 
    MinDistance.resize(input.first, vector <long long>(input.first));
 
    for (int i = 0; i < input.first; i++)
        for (int j = 0; j < input.first; j++)
        {
            if (i != j)
                MinDistance[i][j] = INT_MAX;
            else
                MinDistance[i][j] = 0;
        }
 
    for (int i = 0; i < input.second; i++)
    {
        Pair tmp;
        int w;
        cin >> tmp.first >> tmp.second >> w;
        tmp.first--; tmp.second--;
        MinDistance[tmp.first][tmp.second] = w;
    }
}
 
void FloydWarshall(vector <vector <long long>>& MinDistance)
{
    for (int k = 0; k < MinDistance.size(); k++)
        for (int i = 0; i < MinDistance.size(); i++)
            for (int j = 0; j < MinDistance.size(); j++)
                MinDistance[i][j] = min(MinDistance[i][j], MinDistance[i][k] + MinDistance[k][j]);
 
    for (int i = 0; i < MinDistance.size(); i++)
    {
        for (int j = 0; j < MinDistance.size(); j++)
            cout << MinDistance[i][j] << ' ';
        cout << '\n';
    }
}
 
int main()
{
    freopen("pathsg.in", "r", stdin);
    freopen("pathsg.out", "w", stdout);
 
    BuildGraph();
    FloydWarshall(MinDistance);
 
    return 0;
}
