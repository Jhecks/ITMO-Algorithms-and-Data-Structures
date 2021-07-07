#include <fstream>
#include <iostream>
#include <vector>
 
using namespace std;
 
int n, root;
vector <vector <int>> tree;
vector <vector <int>> result;
 
void input()
{
    cin >> n;
    tree.resize(n);
    result.assign(n, vector<int>(2, 0));
}
 
void Tree(int index)
{
    result[index][0] = 0;
    result[index][1] = 1;
 
    for (int i : tree[index])
        Tree(i);
 
    for (int i : tree[index])
    {
        result[index][0] += max(result[i][0], result[i][1]);
        result[index][1] += result[i][0];
    }
}
 
int main()
{
    input();
 
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
 
        if (temp != 0)
            tree[temp - 1].push_back(i);
        else
            root = i;
    }
 
    Tree(root);
    cout << max(result[root][0], result[root][1]);
}
