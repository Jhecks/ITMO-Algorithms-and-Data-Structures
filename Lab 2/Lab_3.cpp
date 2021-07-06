#include<vector>
#include<fstream>
#include<iostream>
 
using namespace std;
 
long long merge(vector<int> &arr, int left, int mid, int right)
{
    long long count = 0;
    int firstP = mid - left + 1;
    int secondP = right - mid;
 
    vector<int> firstArr;
    vector<int> secondArr;
    firstArr.resize(firstP);
    secondArr.resize(secondP);
 
    for (int i = 0; i < firstP; i++)
        firstArr[i] = arr[left + i];
    for (int j = 0; j < secondP; j++)
        secondArr[j] = arr[mid + 1 + j];
 
    int i = 0;
    int j = 0;
    int k = left;
    while (i < firstP || j < secondP)
    {
        if (((i < firstP) && (j < secondP) && (firstArr[i] <= secondArr[j])) || (j == secondP && i < firstP))
        {
            arr[k] = firstArr[i];
            i++;
        }
        else if (i == firstP && j < secondP)
        {
            arr[k] = secondArr[j];
            j++;
        }
        else
        {
            count += firstP - i;
            arr[k] = secondArr[j];
            j++;
        }
        k++;
    }
    return count;
}
 
long long mergeSort(vector <int> &arr, int left, int right)
{
    long long count = 0;
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        count += mergeSort(arr, left, mid);
        count += mergeSort(arr, mid + 1, right);
        count += merge(arr, left, mid, right);
    }
    return count;
}
 
int main()
{
    ifstream fin("inversions.in");
    ofstream fout("inversions.out");
    int len = 0;
    fin >> len;
    vector <int> arr;
    arr.resize(len);
 
    for (int i = 0; i < len; i++)
        fin >> arr[i];
 
    fout << mergeSort(arr, 0, len - 1) << endl;
 
    fin.close();
    fout.close();
 
    return 0;
}
