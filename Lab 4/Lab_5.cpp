#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int BinSearch(vector<int> &a, int first, int last, int necessary)
{
    if (last >= first)
    {
        int i = first + (last - first) / 2;
        if (a[i] == necessary)
        {
            return i;
        }
        if (a[i] > necessary)
            return BinSearch(a, first, i - 1, necessary);
        return BinSearch(a, i + 1, last, necessary);
    }
    return -1;
}
 
int main()
{
    ifstream cin("binsearch.in");
    ofstream cout("binsearch.out");
    vector<int> arr;
    vector<int> necessary;
 
    int len1 = 0;
    int len2 = 0;
    cin >> len1;
    arr.resize(len1);
    for (int i = 0; i < len1; i++)
        cin >> arr[i];
    cin >> len2;
    necessary.resize(len2);
    for (int i = 0; i < len2; i++)
        cin >> necessary[i];
 
    for (int i = 0; i < len2; i++)
    {
        int NewPos = BinSearch(arr, 0, len1 - 1, necessary[i]);
        int LeftPos = NewPos;
        int RightPos = NewPos;
        if (NewPos == -1)
            cout << -1 << ' ' << -1 << endl;
        else
        {
            while (NewPos > 0)
            {
                NewPos = BinSearch(arr, 0, NewPos - 1, necessary[i]);
                if (NewPos != -1)
                    LeftPos = NewPos;
            }
            NewPos = RightPos;
            while (NewPos > -1 && NewPos < len1 - 1)
            {
                NewPos = BinSearch(arr, NewPos + 1, len1 - 1, necessary[i]);
                if (NewPos != -1)
                    RightPos = NewPos;
            }
            cout << LeftPos + 1 << " " << RightPos + 1 << endl;
        }
    }
    cin.close();
    cout.close();
    return 0;
}
