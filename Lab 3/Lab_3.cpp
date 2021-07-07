#include <iostream>
#include <vector>
#include <string>
#include <fstream>
 
using namespace std;
 
vector<string> radixSort(vector<string> &arrayToSort, int digitsCount, int phasesCount)
{
    vector<string> arr;
    arr.resize(arrayToSort.size());
    for (int i = 0; i < arrayToSort.size(); i++)
        arr[i] = arrayToSort[i];
    vector<string> nextPhaseArray;
    nextPhaseArray.resize(arrayToSort.size());
 
    for (int phase = 0; phase < phasesCount; phase++)
    {
        int j = digitsCount - phase - 1;
        vector<int> digits;
        digits.resize(26);
        int digit;
        for (int i = 0; i < arr.size(); ++i)
        {
            digit = (int) (arr[i][j] - 'a');
            digits[digit]++;
        }
 
        int preCount = 0;
        int temp;
        for (int i = 0; i < 26; ++i)
        {
            temp = digits[i];
            digits[i] = preCount;
            preCount += temp;
        }
 
        for (int i = 0; i < arr.size(); ++i)
        {
            digit = (int) (arr[i][j] - 'a');
            nextPhaseArray[digits[digit]] = arr[i];
            digits[digit]++;
        }
 
        for (int i = 0; i < arrayToSort.size(); i++)
            arr[i] = nextPhaseArray[i];
    }
    return arr;
}
 
 
int main()
{
    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);
 
 
    int n, m, k;
    vector<string> arr;
    cin >> n >> m >> k;
    arr.resize(n);
    string str;
    for (int i = 0 ; i < n; i++)
    {
        cin >> str;
        arr[i] = str;
    }
    arr = radixSort(arr, m, k);
    for (int i = 0; i < n; ++i)
        cout << arr[i] << endl;

    fclose(stdin);
    fclose(stdout);
 
    return 0;
}
