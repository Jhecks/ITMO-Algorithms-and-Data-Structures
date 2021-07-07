#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
unsigned int NumberOfResults = 0;
vector <int> result;
 
bool SubStringCheck(string substr, string str, int iter)
{
    for (int i = iter, j = 0; i < str.size(), j < substr.size(); i++, j++)
    {
        if (str[i] != substr[j])
            return false;
    }
    return true;
}
 
void SubStringSearch(string substr, string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == substr[0])
            if(SubStringCheck(substr, str, i))
            {
                NumberOfResults++;
                result.push_back(i+1);
            }
    }
}
 
int main()
{
    freopen("search1.in", "r", stdin);
    freopen("search1.out", "w", stdout);
 
    string substr;
    string str;
 
    cin >> substr >> str;
 
    SubStringSearch(substr, str);
 
    cout << NumberOfResults << endl;
 
    for(int i = 0 ; i < NumberOfResults; i++)
        cout << result[i] << ' ';
    cout << endl;
 
    return 0;
}
