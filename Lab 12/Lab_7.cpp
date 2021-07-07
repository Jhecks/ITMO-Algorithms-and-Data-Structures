#include <iostream>
#include <cstdio>
 
using namespace std;
 
int dp[301][10001];
 
int main()
{
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
 
    int S, N;
    cin >> S >> N;
 
    int weights[N+1];
    for (int i = 1; i <= N; i++)
        cin >> weights[i];
 
    int ans = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= S; j++)
        {
            dp[i][j] = dp[i-1][j];
            if (j >= weights[i] && dp[i][j] < dp[i-1][j-weights[i]] + weights[i])
                dp[i][j] = dp[i-1][j-weights[i]] + weights[i];
            ans = max(dp[i][j], ans);
        }
 
    cout << ans;
 
    return 0;
}
