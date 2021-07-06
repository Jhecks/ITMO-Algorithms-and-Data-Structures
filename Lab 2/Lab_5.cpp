#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
int modQuickSort(vector<int> &arr, int first,int last, int k)
{
    int piv = arr[(first+last) / 2];
    int i = first;
    int j = last;
    while(i <= j)
    {
        while(arr[i] < piv)
            i++;
        while(arr[j] > piv)
            j--;
        if(i <= j)
        {
            swap(arr[i],arr[j]);
            i++;
            j--;
        }
    }
 
    if (first <= k && k <= j)
        return modQuickSort(arr, first, j, k);
    if (i <= k && k <= last)
        return modQuickSort(arr, i, last, k);
    return arr[k];
}
 
int main()
{
    ifstream fin("kth.in");
    ofstream fout("kth.out");
 
    int len = 0, k = 0, A = 0, B = 0, C = 0, a1 = 0, a2 = 0;
 
    fin >> len >> k;
    vector<int> arr;
    arr.resize(len);
 
    fin >> A >> B >> C >> a1 >> a2;
    arr[0] = a1;
    arr[1] = a2;
    for (int i = 2; i < len; i++)
        arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
 
    fout << modQuickSort(arr, 0, len-1, k-1);
 
    fin.close();
    fout.close();
    return 0;
}
