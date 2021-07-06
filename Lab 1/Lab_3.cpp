#include <vector>
#include <fstream>
 
using namespace std;
 
int main()
{
    ifstream fin("turtle.in");
    ofstream fout("turtle.out");
 
    vector <vector <long long>> a;
    long long len = 0;
    long long wid = 0;
 
    fin >> len >> wid;
 
    a.resize(len + 1);
 
    for (int i = 0; i < len; i++)
    {
        for (int j = 1; j < wid + 1; j++)
        {
            a[i].resize(wid + 1);
            a[i][0] = 0;
            fin >> a[i][j];
        }
    }
    a[len].resize(wid + 1);
    for (int q = 0; q < wid + 1; q++)
        a[len][q] = 0;
 
    for (int i = len - 1; i > -1; i--)
        for (int j = 1; j < wid + 1; j++)
            a[i][j] += max(a[i + 1][j], a[i][j - 1]);
 
    fout << a[0][wid];
     
    fin.close();
    fout.close();
    return 0;
}
