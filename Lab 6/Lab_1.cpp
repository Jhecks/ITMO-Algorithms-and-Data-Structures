#include <vector>
#include <string>
#include <list>
#include <fstream>
 
using namespace std;
 
int hashing(long long elem)
{
    return abs(elem % 10000);
}
 
void ins(long long elem, vector<vector<int>> &bash)
{
    int it = hashing(elem);
    for (int i = 0; i < bash[it].size(); i++)
    {
        if (bash[it][i] == elem)
        {
            return;
        }
    }
    bash[it].push_back(elem);
}
 
bool exis(long long elem, vector<vector<int>> &bash)
{
    int it = hashing(elem);
    for (int i = 0; i < bash[it].size(); i++)
        if (bash[it][i] == elem)
            return true;
    return false;
}
 
void delet(long long elem, vector<vector<int>> &bash)
{
    int it = hashing(elem);
    for (int i = 0; i < bash[it].size(); i++)
    {
        if (bash[it][i] == elem)
        {
            swap(bash[it][i], bash[it][bash[it].size() - 1]);
            bash[it].pop_back();
        }
    }
}
 
int main()
{
    ifstream cin("set.in");
    ofstream cout("set.out");
    vector<vector<int>> bash;
    bash.resize(10000);
    string str;
    long long temp = 0;
    while (cin >> str)
    {
        cin >> temp;
        if (str == "insert")
            ins(temp, bash);
        if (str == "exists")
        {
            if (!exis(temp, bash))
                cout << "false" << endl;
            else
                cout << "true" << endl;
        }
        if (str == "delete")
            delet(temp, bash);
    }
    cin.close();
    cout.close();
    return 0;
}
