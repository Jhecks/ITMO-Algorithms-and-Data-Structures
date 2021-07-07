#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
vector <vector<int>> Graph;
vector <int> OrderList;
vector <char> Color;    // 0 - white, 1 - black
 
struct Pair
{
    int first;
    int second;
};
 
void BuildGraph()
{
    Pair input;
    cin >> input.first >> input.second;
 
    Graph.resize(input.first);
    for (int i = 0; i < input.second; i++)
    {
        Pair tmp;
        cin >> tmp.first >> tmp.second;
        tmp.first--; tmp.second--;
        Graph[tmp.first].push_back(tmp.second);
    }
}
 
void DFS(int v)
{
    Color[v] = 1;
    for (int i : Graph[v])
        if (Color[i] == 0)
            DFS(i);
    OrderList.push_back(v);
}
 
void CreateOrderList()
{
    Color.assign(Graph.size(), 0);
 
    for (int i = 0; i < Graph.size(); i++)
        if (Color[i] == 0)
            DFS(i);
}
 
bool IsHamiltonianGraph()
{
    reverse(OrderList.begin(), OrderList.end());
 
    for (int i = 0; i < OrderList.size() - 1; i++)
    {
        int v = OrderList[i];
        bool IsPath = false;
 
        for (int j : Graph[v])
            if (j == OrderList[i + 1])
                IsPath = true;
        if (!IsPath)
            return false;
    }
    return true;
}
 
int main()
{
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);
 
    BuildGraph();
    CreateOrderList();
    if (IsHamiltonianGraph())
        cout << "YES";
    else
        cout << "NO";
 
    return 0;
}
