#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
int power;
string text;
vector<int> prefix;
 
vector<vector<int>> init()
{
    cin >> power >> text;
    text += "#";
 
    vector<vector<int>> res(text.size(), vector<int>(power));
    return res;
}
 
vector<int> prefixFunction(const string &s)
{
    int n = s.size();
    vector<int> pi(n);
 
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
 
void exec(vector<vector<int>> &res)
{
    prefix = prefixFunction(text);
 
    for (int i = 0; i < text.size(); i++)
    {
        for (char c = 'a'; c < 'a' + power; c++)
        {
            if (i > 0 && c != text[i])
                res[i][c - 'a'] = res[prefix[i - 1]][c - 'a'];
            else
                res[i][c - 'a'] = i + (c == text[i]);
        }
    }
}
 
int main()
{
    vector<vector<int>> res = init();
    exec(res);
 
    for (const auto& row : res)
    {
        for (auto elem : row)
            cout << elem << " ";
        cout << endl;
    }
 
    return 0;
}
