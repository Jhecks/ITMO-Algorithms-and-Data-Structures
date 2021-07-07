#include <iostream>
#include <vector>
#include <cstring>
 
#define MAX 10001
 
using namespace std;
 
string first;
string second;
string ans;
 
int lcs1[2][MAX];
int lcs2[2][MAX];
 
void hirshberg(size_t firstLeft, size_t firstRight, size_t secondLeft, size_t secondRight)
{
    if (secondLeft == secondRight)
        return;
 
    if (firstLeft + 1 == firstRight)
    {
        for (size_t j = secondLeft; j < secondRight; ++j)
            if (first[firstLeft] == second[j])
            {
                ans.push_back(first[firstLeft]);
                break;
            }
        return;
    }
 
    size_t firstMid = (firstLeft + firstRight) / 2;
 
    memset(lcs1[0], 0, sizeof(int) * (secondRight - secondLeft + 1));
    memset(lcs2[0], 0, sizeof(int) * (secondRight - secondLeft + 1));
 
    for (size_t i = 1; i <= firstMid - firstLeft; ++i)
    {
        for (size_t j = 1; j <= secondRight - secondLeft; ++j)
        {
            if (first[firstLeft + i - 1] == second[secondLeft + j - 1])
                lcs1[1][j] = lcs1[0][j - 1] + 1;
            else
                lcs1[1][j] = max(lcs1[0][j], lcs1[1][j - 1]);
        }
        swap(lcs1[0], lcs1[1]);
    }
 
    for (size_t i = 1; i <= firstRight - firstMid; ++i)
    {
        for (size_t j = 1; j <= secondRight - secondLeft; ++j)
        {
            if (first[firstRight - i] == second[secondRight - j])
                lcs2[1][j] = lcs2[0][j - 1] + 1;
            else
                lcs2[1][j] = max(lcs2[0][j], lcs2[1][j - 1]);
        }
        swap(lcs2[0], lcs2[1]);
    }
 
    size_t maxSum = lcs2[0][secondRight - secondLeft];
    size_t len = 0;
 
    for (size_t i = 1; i <= secondRight - secondLeft; ++i)
    {
        if (lcs1[0][i] + lcs2[0][secondRight - secondLeft - i] > maxSum)
        {
            maxSum = lcs1[0][i] + lcs2[0][secondRight - secondLeft - i];
            len = i;
        }
    }
    hirshberg(firstLeft, firstMid, secondLeft, secondLeft + len);
    hirshberg(firstMid, firstRight, secondLeft + len, secondRight);
}
 
int main()
{
    cin >> first >> second;
 
    hirshberg(0, first.size(), 0, second.size());
 
    cout << ans << endl;
 
    return 0;
}
