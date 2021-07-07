#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int M = 1e9;
const int N = 2005;
 
int t_shirts[N];
size_t d[N][N];
size_t L[N][N];
size_t R[N][N];
 
int main()
{
    int n = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t_shirts[i];
 
    for (int len = 1; len <= n; len++)
    {
        for (int l = 1; l <= n - len + 1; l++)
        {
            int r = l + len - 1;
            L[l][r] = (L[l][r] + L[l][r - 1]) % M;
            R[l][r] = (R[l][r] + R[l + 1][r]) % M;
            if (len == 1)
                d[l][r] = 1;
 
            else if (t_shirts[l] == t_shirts[r])
            {
                d[l][r] = (2 * d[l + 1][r - 1] + L[l][r] + R[l][r] + 3) % M;
                L[l][r + 1] = (L[l][r + 1] + d[l + 1][r - 1] + 1) % M;
                R[l - 1][r] = (R[l - 1][r] + d[l + 1][r - 1] + 1) % M;
            }
            else
                d[l][r] = (2 + d[l + 1][r - 1] + L[l][r] + R[l][r]) % M;
        }
    }
 
    cout << d[1][n] % M;
 
    return 0;
}
