#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
 
using namespace std;
 
int n;
string t;
vector <string> s;
vector <map <char, int>> edges;
vector <int> lnk;
vector <int> length;
int last;
 
void init()
{
    cin >> n;
    s.resize(n);
    getline(cin, t);
 
    for (int i = 0; i < n; i++)
        getline(cin, s[i]);
 
    getline(cin, t);
}
 
int main()
{
    freopen("search4.in", "r", stdin);
    freopen("search4.out", "w", stdout);
 
    init();
 
    edges.emplace_back(map<char, int>());
    lnk.push_back(-1);
    length.push_back(0);
    last = 0;
 
    for (int i = 0; i < t.size(); i++)
    {
        edges.emplace_back(map<char, int>());
        length.push_back(i + 1);
        lnk.push_back(0);
        size_t r = edges.size() - 1;
 
        int p = last;
        while (p >= 0 && edges[p].find(t[i]) == edges[p].end())
        {
            edges[p][t[i]] = r;
            p = lnk[p];
        }
 
        if (p != -1)
        {
            int q = edges[p][t[i]];
            if (length[p] + 1 == length[q])
                lnk[r] = q;
 
            else
            {
                edges.push_back(edges[q]);
                length.push_back(length[p] + 1);
                lnk.push_back(lnk[q]);
                size_t new_q = edges.size() - 1;
                lnk[q] = lnk[r] = new_q;
                while (p >= 0 && edges[p][t[i]] == q)
                {
                    edges[p][t[i]] = new_q;
                    p = lnk[p];
                }
            }
        }
        last = r;
    }
 
    for (int i = 0; i < n; i++)
    {
        bool find = true;
        int k = 0;
        for (int j = 0; j < s[i].size(); j++)
        {
            if (edges[k].find(s[i][j]) == edges[k].end())
            {
                find = false;
                break;
            }
            k = edges[k][s[i][j]];
        }
        printf("%s\n", (find ? "YES" : "NO"));
    }
 
    return 0;
}
