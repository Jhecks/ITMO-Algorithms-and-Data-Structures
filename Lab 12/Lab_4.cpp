#include <iostream>
#include <algorithm>
 
#define N 20
 
using namespace std;
 
size_t n, m;
int dp[N][N];
 
void counter(size_t i, size_t j)
{
    if (i == n && j == m)
        return;
 
    if (i + 2 <= n && j + 1 <= m)
    {
        dp[i + 2][j + 1] += dp[i][j];
        counter(i + 2, j + 1);
    }
 
    if (i + 1 <= n && j + 2 <= m)
    {
        dp[i + 1][j + 2] += dp[i][j];
        counter(i + 1, j + 2);
    }
 
    if (i+2 <= n && j > 1)
    {
        dp[i + 2][j - 1] += dp[i][j];
        counter(i + 2, j - 1);
 
    }
 
    if (i > 1 && j + 2 <= m)
    {
        dp[i - 1][j + 2] += dp[i][j];
        counter(i - 1, j+2);
    }
 
    dp[i][j] = 0;
}
 
 
 
 
int main()
{
    freopen("knight2.in",  "r", stdin);
    freopen("knight2.out", "w", stdout);
 
    cin >> n >> m;
 
    dp[1][1] = 1;
    counter(1, 1);
 
    cout << dp[n][m];
 
    return 0;
 
}
