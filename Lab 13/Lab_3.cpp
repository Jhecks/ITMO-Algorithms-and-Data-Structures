#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
vector <int> PrefixFunc;
string String;
 
void PrefixFunction()
{
    PrefixFunc.resize(String.size());
    PrefixFunc[0] = 0;
 
    for (int i = 1; i < String.size(); i++)
    {
        int j = PrefixFunc[i - 1];
        while (j != 0 && String[j] != String[i])
            j = PrefixFunc[j - 1];
        PrefixFunc[i] = (String[j] == String[i]) ? ++j : j;
    }
}
 
int main()
{
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
 
    cin >> String;
    PrefixFunction();
 
    for (auto i : PrefixFunc)
        cout << i << ' ';
 
    return 0;
}
